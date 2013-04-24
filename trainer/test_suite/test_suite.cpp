//
//    test_suite.cpp
//  
#include "../feature_extractor.hpp"
#include "../vocabtree.hpp"
#include "../file_utils.hpp"

#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/nonfree/features2d.hpp>
#include <opencv2/ml/ml.hpp>

#include <boost/filesystem.hpp>

#include <algorithm>

#define FRAMES 2
#define TEST_FRACTION 10

using namespace std;
using namespace boost::filesystem;
using namespace cv;

int rand_gen (int i){
    return (rand() % i);
}

int main (int argc, char *argv[])
{
    if (argc != 2 && argc != 4) {
	cerr << "usage: test_suite <image-root> [model-output vocab-output]" << endl;
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
    vector<string> names;
    FeatureExtractor *featureExtractor = new FeatureExtractor();
    
    int nr_class = FileUtils::read_images(argv[1], images, labels, names);
    cout << "Number of images: " << images.size() << endl;
    cout << "Number of buildings: " << nr_class << endl;
    float current_accuracy = 1.0; //update on each round.
    float round = 0.0;
      
    // deterministically shuffling the vectors
    srand(6421);
    random_shuffle(images.begin(), images.end(), rand_gen);
    srand(6421);
    random_shuffle(labels.begin(), labels.end(), rand_gen);
    srand(6421);
    random_shuffle(names.begin(), names.end(), rand_gen);
    
    int test_round = 0;
    for(; test_round < TEST_FRACTION; test_round++){
        // extract test images 
	int test_size = images.size() / TEST_FRACTION;
	int test_offset = test_size * test_round;
	vector<Mat> test_images(images.begin() + test_offset, images.begin() + test_offset + test_size);
	images.erase(images.begin() + test_offset, images.begin() + test_offset + test_size);
	vector<int> test_labels(labels.begin() + test_offset, labels.begin() + test_offset + test_size);
	labels.erase(labels.begin() + test_offset, labels.begin() + test_offset + test_size);
	vector<string> test_names(names.begin() + test_offset, names.begin() + test_offset + test_size);
	names.erase(names.begin() + test_offset, names.begin() + test_offset + test_size);

	// extract test features
	vector<Mat> test_features;
	featureExtractor->extract_features_batch(test_images, test_features);

	// extract training features
	cout << "Extracting features..." << endl;
	vector<Mat> features;
	featureExtractor->extract_features_batch(images, features);

	// Concatenate the vector of Mats into a big Mat file
	Mat train_data;
	vector<int> features_img_labels;
	int features_size;
	for (int j = 0; j < features.size(); j++) {
	    train_data.push_back(features[j]);
	    features_size = features[j].rows;
	    for (int i = 0; i < features_size; i++) {
		features_img_labels.push_back(j);
	    }
	} 

	cout << "Extracted " << train_data.rows << " features." << endl;

	cout << "Training vocab tree..." << endl;
	//Set up the Vocab Tree Trainer
	CvVocabTree *vocab_tree = new CvVocabTree();
	vocab_tree->train(&train_data, features_img_labels, images.size());
	Mat* results;

	cout << "Predicting ..." << endl;
    
	float num_correct = 0;
	for(vector<int>::size_type i = 0; i != test_images.size(); i++) {
	    int result = vocab_tree->predict(&test_features[i], results);
	    cout << "The predicted building was: " << labels[result] 
		 << "The actual building was: " << test_labels[i]; 
	    if (labels[result] == test_labels[i]){
		num_correct++;
	    } 
	}
	cout << "The accuracy of this calculation is: " 
	     << num_correct/(float)test_labels.size() << endl;
    }
    return 0;
}
