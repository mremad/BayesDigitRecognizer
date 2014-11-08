//
//  BayesEstimators.cpp
//  BayesDigitRecognizer
//
//  Created by Mohamed Emad on 10/28/14.
//  Copyright (c) 2014 Mohamed Emad. All rights reserved.
//

#include "BayesEstimators.h"
#include "math.h"
#include "MatrixOperations.h"
#include "BayesCfg.h"

BayesEstimators::BayesEstimators(int** obs, int* obs_labels, int classes, int dims, int num_observations)
{
    //Constructor
    
    observations = obs;
    observation_labels = obs_labels;
    num_classes = classes;
    num_dim = dims;
    num_obs = num_observations;
    
    mean_values = (double**)malloc(sizeof(double*)*num_classes);
    for(int i = 0;i<num_classes;i++)
    {
        mean_values[i] = (double*)malloc(sizeof(double)*num_dim);
    }
    
    priors = (double*)malloc(sizeof(double)*num_classes);
    for(int i = 0 ; i < num_dim;i++)
        priors[i] = 0;
    
    variance_values = (double*)malloc(sizeof(double)*num_dim);
    for(int i = 0 ; i < num_dim;i++)
        variance_values[i] = 0;
    
    covariance_matrix = (double**)malloc(sizeof(double*)*num_dim);
    for(int i = 0;i < num_dim;i++)
    {
        covariance_matrix[i] = (double*)malloc(sizeof(double)*num_dim);
        for(int j = 0 ; j < num_dim;j++)
            covariance_matrix[i][j] = 0;
    }
}

void BayesEstimators::estimate_pooled_diag_cov_matrix()
{
    //Write to cov_matrix
    
    for(int i = 0 ;i<num_dim;i++)
    {
        for(int j = 0 ; j < num_dim ; j++)
        {
            if(i == j)
                covariance_matrix[i][j] = 1/variance_values[i];
            else
                covariance_matrix[i][j] = 0;
        }
    }
}

void BayesEstimators::estimate_pooled_cov_matrix()
{
    Eigen::MatrixXf cov_mat(num_dim,num_dim);
    
    for(int i = 0; i < num_obs;i++)
    {
        Eigen::VectorXf xn = MatrixOperations::transform_array_to_vector(num_dim, observations[i]);
        Eigen::VectorXf uk = MatrixOperations::transform_array_to_vector(num_dim, mean_values[observation_labels[i]%10]);
        
        cov_mat += (xn - uk) * (xn - uk).transpose();
    }
    
    cov_mat = cov_mat * (1/(num_obs*1.0));
    
    cov_mat = cov_mat.inverse();
    
    covariance_matrix = MatrixOperations::transform_matrix_to_array(num_dim, num_dim, cov_mat);
    
}

void BayesEstimators::estimate_diag_class_cov_matrix()
{
    
}

void BayesEstimators::estimate_cov_matrix()
{
#ifdef POOLED_DIAG_COV_MATRIX
    estimate_pooled_diag_cov_matrix();
#endif
    
#ifdef POOLED_COV_MATRIX
    estimate_pooled_cov_matrix();
#endif
}



void BayesEstimators::estimate_means()
{
    //Write to means array
    
    for(int i = 0;i<num_obs;i++)
    {
        int index = observation_labels[i]%10;
        
        priors[index]++;
        
        for(int j = 0;j<num_dim;j++)
        {
            mean_values[index][j] += observations[i][j];
        }
    }
    
    for(int i = 0;i<num_classes;i++)
        for(int j = 0;j<num_dim;j++)
            mean_values[i][j] = mean_values[i][j]/priors[i];
    
    
    for(int i = 0;i<num_dim;i++)
    {
        //printf("%f ",mean_values[0][i]);
    }
}

void BayesEstimators::estimate_priors()
{
    //Write to priors array
    
    for(int i = 0;i<num_classes;i++)
    {
        priors[i] = priors[i]/(num_obs*1.0);
    }
}

void BayesEstimators::estimate_variances()
{
    //Write to variances array
    
    for(int j = 0;j<num_dim;j++)
    {
        for(int i = 0;i < num_obs;i++)
        {
           variance_values[j] += pow (observations[i][j] - mean_values[observation_labels[i]%10][j],2);
        }
        
        variance_values[j] = variance_values[j]/(num_obs*1.0);
    }
    
    for(int i = 0; i < num_dim;i++)
    {
        //printf("%f ",variance_values[i]);
    }
    
}

void BayesEstimators::deallocate()
{
    //Free arrays
}