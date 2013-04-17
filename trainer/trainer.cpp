//
//  trainer.cpp
//  
//
//

#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/nonfree/features2d.hpp>
#include <opencv2/ml/ml.hpp>

#include <boost/filesystem.hpp>
#include "feature_extractor.h"
#include "vocabtree.hpp"
#include <algorithm>

#define FRAMES 2

using namespace std;
using namespace boost::filesystem;
using namespace cv;


bool isHidden(const path &p)
{
	string name = boost::filesystem::basename(p);
	
    if(name != ".." &&
       name != "."  &&
       (name[0] == '.' || name == "")) {
		return true;
    }

    return false;
}

int read_images(char *root, vector<Mat> &images, vector<int> &labels, vector<string> &Names)
{
	path p(root);

	if ( !exists( p ) ) return -1;
	if ( !is_directory( p ) ) return -1;

	vector<path> vec;
	
	copy(directory_iterator(p), directory_iterator(), back_inserter(vec));

	vector<path>::const_iterator it;
	
	int num = 0;
	int count = 0;
	int stringlength, found_char, namelength;
	string str;
	string picname;
	string slash = "/";
	
	int counter_to_break_2 = 0;
	for (it = vec.begin(); it != vec.end() ; ++it) {
		if (isHidden(*it) || !is_directory(*it))
			continue;
		if (counter_to_break_2 == 6)
			break;
		counter_to_break_2++;
		// Get the name of this image within the filepath
		cout << (*it).string() << endl;
		str = (*it).string();
		stringlength = str.size();
		found_char = str.rfind(slash);
		namelength = stringlength-found_char;
		picname = str.substr(found_char+1,namelength);
		
		vector<path> vec2;

		copy(directory_iterator(*it), directory_iterator(), back_inserter(vec2));

		vector<path>::const_iterator it2;
		int counter_to_break = 0;
		for (it2 = vec2.begin(); it2 != vec2.end(); ++it2) {
			if (isHidden(*it2))
				continue;
			if (counter_to_break == 1){
				counter_to_break = 0;
				break;
			}
			counter_to_break++;
			
			// This fuction reads in the color image	
			Mat im = imread( (*it2).string(), CV_LOAD_IMAGE_GRAYSCALE);
			
			// This iterates through the values that we have that holds the vectors
			images.push_back(im);
			labels.push_back(num);
			Names.push_back(picname);
			
			count++;
		}
		num++;
	}
	return num;
}


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

	int nr_class = read_images(argv[1], images, labels, Names);
	cout << "max of labels: " << *max_element(labels.begin(),labels.end()) << endl;
    cout << "count: " << labels.size() << endl;
	cout << "nr_class: " << nr_class << endl;
	cout << "Size of Names: " << Names.size() << endl;
	cout << "number of images: " << images.size() << endl;

    Mat cv_labels(labels.size(), 1, CV_32SC1, &labels[0]);

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
			features_img_labels.push_back(j);
		}
		cout << "Finished Image: " << j << " of " << features.size() << endl;
	} 
	
	cout << features.size() << endl;
	cout << features_img_labels[0] << endl;
	cout << train_data.rows << endl;
	
	//Set up the Vocab Tree Trainer
	CvVocabTree *vocab_tree = new CvVocabTree();
	vocab_tree->train(&train_data, features_img_labels, nr_class);
	cout << "We made it past train!" << endl;
	Mat* results;
	
	cout << vocab_tree->predict(&features[0],results) << endl;
	
	
 //    if (model_output) {
 //        cout << "Creating model and vocab..." << endl;
 //        classifier.train_bow(images, cv_labels);
 //        classifier.save_with_bow(model_output, vocab_output);
 //    } else {
 //        cout << "Performing cross validation..." << endl;
 //        cout << classifier.cross_validate_bow(images, cv_labels) << endl;
	// }

	return 0;
}
