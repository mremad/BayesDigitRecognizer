//
//  main.cpp
//  BayesDigitRecognizer
//
//  Created by Mohamed Emad on 10/28/14.
//  Copyright (c) 2014 Mohamed Emad. All rights reserved.
//

#include <iostream>
#include "FileReader.h"
#include "BayesEstimators.h"
#include "BayesClassifier.h"
#include "FileOutput.h"

int main(int argc, const char * argv[]) {
    
    printf("Bayes Digit Classifier!\n");
    
    //Change path according to the configuration of the project
    FileReader fr = FileReader("/Users/Mohamed/Documents/BayesDigitRecognizer/BayesDigitRecognizer/usps.train","/Users/Mohamed/Documents/BayesDigitRecognizer/BayesDigitRecognizer/usps.test");
    fr.read_files();
    fr.read_test_files();
    
    
    BayesEstimators bc = BayesEstimators(fr.image_vectors, fr.image_labels,fr.num_labels , fr.num_dim, fr.num_imgs);
    
    bc.estimate_means();
    bc.estimate_variances();
    bc.estimate_priors();
    bc.estimate_cov_matrix();
    
    FileOutput fo = FileOutput("/Users/Mohamed/Documents/BayesDigitRecognizer/BayesDigitRecognizer/usps.outputparams");
    fo.write_params_to_file(bc.mean_values, bc.variance_values, bc.covariance_matrix, bc.priors, fr.num_dim, fr.num_labels);
    
    BayesClassifier classifier = BayesClassifier(fr.num_labels);
    classifier.process_test_data(bc, fr.test_imgs, fr.test_labels, fr.num_test_imgs);
    
    
    return 0;
}
