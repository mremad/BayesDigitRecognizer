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
    this->path = path;
}

void FileOutput::write_params_to_file(double** means, double* variances, double** cov_matrix,double* priors, int num_dims, int num_classes)
{
    //Assume dummy data for means, variances and cov_matrix
    //Assume num_dims = 256
    //Assume num_classes = 10
    
    //Write params to a file conforming to usps.README
    
	ofstream fout(this->path);
	
	fout << "d" << endl;
	fout << num_classes << "\t: # of classes" << endl;
	fout << num_dims << "\t: # dimension of observation vectors" << endl;
	
	for(int c=0; c<num_classes; c++){ //classes
		fout << c << "\t: class k=" << c << endl;
		fout << priors[c] << "\t: prior p(k=" << c << ")" << endl;
		
		//print mean vector for class c
		for(int d=0; d<num_dims; d++)
			fout << means[c][d] << " ";
			
		fout << "\t: mean vector mu_{k=" << c << "}" << endl;
		
		//print co-variance vector for class c
		for(int d=0; d<num_dims; d++)
			fout << variances[d] << " ";
			
		fout << "\t: vector of variances sigma^2_{k=" << c << "}" << endl;
 	}
	
	fout.close();
	
    printf("Writing to file completed successfully!\n");
}

// b)
void FileOutput::write_covariance_to_file(double** cov_matrix, int num_dims, int num_classes)
{
    // TO DO
    
    //Append the given covariance matrix to a file (usps.covariances)
}