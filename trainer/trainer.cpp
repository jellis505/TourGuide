//
//  trainer.cpp
//  
//
//
#include "feature_extractor.hpp"
#include "vocabtree.hpp"
#include "file_utils.hpp"

#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/nonfree/features2d.hpp>
#include <opencv2/ml/ml.hpp>

#include <boost/filesystem.hpp>

#define FRAMES 2

using namespace std;
using namespace boost::filesystem;
using namespace cv;

int main (int argc, char *argv[])
{
	if (argc != 2 && argc != 4) {
		cerr << "usage: trainer <image-root> [model-output vocab-output]" << endl;
		return -1;
	}

    char *image_root = argv[1];
    char *model_output = NULL;
    char *vocab_output = NULL;

    if (argc == 4) {
        model_output = argv[2];
        vocab_output = argv[3];
    }

	vector<Mat> images;
	vector<int> labels;
	vector<string> Names;
    FeatureExtractor *featureExtractor = new FeatureExtractor();

	int nr_class = FileUtils::read_images(argv[1], images, labels, Names);

    cout << "count: " << labels.size() << endl;
	cout << "nr_class: " << nr_class << endl;
	cout << "Size of Names: " << Names.size() << endl;
	cout << "number of images: " << images.size() << endl;

	// Extract the features in batch mode for the pictures available
	vector<Mat> features;
    featureExtractor->extract_features_batch(images, features);
	
	// Concatenate the vector of Mats into a big Mat file
	cout << "We just got out of the extract features batch code" << endl;
	Mat train_data;
	vector<int> features_img_labels;
	int features_size;
	for (int j = 0; j < features.size(); j++)
	{
		train_data.push_back(features[j]);
		features_size = features[j].rows;
		for (int i = 0; i < features_size; i++)
		{
			features_img_labels.push_back(labels[j]);
		}
		cout << "Finished Image: " << j << " of " << features.size() << endl;
	} 
	
	//Set up the Vocab Tree Trainer
	CvVocabTree *cvVocabtree = new CvVocabTree();
	
	return 0;
}
