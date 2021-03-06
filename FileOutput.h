//
//  FileOutput.h
//  BayesDigitRecognizer
//
//  Created by Mohamed Emad on 10/28/14.
//  Copyright (c) 2014 Mohamed Emad. All rights reserved.
//

#ifndef __BayesDigitRecognizer__FileOutput__
#define __BayesDigitRecognizer__FileOutput__

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
using namespace std;
class FileOutput
{
    
    string path;
public:
    FileOutput(string path);
    
    
    void write_params_to_file(double** means, double* vars, double** cov_matrix,double* priors, int num_dims, int num_classes);
    void write_covariance_to_file(double** cov_matrix, int num_dims, int num_classes, ofstream & output);
    void deallocate();
    
};

#endif /* defined(__BayesDigitRecognizer__FileOutput__) */
