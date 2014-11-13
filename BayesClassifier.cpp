//
//  BayesClassifier.cpp
//  BayesDigitRecognizer
//
//  Created by Mohamed Emad on 10/28/14.
//  Copyright (c) 2014 Mohamed Emad. All rights reserved.
//

#include "BayesClassifier.h"
#include "MatrixOperations.h"
#include "math.h"
#include "BayesCfg.h"

BayesClassifier::BayesClassifier(int num_classes)
{
    confusion_matrix = (int**)malloc(sizeof(int*)*num_classes);
    
    for(int i = 0;i<num_classes;i++)
    {
        confusion_matrix[i] = (int*)malloc(sizeof(int)*num_classes);
        for(int j = 0;j < num_classes;j++)
        {
            confusion_matrix[i][j] = 0;
        }
    }
}


int BayesClassifier::classify_single_image(BayesEstimators estimator, int* img, double* class_constants)
{
    //Classify a single image and return the recognized digit
    
    double max_posterior = -1000000;
    int chosen_class = -1;
    
    double* prec_img = (double*)malloc(estimator.num_dim*sizeof(double));
    for(int i = 0;i<estimator.num_dim;i++)
    {
        prec_img[i] = img[i]*1.0;
    }
    
    Eigen::VectorXf img_vec = MatrixOperations::transform_array_to_vector(estimator.num_dim, prec_img);
    
#ifdef POOLED_COV_MATRIX
    Eigen::MatrixXf cov_matrix =
    MatrixOperations::transform_array_to_matrix(estimator.num_dim, estimator.num_dim, estimator.covariance_matrix);
#endif
    
#ifdef POOLED_DIAG_COV_MATRIX
    Eigen::MatrixXf cov_matrix =
    MatrixOperations::transform_array_to_matrix(estimator.num_dim, estimator.num_dim, estimator.covariance_matrix);
#endif
    
    
    for(int i = 0; i < estimator.num_classes;i++)
    {
        
#ifdef FULL_CLASS_COV_MATRIX
        Eigen::MatrixXf cov_matrix =
        MatrixOperations::transform_array_to_matrix(estimator.num_dim, estimator.num_dim, estimator.class_cov[i]);
#endif
        
#ifdef SMOOTHED_COV
        Eigen::MatrixXf cov_matrix =
        MatrixOperations::transform_array_to_matrix(estimator.num_dim, estimator.num_dim, estimator.class_cov[i]);
#endif
        
#ifdef DIAG_CLASS_COV_MARTIX
        Eigen::MatrixXf cov_matrix =
        MatrixOperations::transform_array_to_matrix(estimator.num_dim, estimator.num_dim, estimator.class_cov[i]);
#endif
        
        Eigen::VectorXf mean_vec = MatrixOperations::transform_array_to_vector(estimator.num_dim, estimator.mean_values[i]);

        double posterior = class_constants[i] - ( 0.5*((img_vec - mean_vec).transpose()*cov_matrix)*(img_vec - mean_vec) );
        
        if(posterior > max_posterior)
        {
            chosen_class = i;
            max_posterior = posterior;
        }
    }
    
    return chosen_class;
}


void BayesClassifier::process_test_data(BayesEstimators estimators, int** test_imgs, int* test_labels, int num_test_imgs)
{
    
    int numErrors = 0;
    //2. Classify images using bayes estimators
    
    double* class_constants = (double*)malloc(sizeof(double)*estimators.num_classes);
    
#ifdef POOLED_COV_MATRIX
    estimators.calculate_pooled_cov_inverse();
#endif
    
#ifdef POOLED_DIAG_COV_MATRIX
    estimators.calculate_pooled_cov_inverse();
#endif
    
#ifdef FULL_CLASS_COV_MATRIX
    estimators.calculate_class_cov_inverse();
#endif

#ifdef SMOOTHED_COV
    estimators.calculate_class_cov_inverse();
#endif
    
#ifdef DIAG_CLASS_COV_MARTIX
    estimators.calculate_class_cov_inverse();
#endif
    
    for(int i=0;i<estimators.num_classes;i++)
    {
        double class_constant = log10f(estimators.priors[i]);
        class_constants[i] = class_constant;
    }
    printf("Classifying test data...\n");
    for(int i=0;i<num_test_imgs;i++)
    {
        int KgivenX = classify_single_image(estimators, test_imgs[i], class_constants);
        confusion_matrix[test_labels[i]%10][KgivenX]++;
       
        if(KgivenX != (test_labels[i]%10)){
            numErrors++;
        }
    }
    //3. Fill confusion matrix with values
    
    
    //4. Calculate error rate ( < 20%)
    double errorRate = numErrors/(num_test_imgs*1.0);
    printf("Error Rate: %f%%\n",errorRate*100);
    printf("Confusion Matrix: \n");
    for(int i = 0;i<estimators.num_classes;i++)
    {
        for(int j = 0;j<estimators.num_classes;j++)
        {
            printf("%d\t\t\t",confusion_matrix[i][j]);
        }
        
        printf("\n");
    }
}