/*M///////////////////////////////////////////////////////////////////////////////////////
//
//  IMPORTANT: READ BEFORE DOWNLOADING, COPYING, INSTALLING OR USING.
//
//  By downloading, copying, installing or using the software you agree to this license.
//  If you do not agree to this license, do not download, install,
//  copy or use the software.
//
//
//            Intel License Agreement
//
// Copyright (C) 2000, Intel Corporation, all rights reserved.
// Third party copyrights are property of their respective owners.
//
// Redistribution and use in source and binary forms, with or without modification,
// are permitted provided that the following conditions are met:
//
//   * Redistribution's of source code must retain the above copyright notice,
//     this list of conditions and the following disclaimer.
//
//   * Redistribution's in binary form must reproduce the above copyright notice,
//     this list of conditions and the following disclaimer in the documentation
//     and/or other materials provided with the distribution.
//
//   * The name of Intel Corporation may not be used to endorse or promote products
//     derived from this software without specific prior written permission.
//
// This software is provided by the copyright holders and contributors "as is" and
// any express or implied warranties, including, but not limited to, the implied
// warranties of merchantability and fitness for a particular purpose are disclaimed.
// In no event shall the Intel Corporation or contributors be liable for any direct,
// indirect, incidental, special, exemplary, or consequential damages
// (including, but not limited to, procurement of substitute goods or services;
// loss of use, data, or profits; or business interruption) however caused
// and on any theory of liability, whether in contract, strict liability,
// or tort (including negligence or otherwise) arising in any way out of
// the use of this software, even if advised of the possibility of such damage.
//
//M*/

// Created by Joe Ellis and Peter Sugihara
// Columbia University -- 2013

// #include "precomp.hpp"

#include "vocabtree.hpp"
#include <opencv2/ml/ml.hpp>
#include <opencv2/flann/flann.hpp>

using namespace std;
using namespace cv;


CvVocabTree::CvVocabTree()
{
    // TODO: fill this in
}

void CvVocabTree::clear()
{
    // TODO: fill this in
}


CvVocabTree::~CvVocabTree()
{
    clear();
}


CvVocabTree::CvVocabTree(
    const CvMat* _train_data, const CvMat* _responses,
    const CvMat* _var_idx, const CvMat* _sample_idx,
    const int _branch_factor, const int _depth );
{
    branch_factor = _branch_factor;
    depth = _depth;

    train( _train_data, _responses, _var_idx, _sample_idx );
}


bool CvVocabTree::train( const CvMat* _train_data, const CvMat* _responses,
                            const CvMat* _var_idx, const CvMat* _sample_idx, bool update )
{
    // Generate words by running (k^l)-means

    // Construct flann index with means

    // Generate weights matrix of size num(responses) x num(means)
    
    return result;
}

float CvVocabTree::predict( const CvMat* samples, CvMat* results ) const
{
    // Run flann, return the label based on the weights matrix.
    return 0.0;
}


void CvVocabTree::write( CvFileStorage* fs, const char* name ) const
{
}


void CvVocabTree::read( CvFileStorage* fs, CvFileNode* root_node )
{
}

// Functions -- Not in the class header file
void TF_Idf(Mat &Raw_CountMats, Mat &TF_IDF_Mat)
{
	// This function calculates the TF_IDF score for each value and each hit of the matrix
	
	
}


/* End of file. */

