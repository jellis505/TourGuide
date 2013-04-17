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
                       const int _nr_unique_labels);

    virtual float predict(const cv::Mat* samples, cv::Mat* results=0) const;
    virtual void clear();

    virtual void write(CvFileStorage* storage, const char* name) const;
    virtual void read(CvFileStorage* storage, CvFileNode* node);

protected:
    cv::Mat* cls_labels;
    cv::flann::Index* flann_index;
    cv::Mat *weights;
    int branch_factor;
    int depth;
	std::vector<int> labels;
};

#endif
