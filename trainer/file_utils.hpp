#ifndef FILE_UTILS_H
#define FILE_UTILS_H
#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>

#include <boost/filesystem.hpp>

using namespace std;
using namespace boost::filesystem;

class FileUtils {
	public:
	static bool isHidden(const path &);
	static int read_images(char *, vector<Mat> &, vector<int> &, vector<string> &);
};

bool FileUtils::isHidden(const path &p)
{
	string name = boost::filesystem::basename(p);
	
    if(name != ".." &&
       name != "."  &&
       (name[0] == '.' || name == "")) {
		return true;
    }

    return false;
};

int FileUtils::read_images(char *root, vector<Mat> &images, vector<int> &labels, vector<string> &Names)
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
};
#endif