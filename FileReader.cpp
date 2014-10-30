#include "FileReader.h"
#include <sstream>
using namespace std;
FileReader::FileReader(string document_path, string test_data_path,string params_path)
{
    path=document_path;
    test_path = test_data_path;
    param_path = params_path;
}


//Free the memory
void FileReader::deallocate()
{
    for(int i=0;i<num_imgs;i++)
    {
        delete[] image_vectors[i];
    }
}
void FileReader::read_files()
{
    num_imgs = 7291;
    
    int imgs_read = -1;
    int img_width = 0;
    
    string line;
    image_vectors = (int**)malloc(sizeof(int*)*num_imgs);
    image_labels = (int*) malloc(sizeof(int)*num_imgs);
    
    ifstream myfile (path);
    if (myfile.is_open())
    {
        int i=0;
        while ( getline (myfile,line))
        {
            stringstream ssin(line);
            
            if( i == 0 )
            {
                
                ssin >> num_labels;
                
                i++;
                continue;
            }
            
            if( i == 1)
            {
               
                ssin >> num_dim;
                
                
                i++;
                continue;
            }
            
            if(line.size() < 10)
            {
                imgs_read++;
                
                ssin >> image_labels[imgs_read];
                
                image_vectors[imgs_read] = (int*)malloc(sizeof(int)*num_dim);
                img_width = 0;
                
                continue;
            }
            
            int width = 0;
            while (ssin.good() && width < 16)
            {
                ssin >> image_vectors[imgs_read][img_width];
                
                ++width;
                ++img_width;
            }
            
            i++;
            //printf("%s\n",line.c_str());
            
        }
        myfile.close();
        printf("%d images read successfully\n",imgs_read+1);
        
    }
    
    else printf("Unable to open file\n");
}

void FileReader::read_test_files()
{
    num_test_imgs = 2007;
    
    int imgs_read = -1;
    int img_width = 0;
    
    string line;
    test_imgs = (int**)malloc(sizeof(int*)*num_test_imgs);
    test_labels = (int*) malloc(sizeof(int)*num_test_imgs);
    
    ifstream myfile (test_path);
    if (myfile.is_open())
    {
        int i=0;
        while ( getline (myfile,line))
        {
            stringstream ssin(line);
            
            if( i == 0 )
            {
                
                ssin >> num_labels;
                
                i++;
                continue;
            }
            
            if( i == 1)
            {
                
                ssin >> num_dim;
                
                
                i++;
                continue;
            }
            
            if(line.size() < 10)
            {
                imgs_read++;
                
                ssin >> test_labels[imgs_read];
                
                test_imgs[imgs_read] = (int*)malloc(sizeof(int)*num_dim);
                img_width = 0;
                
                continue;
            }
            
            int width = 0;
            while (ssin.good() && width < 16)
            {
                ssin >> test_imgs[imgs_read][img_width];
                
                ++width;
                ++img_width;
            }
            
            i++;
            //printf("%s\n",line.c_str());
            
        }
        myfile.close();
        printf("%d images read successfully\n",imgs_read+1);
        
    }
    
    else printf("Unable to open file\n");
}

void FileReader::read_param_file(BayesEstimators be)
{
    
    
    string line;
    int curr_class = -1;
    int reading_index = 0;
    
    ifstream myfile (param_path);
    if (myfile.is_open())
    {
        int i=0;
        while ( getline (myfile,line))
        {
            stringstream ssin(line);
            
            if( i == 0 )
            {
                i++;
                continue;
            }
            
            if( i == 1)
            {
                
                ssin >> num_labels;
                
                
                i++;
                continue;
            }
            
            if(i == 2)
            {
                ssin >> num_dim;
                
                
                i++;
                continue;
            }
            
            switch (reading_index)
            {
                case 0:
                    ssin >> curr_class;
                    reading_index++;
                    break;
                case 1:
                    ssin >> be.priors[curr_class];
                    reading_index++;
                    break;
                case 2:
                    for(int k = 0;k<num_dim;k++)
                    {
                        ssin >> be.mean_values[curr_class][k];
                    }
                    reading_index++;
                    break;
                case 3:
                    for(int k = 0;k<num_dim;k++)
                    {
                        ssin >> be.variance_values[k];
                    }
                    reading_index = 0;
                    break;
                default:
                    break;
            }
            
            
            i++;
            //printf("%s\n",line.c_str());
            
        }
        myfile.close();
        printf("Params read successfully\n");
        
    }
    
    else printf("Unable to open file\n");
}


