#ifndef _FILEREADER
#define _FILEREADER

#include <iostream>
#include <fstream>
#include <string>
#include "BayesEstimators.h"

using namespace std;
class FileReader
{
    
    string path;
    string test_path;
    string param_path;
public:
    FileReader(string path, string test_path, string param_path);
    //2D array of all the dimensions of all the images. Size: (NxD)
    int** image_vectors;
    
    //1D array of the label of each image (Nx1)
    int* image_labels;
    
    //Number of classes
    int num_labels;
    
    //Number of image dimensions
    int num_dim;
    
    //Number of observations
    int num_imgs;
    
    
    
    int num_test_imgs;
    
    int* test_labels;
    
    int** test_imgs;
    
    void read_files();
    void read_test_files();
    void read_param_file(BayesEstimators be);
    
    void deallocate();
    
};

#endif