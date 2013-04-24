/*M///////////////////////////////////////////////////////////////////////////////////////
//
//  IMPORTANT: READ BEFORE DOWNLOADING, COPYING, INSTALLING OR USING.
//
//  By downloading, copying, installing or using the software you agree to this license.
//  If you do not agree to this license, do not download, install,
//  copy or use the software.
//
//
//            Intel License Agreement
//
// Copyright (C) 2000, Intel Corporation, all rights reserved.
// Third party copyrights are property of their respective owners.
//
// Redistribution and use in source and binary forms, with or without modification,
// are permitted provided that the following conditions are met:
//
//   * Redistribution's of source code must retain the above copyright notice,
//     this list of conditions and the following disclaimer.
//
//   * Redistribution's in binary form must reproduce the above copyright notice,
//     this list of conditions and the following disclaimer in the documentation
//     and/or other materials provided with the distribution.
//
//   * The name of Intel Corporation may not be used to endorse or promote products
//     derived from this software without specific prior written permission.
//
// This software is provided by the copyright holders and contributors "as is" and
// any express or implied warranties, including, but not limited to, the implied
// warranties of merchantability and fitness for a particular purpose are disclaimed.
// In no event shall the Intel Corporation or contributors be liable for any direct,
// indirect, incidental, special, exemplary, or consequential damages
// (including, but not limited to, procurement of substitute goods or services;
// loss of use, data, or profits; or business interruption) however caused
// and on any theory of liability, whether in contract, strict liability,
// or tort (including negligence or otherwise) arising in any way out of
// the use of this software, even if advised of the possibility of such damage.
//
//M*/

// Created by Joe Ellis and Peter Sugihara
// Columbia University -- 2013

// #include "precomp.hpp"

#include "vocabtree.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <opencv2/ml/ml.hpp>
#include <opencv2/flann/flann.hpp>
#include <cmath>

using namespace std;
using namespace cv;

void _TF_IDF(const Mat &raw_counts, vector<float> &TF_IDF_weights)
{
	// This function calculates the TF_IDF score for each value and each hit of the matrix
	// Mat raw counts is the matrix that contains
	// The raw counts should be a CV_32F matrix of dim. nr_classes x nr_words.
	// The TF_IDF_weights are the weights of the each respective codeword in the algorithm,
	// and these are computed by w_i = ln(N/Ni), where N is the number of images, and Ni is the number
	// of images that contain at least one example of codeword i

	float nr_images = raw_counts.rows;
	float nr_feats = raw_counts.cols;
	float N_i;
	float weight;
	for (int i = 0; i < nr_feats; i++) {
		// Set the counts to 0
		N_i = 1; 	// This is one to eliminate dividing by 0 in the weighting scheme
		weight = 0;
		// This goes through one whole column and counts the number of values that
		for (int j = 0; j < nr_images; j++) {
			// If this image had this codeword within it add increment our counter
			if (raw_counts.at<float>(j,i) > 0) {
				N_i++;
			}
		}
		// Now calculate the weight of this leaf node using the weighting scheme described above
		weight = log(nr_images/N_i);
		TF_IDF_weights.push_back(weight);
	}
}

CvVocabTree::CvVocabTree()
{
	branch_factor = 3;
	depth = 6; 
    // TODO: fill this in
}

void CvVocabTree::clear()
{
    // TODO: fill this in
}


CvVocabTree::~CvVocabTree()
{
    clear();
}


CvVocabTree::CvVocabTree(
    const Mat* _train_data,
	const vector<int> _labels, const int _nr_unique_labels,
    const int _branch_factor, const int _depth)
{
    branch_factor = _branch_factor;
    depth = _depth;

    train( _train_data, _labels, _nr_unique_labels);
}


bool CvVocabTree::train(const Mat* _train_data, const vector<int>& labels,
                        const int _nr_unique_labels)
{
    nr_classes = _nr_unique_labels;

    // Generate words by running (k^l)-means.
    Mat means;
    int max_iterations = 10;
    TermCriteria criteria(TermCriteria::EPS, 1, 200);
    int attempts = 1;
    nr_words = pow((float)branch_factor, depth);
    Mat cluster_labels;
	
    kmeans(*_train_data, nr_words, cluster_labels, criteria, attempts,
           KMEANS_PP_CENTERS, means);

    // Construct kd-tree of words (means).
    cvflann::flann_centers_init_t centers_init = cvflann::CENTERS_KMEANSPP;
    float cluster_boundary_index = 0.2;
    flann::KMeansIndexParams indexParams(branch_factor, depth, centers_init,
                                         cluster_boundary_index);
	
    word_tree = new flann::Index(means, indexParams);
    
	cout << "Constructed kd-tree of words." << endl;

    // Generate word occurence histograms for each class.
    // Each row of class_counts is a histogram with nr_words columns.
    Mat class_counts = Mat::zeros(_nr_unique_labels, nr_words, CV_32F);
    for (int i = 0; i < _train_data->rows; i++) {
		Mat nearest;
		Mat dists;
        word_tree->knnSearch(_train_data->row(i), nearest, dists, 1,
                               flann::SearchParams(1));
        class_counts.at<float>(labels[i], nearest.at<int>(0,0))++;
    }

	vector<float> TF_IDF_weights;
	_TF_IDF(class_counts, TF_IDF_weights);

    Mat tf_idf_weights_t(TF_IDF_weights);
    tf_idf_weights = new Mat(tf_idf_weights_t.t());

	// Normalize class_counts.
	float norm_factor;
	Scalar sum_val;
	float desired_sum = 1000;
	for (int i = 0; i < nr_classes; i++) {
		sum_val = sum(class_counts.row(i));
		norm_factor = desired_sum / sum_val[0];
		class_counts.row(i) = class_counts.row(i) * norm_factor;
	}

    cout << "normalized" << endl;

    // Multiply each row of the counts matrix by the tf_idf weights.
	for (int i = 0; i < class_counts.rows; i++) {
        class_counts.row(i) = class_counts.row(i).mul(tf_idf_weights->row(0));
    }

    // Construct a kd-tree for running knn on the classes.
    class_tree = new flann::Index(class_counts, indexParams);

    return true;
}

int CvVocabTree::predict(const Mat* samples, Mat* results) const
{
    // Construct a histogram of word occurences.
    Mat counts = Mat::zeros(1, nr_words, CV_32F);
    for (int i = 0; i < samples->rows; i++) {
		Mat nearest;
		Mat dists;
        word_tree->knnSearch(samples->row(i), nearest, dists, 1, 0);
        counts.at<float>(0, nearest.at<int>(0,0))++;
    }
    
	// Normalize the histogram.
	float norm_factor;
	Scalar sum_val;
	float desired_sum = 1000;
    sum_val = sum(counts);
    norm_factor = desired_sum / sum_val[0];
    counts = counts * norm_factor;

    // Multiply by the tf_idf weights.
    counts = counts.mul(tf_idf_weights->row(0));

    // Run flann, return the label based on the weights matrix.
    Mat nearest;
    Mat dists;
    class_tree->knnSearch(counts, nearest, dists, 1, flann::SearchParams(1));

    return nearest.at<int>(0,0);
}


void CvVocabTree::write( CvFileStorage* fs, const char* name ) const
{
}


void CvVocabTree::read( CvFileStorage* fs, CvFileNode* root_node )
{
}


/* End of file. */

