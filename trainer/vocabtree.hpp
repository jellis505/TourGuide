#ifndef H_VOCAB_TREE
#define H_VOCAB_TREE

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/nonfree/features2d.hpp>
#include <opencv2/ml/ml.hpp>
#include <opencv2/flann/flann.hpp>

/****************************************************************************************\
*                                 Vocabulary Tree                                        *
\****************************************************************************************/

/* This structure is... */

class CvVocabTree
{
public:
    CvVocabTree();
    ~CvVocabTree();

    CvVocabTree(const cv::Mat* trainData, const std::vector<int> _labels,
                const int _nr_unique_labels, const int _branch_factor,
                const int _depth);


    virtual bool train(const cv::Mat* _train_data,
                       const std::vector<int>& labels,
					   const std::vector<int>& classes,
                       const int _nr_unique_labels);

    virtual int predict(const cv::Mat* samples, cv::Mat* results, cv::Mat* distances) const;
    virtual void clear();

    virtual void write() const;
    virtual void read();

protected:
    cv::flann::Index* word_tree;
    int nr_words;
    cv::flann::Index* class_tree;
    int nr_classes;
    cv::Mat *tf_idf_weights;
    int branch_factor;
    int depth;
	std::vector<int> labels;	// The sample the ith feature-vector came from.
	std::vector<int> classes;	// The ground truth value of a ith feature-vector.
	cv::Mat means;
	cv::Mat class_counts;
};

#endif
