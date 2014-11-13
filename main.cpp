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
    
    ofstream output("/Users/Mohamed/Documents/BayesDigitRecognizer/BayesDigitRecognizer/usps.covariances");
    
    //Change path according to the configuration of the project
    FileReader fr = FileReader("/Users/Mohamed/Documents/BayesDigitRecognizer/BayesDigitRecognizer/usps.train","/Users/Mohamed/Documents/BayesDigitRecognizer/BayesDigitRecognizer/usps.test","/Users/Mohamed/Documents/BayesDigitRecognizer/BayesDigitRecognizer/usps.outputparams");
    FileOutput fo = FileOutput("/Users/Mohamed/Documents/BayesDigitRecognizer/BayesDigitRecognizer/usps.outputparams");
    fr.read_files();
    fr.read_test_files();
    
    
    BayesEstimators bc = BayesEstimators(fr.image_vectors, fr.image_labels,fr.num_labels , fr.num_dim, fr.num_imgs);
    
    bc.estimate_means();
    bc.estimate_variances();
    bc.estimate_priors();
    
#ifdef ESTIMATE_ALL_COVARIANCE
    bc.estimate_pooled_cov_matrix();
    output << "Pooled Covariance Matrix: "<<endl;
    fo.write_covariance_to_file(bc.covariance_matrix, bc.num_dim, bc.num_classes, output);
    
    bc.estimate_pooled_diag_cov_matrix();
    output << "Diagonal Pooled Covariance Matrix: "<<endl;
    fo.write_covariance_to_file(bc.covariance_matrix, bc.num_dim, bc.num_classes, output);
    
    output << "Full Class Covariance Matrix: "<<endl;
    bc.estimate_full_cov_matrix();
    for(int i = 0;i<bc.num_classes;i++)
    {
        output << "Class K= "<<i<<endl;
        fo.write_covariance_to_file(bc.class_cov[i], bc.num_dim, bc.num_classes, output);
        
    }
    
    output << "Diagonal Class-Specific Covariance Matrix: "<<endl;
    bc.estimate_diag_class_cov_matrix();
    for(int i = 0;i<bc.num_classes;i++)
    {
        output << "Class K= "<<i<<endl;
        fo.write_covariance_to_file(bc.class_cov[i], bc.num_dim, bc.num_classes, output);
        
    }
    
    output.close();
    printf("Covariances estimated and printed in usps.covariances\n");
    return 0;
#endif
    
    bc.estimate_cov_matrix();
    
    
    fo.write_params_to_file(bc.mean_values, bc.variance_values, bc.covariance_matrix, bc.priors, fr.num_dim, fr.num_labels);
    
    fr.read_param_file(bc);
    
    BayesClassifier classifier = BayesClassifier(fr.num_labels);
    classifier.process_test_data(bc, fr.test_imgs, fr.test_labels, fr.num_test_imgs);
    
    
    return 0;
}
