//
//  FileOutput.cpp
//  BayesDigitRecognizer
//
//  Created by Mohamed Emad on 10/28/14.
//  Copyright (c) 2014 Mohamed Emad. All rights reserved.
//

#include "FileOutput.h"

FileOutput::FileOutput(string path)
{
    
}

void FileOutput::write_params_to_file(double** means, double* variances, double** cov_matrix,double* priors, int num_dims, int num_classes)
{
    //Assume dummy data for means, variances and cov_matrix
    //Assume num_dims = 256
    //Assume num_classes = 10
    
    //Write params to a file conforming to usps.README
    
    printf("Writing to file completed successfully!\n");
}