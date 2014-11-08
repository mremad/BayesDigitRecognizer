//
//  MatrixOperations.cpp
//  BayesDigitRecognizer
//
//  Created by Mohamed Emad on 11/8/14.
//  Copyright (c) 2014 Mohamed Emad. All rights reserved.
//

#include "MatrixOperations.h"


 Eigen::MatrixXf MatrixOperations::transform_array_to_matrix(int width, int height, double ** matrix)
{
    Eigen::MatrixXf ret_mat(width,height);
    
    for(int i = 0;i<height;i++)
    {
        for(int j = 0;j<width;j++)
        {
            ret_mat(i,j) = matrix[i][j];
        }
    }
    
    return ret_mat;
}

double** MatrixOperations::transform_matrix_to_array(int width, int height, Eigen::MatrixXf matrix)
{
    double** ret_array = (double**)malloc(sizeof(double*)*height);
    
    for(int i = 0; i < height ; i++)
    {
        ret_array[i] = (double*)malloc(sizeof(double)*width);
    }
    
    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            ret_array[i][j] = matrix(i,j);
        }
    }
    
    return ret_array;
}

 Eigen::VectorXf MatrixOperations::transform_array_to_vector(int width, double* vector)
{
    Eigen::VectorXf ret_vec(width);
    
    for(int i = 0;i<width;i++)
    {
        ret_vec[i] = vector[i];
    }
    
    return ret_vec;
}

Eigen::VectorXf MatrixOperations::transform_array_to_vector(int width, int* vector)
{
    Eigen::VectorXf ret_vec(width);
    
    for(int i = 0;i<width;i++)
    {
        ret_vec[i] = vector[i];
    }
    
    return ret_vec;
}
