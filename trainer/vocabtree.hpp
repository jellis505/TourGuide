#ifndef H_VOCAB_TREE
#define H_VOCAB_TREE

/****************************************************************************************\
*                                 Vocabulary Tree                                        *
\****************************************************************************************/

/* This structure is... */

class CvVocabTree : public CvStatModel
{
public:
    virtual CvVocabTree();
    virtual ~CvVocabTree();

    CvVocabTree( const CvMat* trainData, const CvMat* responses,
        const CvMat* varIdx=0, const CvMat* sampleIdx=0,
        const int branch_factor, const int depth );

    virtual bool train( const CvMat* trainData, const CvMat* responses,
        const CvMat* varIdx = 0, const CvMat* sampleIdx=0, bool update=false );

    virtual float predict( const CvMat* samples, CV_OUT CvMat* results=0 ) const;
    virtual void clear();

    virtual void write( CvFileStorage* storage, const char* name ) const;
    virtual void read( CvFileStorage* storage, CvFileNode* node );

protected:
    CvMat*                  cls_labels;
    flann::Index_<CvMat*>*  flann_index;
    CvMat*                  weights;
    int branch_factor;
    int depth;
};

#endif H_VOCAB_TREE
