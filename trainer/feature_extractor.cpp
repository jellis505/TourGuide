#include "feature_extractor.hpp"

void FeatureExtractor::extract_features_batch(vector<Mat> &images, vector<Mat> &feature_descriptors) {
    int number_of_images = images.size();
    for (int i = 0; i < number_of_images; i++) {
        Mat descriptors;
        extract_features(images[i], descriptors);
        feature_descriptors.push_back(descriptors);
    }
}

void FeatureExtractor::extract_features(Mat &image, Mat &feature_descriptors) {
    vector<KeyPoint> keypoints;
    imshow("hey", image);
    cout << "detecting features" << endl;
    detector->detect(image, keypoints);
    cout << "extracting features" << endl;
    extractor->compute(image, keypoints, feature_descriptors);
    cout << "outputting features over image" << endl;
    display_features(image, keypoints, feature_descriptors);
};

void FeatureExtractor::display_features(Mat &image, vector<KeyPoint> &keypoints, Mat &feature_descriptors) {
    int number_of_keypoints = keypoints.size();
    for (int i = 0; i < number_of_keypoints; i++) {
        circle(image, keypoints[i].pt, keypoints[i].size, Scalar(12,143,50));
    }
    imshow("Image", image);
    cout << "done with this image" << endl;
}