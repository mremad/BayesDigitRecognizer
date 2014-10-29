#include "FileReader.h"
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
    string line;
    image_vectors = (int**)malloc(sizeof(int*)*num_imgs);
    image_labels = (int*) malloc(sizeof(int)*num_imgs);
    
    ifstream myfile (path);
    if (myfile.is_open())
    {
        int i=0;
        while ( getline (myfile,line))
        {
            //Read test/training file, and dump its contents in
            //the corresponding data arrays
            
            //printf("%s\n",line.c_str());
            i++;
        }
        myfile.close();
        printf("%d Documents read successfully\n",i);
    }
    
    else printf("Unable to open file\n");
}

