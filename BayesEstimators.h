//
//  BayesClassifier.h
//  BayesDigitRecognizer
//
//  Created by Mohamed Emad on 10/28/14.
//  Copyright (c) 2014 Mohamed Emad. All rights reserved.
//

#ifndef __BayesDigitRecognizer__BayesEstimators__
#define __BayesDigitRecognizer__BayesEstimators__


#include <iostream>
#include <fstream>
#include <string>


using namespace std;
class BayesEstimators
{

    
    //Number of observations for each class Nk (Kx1);
    int* observations_per_class;
    
    void estimate_full_cov_matrix();
    void estimate_diag_class_cov_matrix();
    void estimate_pooled_cov_matrix();
    void estimate_pooled_diag_cov_matrix();
    
public:
    
    int num_obs;
    int** observations;
    int* observation_labels;
    int num_classes;
    int num_dim;
    
    BayesEstimators(int** observations, int* observation_labels, int num_classes, int num_dims, int num_obs);
    
    //2D array of all the means of all the dimensions for each class (DxK)
    double** mean_values;
    
    //1D array of the variance for each dimension (Dx1)
    double* variance_values;
    
    //double array of the covariance matrix (DxD)
    double** covariance_matrix;
    
    //Prior probabilities for each class (Kx1)
    double* priors;
    

    //Bayes Parameters Estimators
    void estimate_means();
    void estimate_variances();
    void estimate_cov_matrix();
    void estimate_priors();
    
    void deallocate();
    
};



#endif /* defined(__BayesDigitRecognizer__BayesClassifier__) */
