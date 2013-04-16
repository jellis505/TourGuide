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

class CvVocabTree : public CvStatModel
{
public:
    CvVocabTree();
    ~CvVocabTree();

    CvVocabTree( const CvMat* trainData, const CvMat* responses,
		const std::vector<int> labels,
        const CvMat* varIdx=0, const CvMat* sampleIdx=0,
        const int branch_factor=4, const int depth=3 );

    virtual bool train( const CvMat* trainData, const CvMat* responses,
        std::vector<int> labels, const CvMat* varIdx=0, const CvMat* sampleIdx=0, bool update=false );

    virtual float predict( const CvMat* samples, CV_OUT CvMat* results=0 ) const;
    virtual void clear();

    virtual void write( CvFileStorage* storage, const char* name ) const;
    virtual void read( CvFileStorage* storage, CvFileNode* node );

protected:
    CvMat*                      cls_labels;
    cv::flann::Index_<CvMat*>*  flann_index;
    CvMat*                      weights;
    int branch_factor;
    int depth;
	std::vector<int> labels;
};

#endif
