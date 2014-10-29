//
//  BayesClassifier.h
//  BayesDigitRecognizer
//
//  Created by Mohamed Emad on 10/28/14.
//  Copyright (c) 2014 Mohamed Emad. All rights reserved.
//

#ifndef __BayesDigitRecognizer__BayesClassifier__
#define __BayesDigitRecognizer__BayesClassifier__

#include <stdio.h>
#include "BayesEstimators.h"

class BayesClassifier
{
    int** test_imgs;
    int* test_labels;
    
public:
    //Which real classes are confused with which recognized classes (KxK)
    int** confusion_matrix;
    
    int error_rate;
    
    BayesClassifier(int num_classes);
    
    int classify_single_image(BayesEstimators estimator, int* img);
    void load_test_data(string path);
    void process_test_data(BayesEstimators estimators, string path);
};

#endif /* defined(__BayesDigitRecognizer__BayesClassifier__) */
