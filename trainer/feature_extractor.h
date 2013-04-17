#ifndef FEATURE_EXTRACTOR_H
#define FEATURE_EXTRACTOR_H
#include <vector>
#include <stdio.h>
#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/nonfree/features2d.hpp>
#include <opencv2/ml/ml.hpp>

using namespace cv;
using namespace std;


class FeatureExtractor 
{
	public:
		FeatureExtractor() 
		{
            detector = FeatureDetector::create("STAR");
            extractor = new SiftDescriptorExtractor();
		}
        ~FeatureExtractor() {};

        void extract_features(Mat &images, Mat &feature_descriptors);
        void extract_features_batch(vector<Mat> &images, vector<Mat> &feature_descriptors);
        void display_features(Mat &image, vector<KeyPoint> &keypoints, Mat &feature_descriptors);
private:
    Ptr<FeatureDetector> detector;
    DescriptorExtractor *extractor;
};

#endif