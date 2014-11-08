//
//  MatrixOperations.h
//  BayesDigitRecognizer
//
//  Created by Mohamed Emad on 11/8/14.
//  Copyright (c) 2014 Mohamed Emad. All rights reserved.
//

#ifndef __BayesDigitRecognizer__MatrixOperations__
#define __BayesDigitRecognizer__MatrixOperations__

#include <stdio.h>
#include "Eigen/Dense"

class MatrixOperations
{
public:
   static Eigen::MatrixXf transform_array_to_matrix(int width, int height, double ** matrix);
   static Eigen::VectorXf transform_array_to_vector(int width, double* vector);
   static Eigen::VectorXf transform_array_to_vector(int width, int* vector);
   static double** transform_matrix_to_array(int width, int height, Eigen::MatrixXf matrix);
};

#endif /* defined(__BayesDigitRecognizer__MatrixOperations__) */
