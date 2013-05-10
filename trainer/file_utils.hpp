#ifndef FILE_UTILS_H
#define FILE_UTILS_H
#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <stdlib.h>

#include <boost/filesystem.hpp>

using namespace std;
using namespace boost::filesystem;

class FileUtils {
	public:
	static bool is_hidden(const path &);
	static int read_images(char *, vector<Mat> &, vector<int> &, vector<string> &);
	static void output_names(string outputfilename, vector<string> &names);
	static void input_names(string inputfilename, vector <string> &names);
	static void ReadOneImage(string name, Mat &image);
};

bool FileUtils::is_hidden(const path &p)
{
	string name = boost::filesystem::basename(p);
	
    if(name != ".." &&
       name != "."  &&
       (name[0] == '.' || name == "")) {
		return true;
    }

    return false;
}

int FileUtils::read_images(char *root, vector<Mat> &images, vector<int> &labels, vector<string> &names)
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
		if (is_hidden(*it) || !is_directory(*it))
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
		for (it2 = vec2.begin(); it2 != vec2.end(); ++it2) {
			if (is_hidden(*it2))
				continue;

			// This fuction reads in the color image	
			Mat im = imread( (*it2).string(), CV_LOAD_IMAGE_GRAYSCALE);
			
			// This iterates through the values that we have that holds the vectors
			images.push_back(im);
			labels.push_back(num);
			names.push_back(picname);
			
			count++;
		}
		num++;

        // TODO: Remove this to use more than 3 classes.
        if (num > 100)
            break;
	}
	return num;
}

void FileUtils::ReadOneImage(string name, Mat &image)
{
	// Read in the file in grayscale format
	string PIXEL_LIMIT = "300000";
	string resize = string("convert ") + name + " -resize @" + PIXEL_LIMIT + " " + name;
	system(resize.c_str());
	string grayscale = string("convert ") + name + " -colorspace Gray " + name;
	system(grayscale.c_str());

	image = imread(name, CV_LOAD_IMAGE_GRAYSCALE);
}

void FileUtils::output_names(string outputfilename, vector<string> &names)
{
	// Output the names to a file
	ofstream outputfile;
	outputfile.open (outputfilename.c_str());
	
	for (int j = 0; j < names.size(); j++)
	{
		// Output the name of the returned files 
		outputfile << names[j];
		outputfile << "\n";
	}
	outputfile.close();
	
	
	return;
	
}

void FileUtils::input_names(string inputfilename, vector<string> &names)
{
	  string line;
	  ifstream myfile (inputfilename.c_str());
	  if (myfile.is_open())
	  {
	    while ( myfile.good() )
	    {
	      getline(myfile,line);
		  names.push_back(line);
	    }
	    myfile.close();
		return;
	  }

	  else cout << "Unable to open file"; 
	  
	  // Return the server
	  return;
}



#endif
