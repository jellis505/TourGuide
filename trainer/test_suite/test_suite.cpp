//
//    trainer.cpp
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

#include <algorithm>


#define FRAMES 2

using namespace std;
using namespace boost::filesystem;
using namespace cv;

int main (int argc, char *argv[])
{
    cout << "Entered main loop." << endl;

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
    vector<string> names;
    FeatureExtractor *featureExtractor = new FeatureExtractor();
    
    int nr_class = FileUtils::read_images(argv[1], images, labels, names);
    cout << "Number of images: " << images.size() << endl;
    cout << "Number of buildings: " << nr_class << endl;

    cout << "getting images" << endl;
    int test_label = labels[8];
    cout << "got label" << endl;
    string test_name = names[8];
    Mat test_image = images[8];
    cout << "erasing images" << endl;
    images.erase(images.begin() + 8);
    labels.erase(labels.begin() + 8);
    names.erase(names.begin() + 8);
    cout << "getting features" << endl;
    Mat test_features;
    featureExtractor->extract_features(test_image, test_features);
    cout << "done" << endl;

    // Extract the features in batch mode for the pictures available
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

    cout << "\"Predicting\" ..." << endl;
    cout << "image 4 is image..." << vocab_tree->predict(&test_features, results) << endl;
    
    return 0;
}
