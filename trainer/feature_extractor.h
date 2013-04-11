#ifndef FEATURE_EXTRACTOR_H
#define FEATURE_EXTRACTOR_H
#include <vector>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/nonfree/features2d.hpp>
#include <opencv2/ml/ml.hpp>

using namespace cv;


class FeatureExtractor 
{
	public:
		FeatureExtractor() 
		{
            
		}
        ~FeatureExtractor() {};

        void extractFeatures(Mat &, Mat *); 
};

#endif