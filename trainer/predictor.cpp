//
//    .cpp
//  
#include "feature_extractor.hpp"
#include "vocabtree.hpp"
#include "file_utils.hpp"

#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/nonfree/features2d.hpp>
#include <opencv2/ml/ml.hpp>



#define FRAMES 2

using namespace std;
using namespace cv;

int main (int argc, char *argv[])
{
    if (argc != 2 && argc != 4) {
      cerr << "usage: trainer <image-root>" << endl;
      return -1;
    }
	 
	/*
    if (argc == 4) {
        model_output = argv[2];
        vocab_output = argv[3];
    }
	*/
	
	// Read in the necessary files
	Mat image;
    FileUtils::ReadOneImage(argv[1],image);
	
	
	// Read in the string of the file
    FeatureExtractor *featureExtractor = new FeatureExtractor();
	
	// Extract the features from the images
    Mat features;
    featureExtractor->extract_features(image, features);

	// Initialize the Vocab Tree
    CvVocabTree *vocab_tree = new CvVocabTree();
    
	// Now read in the vocab tree and the names of each element
	vocab_tree->read();
	vector <string> names;
	string namefile = "models/names.txt";
	FileUtils::input_names(namefile, names);
	
	// Read in the name files
	cout << "Got passed the file reading" << endl;
	
    Mat results;
	Mat* dists;
	int result = vocab_tree->predict(&features, &results);
	
	cout << "Success!" << endl;
	cout << "The first found name is: " << endl;
	cout << names[result] << endl;
	
	cout << "These are the top 10 results" << endl;
	cout << "results rows: " << results.rows << endl;
	cout << "columns cols: " << results.cols << endl;
	// This section outputs the top ten returned results
	for (int j = 0; j < results.cols; j++){
		cout << names[results.at<int>(0,j)] << endl;
	}
	
	// Return from the function
    return 0;
}
