#include "FileReader.h"
#include <sstream>
using namespace std;
FileReader::FileReader(string document_path)
{
    path=document_path;
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

