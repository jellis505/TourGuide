#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <cmath>

#include <boost/filesystem.hpp>

#include "../vocabtree.hpp"
#include "../feature_extractor.hpp"
#include "../ml.hpp"
#include "../file_utils.hpp"

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

  /* main loop for testing */
  for (int i = 0; i < number_of_tests; ++i) {
    int random_index = rand() % images.size();
    /* extract a random image, along with its name and label */
    Mat image = images[random_index];
    int label = labels[random_index];
    string name = names[random_index];

    cout << "Testing " << name << " against training set" << endl;

    /* remove items from theri respective vectors */
    images.erase(images.begin() + random_index);
    labels.erase(labels.begin() + random_index);
    names.erase(names.begin() + random_index);

    /* now build all the features with remainder of images */
    vector<Mat> features;
    featureExtractor->extract_features_batch(images, features);

    Mat train_data;
    vector<int> features_img_labels;
    int features_size;

    /* build a column-vector that has maps image labels to descriptors */
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
  
  }

}