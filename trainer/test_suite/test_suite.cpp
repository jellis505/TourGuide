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
      
    while(1){ // this goes on forever for now; updating to a deterministic system soon
		
    // deterministically shuffling the vectors
    srand(6421);
    random_shuffle(images.begin(), images.end(), rand_gen);
    srand(6421);
    random_shuffle(labels.begin(), labels.end(), rand_gen);
    srand(6421);
    random_shuffle(names.begin(), names.end(), rand_gen);
    
    // extract test images 
    int test_size = images.size() / TEST_FRACTION;
    vector<Mat> test_images(images.begin() + 0, images.begin() + test_size);
    images.erase(images.begin() + 0, images.begin() + test_size);
    vector<int> test_labels(labels.begin() + 0, labels.begin() + test_size);
    labels.erase(labels.begin() + 0, labels.begin() + test_size);
    vector<string> test_names(names.begin() + 0, names.begin() + test_size);
    names.erase(names.begin() + 0, names.begin() + test_size);

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
		if (labels[result] == test_labels[i]){
			num_correct++;
		} 
    }
}
    // labels.insert(labels.begin() + k, test_label);
    // names.insert(names.begin() + k, test_name);
    // images.insert(images.begin() + k, test_image);
    
    return 0;
}
