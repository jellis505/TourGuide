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

// Function Declarations
void TF_IDF(const Mat &raw_counts, vector<double> &TF_IDF_weights);

CvVocabTree::CvVocabTree()
{
	branch_factor = 3;
	depth = 5; 
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


bool CvVocabTree::train(const Mat* _train_data,
                        const vector<int>& labels, const int _nr_unique_labels)
{
    // Generate words by running (k^l)-means
    Mat means;
    int max_iterations = 10;
    TermCriteria criteria(TermCriteria::EPS, 1, 200);
    int attempts = 1;
    int nr_means = pow((double)branch_factor, depth);
    Mat cluster_labels;
	cout << "The number of means" << nr_means << endl;
	cout << "The number of rows" << _train_data->rows << endl;
	cout << "The number of cols" << _train_data->cols << endl;
	
    double compactness = kmeans(*_train_data, nr_means, cluster_labels,
                                criteria, attempts, KMEANS_PP_CENTERS, means);

								cout << "Got out of kmeans code" << endl;
								
    // Construct flann index with means
    cvflann::flann_centers_init_t centers_init = cvflann::CENTERS_KMEANSPP;
    float cluster_boundary_index = 0.2;
    flann::KMeansIndexParams indexParams(branch_factor,
                                         depth, centers_init,
                                         cluster_boundary_index);
	
    flann_index = new flann::Index(means, indexParams);
	cout << "Got out of the Flann Shit" << endl;

    // Generate weights matrix of size num(train_data) x num(means)
    Mat *new_weights = new Mat( Mat::zeros(_nr_unique_labels,
                                                   means.rows,
                                                   CV_32F) );

    for (int i = 0; i < _train_data->rows; i++) 
	{
		Mat nearest;
		Mat dists;
        flann_index->knnSearch(_train_data->row(i), nearest, dists, 1, flann::SearchParams(1));
        new_weights->at<int>(labels[i], nearest.at<int>(0,0))++;

    }

    weights = new_weights;
	cout << weights->rows << endl;
	cout << weights->cols << endl;
	cout << "made it number one" << endl;
	
	// This section of the code creates weights for the TF-IDF documentiaton work
    Mat *image_vec_counts = new Mat( Mat::zeros(_nr_unique_labels,
                                                   means.rows,
                                                   CV_32F) );
	
	// This section of the code will return the list of images that have each of the values 
	for (int j = 0; j < _train_data->rows; j++) 
	{
		Mat nearest;
		Mat dists;
        flann_index->knnSearch(_train_data->row(j), nearest, dists, 1, flann::SearchParams(64));
		// Now increment this point with this image
		image_vec_counts->at<int>(labels[j],nearest.at<int>(0,0))++;
	}
	
	// This portion calculates the TF_IDF weighting scheme
	vector<double> TF_IDF_weights;

	TF_IDF(*image_vec_counts, TF_IDF_weights);
	
	
    Mat tf_idf(TF_IDF_weights);
	tf_idf = tf_idf.t();
	
	// normalize the weights row
	
	for (int i = 0; i < weights->rows; i++) 
	{
		for (int j = 0; j < weights->cols; j++ )
		{
			weights->at<float>(i,j) = weights->at<float>(i,j) * tf_idf.at<double>(0,j);
		}
    }
    return true;
}

float CvVocabTree::predict(const Mat* samples, Mat* results) const
{
    Mat *sum = new Mat( Mat::zeros(1, weights->cols, CV_32F) );

    for (int i = 0; i < samples->rows; i++) {
		Mat nearest;
		Mat dists;
        flann_index->knnSearch(samples->row(i), nearest, dists, 1, 0);
		cout << nearest.at<int>(0,0) << endl;
		sum->at<int>(0, nearest.at<int>(0,0))++;
    }

    double min, max;
    int minInd, maxInd;
    minMaxIdx(*sum, &min, &max, &minInd, &maxInd, Mat());

    // Run flann, return the label based on the weights matrix.
    return maxInd;
}


void CvVocabTree::write( CvFileStorage* fs, const char* name ) const
{
}


void CvVocabTree::read( CvFileStorage* fs, CvFileNode* root_node )
{
}

// Functions -- Not in the class header file
void TF_IDF(const Mat &raw_counts, vector<double> &TF_IDF_weights)
{
	// This function calculates the TF_IDF score for each value and each hit of the matrix
	// Mat raw counts is the matrix that contains
	// The raw counts file should be a matrix of dim. #ofimages x #ofcodewords
	// The TF_IDF_weights are the weights of the each respective codeword in the algorithm,
	// and these are computed by w_i = ln(N/Ni), where N is the number of images, and Ni is the number
	// of images that contain at least one example of codeword i
	
	int num_of_images = raw_counts.rows;
	int num_of_feats = raw_counts.cols;
	int N_i;
	double weight;
	for (int i = 0; i < num_of_feats; i++) {
		// Set the counts to 0
		N_i = 1; 	// This is one to eliminate dividing by 0 in the weighting scheme
		weight = 0;
		// This goes through one whole column and counts the number of values that 
		for (int j = 0; j < num_of_images; j++) {
			// If this image had this codeword within it add increment our counter 
			if (raw_counts.at<int>(j,i) > 0) {
				N_i++;
			}
		}
		// Now calculate the weight of this leaf node using the weighting scheme described above
		weight = log(num_of_images/N_i);
		TF_IDF_weights.push_back(weight);
		
	} 
	
	
}


/* End of file. */

