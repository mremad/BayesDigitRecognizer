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

void FileOutput::write_params_to_file(double** means, double* variances, double** cov_matrix, int num_dims, int num_classes)
{
    //Assume dummy data for means, variances and cov_matrix
    //Assume num_dims = 256
    //Assume num_classes = 10
    
    //Write params to a file conforming to usps.README
    
	ofstream fout(this->path);
	
	fout << "d" << endl;
	fout << num_classes << "\t: # of classes" << endl;
	fout << num_dims << "\t: # dimension of observation vectors" << endl;
	
	for(int c=1; c<10; c++){ //classes
		fout << c << "\t: class k=" << c << endl;
		fout << p[c-1] << "\t: prior p(k=" << c << ")" << endl;
		
		//print mean vector for class c
		for(int d=0; d<256; d++)
			fout << means[c][d] << " ";
			
		fout << "\t: mean vector mu_{k=" << c << "} = (0,0)" << endl;
		
		//print co-variance vector for class c
		for(int d=0; d<256; d++)
			fout << cov_matrix[c][d] << " ";
			
		fout << "\t: vector of variances sigma^2_{k=" << c << "} = (1 1)" << endl;
 	}
	
	fout.close();
	
    printf("Writing to file completed successfully!\n");
}