//
//  BayesClassifier.cpp
//  BayesDigitRecognizer
//
//  Created by Mohamed Emad on 10/28/14.
//  Copyright (c) 2014 Mohamed Emad. All rights reserved.
//

#include "BayesClassifier.h"

BayesClassifier::BayesClassifier(int num_classes)
{
    
}

int BayesClassifier::classify_single_image(BayesEstimators estimator, int* img)
{
    //Classify a single image and return the recognized digit
    
    return 0;
}

void BayesClassifier::load_test_data(string path)
{
    //Load the test images from usps.test into the arrays
}

void BayesClassifier::process_test_data(BayesEstimators estimators, string path)
{
    //1. Load test images
    
    //2. Classify images using bayes estimators
    
    //3. Fill confusion matrix with values
    
    //4. Calculate error rate ( < 20%)
}