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
#define SHUFFLE_SEED 6421

using namespace std;
using namespace boost::filesystem;
using namespace cv;

int rand_gen (int i){
    return (rand() % i);
}

template <class T>
vector<T> get_slice(vector<T>* v, int round, int total_size){
    int slice_size = total_size / TEST_FRACTION;
    int start_offset = round * slice_size;
    int end_offset = start_offset + slice_size;
    end_offset = (end_offset > total_size) ? total_size : end_offset;
    vector<T> slice(v->begin() + start_offset, v->begin() + end_offset);
    v->erase(v->begin() + start_offset, v->begin() + end_offset);
    return slice;
} 

template<class T>
void restore_slice(vector<T>* v, vector<T>* slice, int round, int total_size){
    int slice_size = total_size / TEST_FRACTION;
    int offset = round * slice_size;
    for(int i = 0; i < slice->size(); i++) {
	if(offset + i > total_size){
	    v->insert(v->end(), (*slice)[i]);
	}
	else{
	    v->insert(v->begin() + offset + i, (*slice)[i]);
	}
    }
}

template<class T>
void deterministic_shuffle(vector<T>* v){
    srand(SHUFFLE_SEED);
    random_shuffle(v->begin(), v->end(), rand_gen);
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
      
    // shuffle the vectors
    deterministic_shuffle(&images);
    deterministic_shuffle(&labels);
    deterministic_shuffle(&names);
        
    int test_round = 0;
    for(; test_round < TEST_FRACTION; test_round++){
        // extract test images 
	int total_size = images.size();
	vector<Mat> test_images = get_slice(&images, test_round, total_size);
	vector<int> test_labels = get_slice(&labels, test_round, total_size);
	vector<string> test_names = get_slice(&names, test_round, total_size);

	// extract test features
	vector<Mat> test_features;
	featureExtractor->extract_features_batch(test_images, test_features);

	// extract training features
	cout << "Extracting features..." << endl;
	vector<Mat> features;
	featureExtractor->extract_features_batch(images, features);

        // concatenate the vector of Mats into a big Mat file
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
	Mat results;
	Mat distances;


	cout << "Predicting..." << endl;
	float num_correct_1 = 0.0;
	float num_correct_3 = 0.0;
	float num_correct_10 = 0.0;
	float per_building_correct[nr_class];
	float per_building_count[nr_class];
	vector <string> per_building_names;
	for(int i = 0; i < nr_class; i++){
	    per_building_names.push_back(0);
	}
	//fill_n(per_building_correct, nr_class, 0.0);
	//fill_n(per_building_count, nr_class, 0.0);
	int return_num = 30;
	for(int i = 0; i < test_images.size() && i < test_features.size(); i++) {
		int result = vocab_tree->predict(&test_features[i], &results, &distances, return_num);
	    //cout << "predicted " << names[result] 
		// << ", actually " << test_names[i] << endl;
	    per_building_count[test_labels[i]] += 1;
	    per_building_names[test_labels[i]] = test_names[i];
		// This line solves for the one nearest neighbor
		if (labels[result] == test_labels[i]){
		num_correct_1++;
		//per_building_correct[test_labels[i]] += 1;
	    }  
		
		for (int k = 0; k < 3; k++){
			if (labels[results.at<int>(0,k)] == test_labels[i]){
				num_correct_3++;
				break;
				}
			}
		// This line solves for the 10 nearest neighbors
		for (int k = 0; k < 10; k++){
			if (labels[results.at<int>(0,k)] == test_labels[i]){
				num_correct_10++;
				break;
				}
			}
	
			// Reset the values for results and distances
			//Mat results;
			//Mat distances;		
	}
	
	// Output the accuracies
	cout << "1-NN Classification Accuracy: " 
	     << num_correct_1/(float)test_labels.size() << endl;
	cout << "3-NN Classification Accuracy: " 
	     << num_correct_3/(float)test_labels.size() << endl;
	cout << "10-NN Classification Accuracy: " 
	     << num_correct_10/(float)test_labels.size() << endl << endl;
	
	for(int i = 0; i < nr_class; i++){
	    if(per_building_count[i] > 0){
		cout << "The accuracy for " << per_building_names[i] << " is "
		     << per_building_correct[i]/per_building_count[i] << endl;
	    }
	}

	restore_slice(&images, &test_images, test_round, total_size);
	restore_slice(&labels, &test_labels, test_round, total_size);
	restore_slice(&names, &test_names, test_round, total_size); 
    }
    return 0;
}
