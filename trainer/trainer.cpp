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
#include <boost/filesystem.hpp>
#include <algorithm>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/nonfree/features2d.hpp>
#include <opencv2/ml/ml.hpp>



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

	/*
    if (argc == 4) {
        model_output = argv[2];
        vocab_output = argv[3];
    }
	*/

    vector<Mat> images;
    vector<int> labels;
    vector<string> names;
    FeatureExtractor *featureExtractor = new FeatureExtractor();

    int nr_class = FileUtils::read_images(argv[1], images, labels, names);
    cout << "Number of images: " << images.size() << endl;
    cout << "Number of buildings: " << nr_class << endl;

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
    vocab_tree->train(&train_data, features_img_labels, labels, images.size());
    Mat* results;


    // Now we want to output the index structure that we have learned
	cout << "Saving the Tree Structure: " << endl;
	vocab_tree->write();
	
	// File Utils 
	cout << "Saving the Picture Indices: " << endl;
	string outputNameFile = "models/names.txt";
	FileUtils::output_names(outputNameFile,names);
	
	cout << "Successfully Output Names" << endl;
	cout << "Training Complete: " << endl;
	
    
    return 0;
}
