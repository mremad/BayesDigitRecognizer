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
    
    class_cov = (double***)malloc(sizeof(double**)*num_classes);
    
    for(int k = 0;k<num_classes;k++)
    {
        class_cov[k] = (double**)malloc(sizeof(double*)*num_dim);
        for(int i = 0;i < num_dim;i++)
        {
            class_cov[k][i] = (double*)malloc(sizeof(double)*num_dim);
            for(int j = 0 ; j < num_dim;j++)
                class_cov[k][i][j] = 0;
        }
    }
}

// d)
void BayesEstimators::smooth_covariances(double delta)
{
    estimate_full_cov_matrix();
    estimate_pooled_cov_matrix();
    
    Eigen::MatrixXf pooled_cov = MatrixOperations::transform_array_to_matrix(num_dim, num_dim, covariance_matrix);
    
    Eigen::MatrixXf *class_cov_mat = (Eigen::MatrixXf *)malloc(sizeof(Eigen::MatrixXf)*num_classes);
    for(int i = 0;i<num_classes;i++)
    {
        class_cov_mat[i] = MatrixOperations::transform_array_to_matrix(num_dim, num_dim, class_cov[i]);
        
        class_cov_mat[i] = (delta * pooled_cov) + ( class_cov_mat[i] * (1-delta) );
        
        class_cov[i] = MatrixOperations::transform_matrix_to_array(num_dim, num_dim, class_cov_mat[i]);
    }
    
}

// b) iv)
void BayesEstimators::estimate_pooled_diag_cov_matrix()
{
    
    for(int i = 0 ;i<num_dim;i++)
    {
        for(int j = 0 ; j < num_dim ; j++)
        {
            if(i == j)
                covariance_matrix[i][j] = variance_values[i];
            else
                covariance_matrix[i][j] = 0;
        }
    }
}

// b) iii)
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
    
    covariance_matrix = MatrixOperations::transform_matrix_to_array(num_dim, num_dim, cov_mat);
    
}

// b) ii)
void BayesEstimators::estimate_diag_class_cov_matrix()
{
    int *class_entries = (int*)malloc(sizeof(int)*num_classes);
    
    for(int i = 0;i<num_classes;i++)
        for(int j = 0;j<num_dim;j++)
            for(int k = 0;k<num_dim;k++)
                class_cov[i][j][k] = 0;
    
    for(int i = 0; i < num_obs;i++)
    {
        for(int j = 0;j < num_dim;j++)
        {
           class_cov[observation_labels[i]%10][j][j] += pow(observations[i][j] - mean_values[observation_labels[i]%10][j],2);
        }
        
        class_entries[observation_labels[i]%10] ++;
    }
    
    for(int i = 0;i < num_classes;i++)
    {
        for(int j = 0; j < num_dim; j++)
        {
            class_cov[i][j][j] = class_cov[i][j][j]/(class_entries[i]*1.0);
        }
    }
}

// b) i)
void BayesEstimators::estimate_full_cov_matrix()
{
    Eigen::MatrixXf *class_cov_mat = (Eigen::MatrixXf *)malloc(sizeof(Eigen::MatrixXf)*num_classes);
    for(int i = 0;i<num_classes;i++)
        class_cov_mat[i] = Eigen::MatrixXf(num_dim,num_dim);
    int *class_entries = (int*)malloc(sizeof(int)*num_classes);
    
    for(int i = 0;i<num_classes;i++)
        class_entries[i] = 0;
    
    for(int i = 0; i < num_obs;i++)
    {
        Eigen::VectorXf xn = MatrixOperations::transform_array_to_vector(num_dim, observations[i]);
        
        Eigen::VectorXf uk = MatrixOperations::transform_array_to_vector(num_dim, mean_values[observation_labels[i]%10]);
        
        class_cov_mat[observation_labels[i]%10] += (xn - uk) * (xn - uk).transpose();
        class_entries[observation_labels[i]%10] ++;
    }
    
    for(int i = 0;i < num_classes ;i ++)
    {
        class_cov_mat[i] = class_cov_mat[i] * (1/(class_entries[i]*1.0));
        
        class_cov[i] = MatrixOperations::transform_matrix_to_array(num_dim, num_dim, class_cov_mat[i]);
    }
    
    
}

void BayesEstimators::calculate_pooled_cov_inverse()
{
    Eigen::MatrixXf pooled_cov = MatrixOperations::transform_array_to_matrix(num_dim, num_dim, covariance_matrix);
    covariance_matrix = MatrixOperations::transform_matrix_to_array(num_dim, num_dim, pooled_cov.inverse());

}

void BayesEstimators::calculate_class_cov_inverse()
{
    Eigen::MatrixXf *class_cov_mat = (Eigen::MatrixXf *)malloc(sizeof(Eigen::MatrixXf)*num_classes);
    for(int i = 0;i<num_classes;i++)
    {
        class_cov_mat[i] = MatrixOperations::transform_array_to_matrix(num_dim, num_dim, class_cov[i]);
        
        class_cov[i] = MatrixOperations::transform_matrix_to_array(num_dim, num_dim, class_cov_mat[i].inverse());
    }
}

void BayesEstimators::estimate_cov_matrix()
{
#ifdef POOLED_DIAG_COV_MATRIX
    estimate_pooled_diag_cov_matrix();
#endif
    
#ifdef POOLED_COV_MATRIX
    estimate_pooled_cov_matrix();
#endif
    
#ifdef FULL_CLASS_COV_MATRIX
    estimate_full_cov_matrix();
#endif
    
#ifdef DIAG_CLASS_COV_MARTIX
    estimate_diag_class_cov_matrix();
#endif
    
#ifdef SMOOTHED_COV
    smooth_covariances(DELTA);
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