#ifndef _FILEREADER
#define _FILEREADER

#include <iostream>
#include <fstream>
#include <string>

using namespace std;
class FileReader
{
    
    string path;
public:
    FileReader(string path);
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
    
    void read_files();
    void deallocate();
    
};

#endif