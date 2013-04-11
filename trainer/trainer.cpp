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


#define FRAMES 2

using namespace std;
using namespace cv;
using namespace boost::filesystem;


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
	
	for (it = vec.begin(); it != vec.end() ; ++it) {
		if (isHidden(*it) || !is_directory(*it))
			continue;
		
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
			if (counter_to_break == 2){
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

	int nr_class = read_images(argv[1], images, labels, Names);

    cout << "count: " << labels.size() << endl;
	cout << "nr_class: " << nr_class << endl;
	cout << "Size of Names: " << Names.size() << endl;
	
	
    Mat cv_labels(labels.size(), 1, CV_32SC1, &labels[0]);
	
	

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
	