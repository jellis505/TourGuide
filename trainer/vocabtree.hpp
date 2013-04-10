/****************************************************************************************\
*                                 Normal Bayes Classifier                                *
\****************************************************************************************/

/* The structure, representing the grid range of statmodel parameters.
   It is used for optimizing statmodel accuracy by varying model parameters,
   the accuracy estimate being computed by cross-validation.
   The grid is logarithmic, so <step> must be greater then 1. */

class CvVocabTree : public CvStatModel
{
public:
    virtual CvVocabTree();
    virtual ~CvVocabTree();

    CvVocabTree( const CvMat* trainData, const CvMat* responses,
        const CvMat* varIdx=0, const CvMat* sampleIdx=0 );

    virtual bool train( const CvMat* trainData, const CvMat* responses,
        const CvMat* varIdx = 0, const CvMat* sampleIdx=0, bool update=false );

    virtual float predict( const CvMat* samples, CV_OUT CvMat* results=0 ) const;
    virtual void clear();

#ifndef SWIG
    CvVocabTree( const cv::Mat& trainData, const cv::Mat& responses,
                            const cv::Mat& varIdx=cv::Mat(), const cv::Mat& sampleIdx=cv::Mat() );
    virtual bool train( const cv::Mat& trainData, const cv::Mat& responses,
                       const cv::Mat& varIdx = cv::Mat(), const cv::Mat& sampleIdx=cv::Mat(),
                       bool update=false );
    virtual float predict( const cv::Mat& samples, CV_OUT cv::Mat* results=0 ) const;
#endif

    virtual void write( CvFileStorage* storage, const char* name ) const;
    virtual void read( CvFileStorage* storage, CvFileNode* node );

protected:
    CvMat*  cls_labels;
};
