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
#include <cmath>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/nonfree/features2d.hpp>
#include <opencv2/ml/ml.hpp>

#include <boost/filesystem.hpp>

#include <algorithm>

using namespace std;
using namespace boost::filesystem;
using namespace cv;

int main (int argc, char *argv[])
{
    if (argc != 2) {
      cerr << "usage: test_suite <image-root>" << endl;
      return -1;
    }
    
    int number_of_tests;
    /* number of times we run this test AKA number of random images we test with */
    if (argc == 3) {
      number_of_tests = atoi(argv[2]);
    } else {
      number_of_tests = 10;
    }

    char *image_root = argv[1];
    char *model_output = NULL;
    char *vocab_output = NULL;
    
    vector<Mat> images;
    vector<int> labels;
    vector<string> names;
    FeatureExtractor *featureExtractor = new FeatureExtractor();

    /* load in images */
    int nr_class = FileUtils::read_images(argv[1], images, labels, names);
    /* take one image out of the set randomly and test it against the training set */

    vector<string> images_used; /* keep track of images we used so we don't repeat */
    vector<int> training_numbers;
    for (int i = 0; i < images.size(); i++) {
        training_numbers.push_back(i);
    }

    /* main loop for testing */
    for (int i = 0; i < 10; ++i) {
        vector <Mat> test_images;
        vector<int> test_labels;
        vector<string> test_names;

        int num_images = images.size();
        int steps = num_images / 10;
        int j = 0;

        for (j = i; j < num_images; j += steps) {
            test_images.push_back(images[j]);
            test_labels.push_back(labels[j]);
            test_names.push_back(names[j]);
        }

        /* remove items from their respective vectors */
        j = j - steps;
        for (; j >= 0; j -= steps) {
            images.erase(images.begin() + j);
            labels.erase(labels.begin() + j);
            names.erase(names.begin() + j);
        }

        /* now build all the features with remainder of images */
        vector<Mat> training_features;
        featureExtractor->extract_features_batch(images, training_features);

        vector<Mat> test_features;
        featureExtractor->extract_features_batch(test_images, test_features);

        Mat train_data;
        vector<int> features_img_labels;
        int features_size;

        /* build a column-vector that has maps image labels to descriptors */
        for (int j = 0; j < training_features.size(); j++)
        {
          train_data.push_back(training_features[j]);
          features_size = training_features[j].rows;
          for (int i = 0; i < features_size; i++)
          {
            features_img_labels.push_back(labels[j]);
          }
          cout << "Finished Image: " << j << " of " << training_features.size() << endl;
        }

        cout << "Training vocab tree..." << endl;

        //Set up the Vocab Tree Trainer
        CvVocabTree *vocab_tree = new CvVocabTree();
        vocab_tree->train(&train_data, features_img_labels, images.size());
        Mat* results;
        int num_test_images = test_images.size();
	int i = 0;
	for (; i < num_test_images; i++) {
            cout << "\"Predicting\" (on images I should know)..." << endl;
            cout << "image " << test_labels[i] << " is image... " 
		 << vocab_tree->predict(&test_features[i], results) << endl;
        }
	j = i;
        for (; j < num_images; j += steps) {
            images.insert(images.begin() + j, test_images[ j / steps]);
            labels.insert(labels.begin() + j, test_labels[j / steps]);
            names.insert(names.begin() + j, test_names[j / steps]);
        }
  }
}
