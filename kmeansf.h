#ifndef MY_KMEANSF_H
#define MY_KMEANSF_H
#include "medistruct.h"

//extern Point Point;
//extern Cluster Cluster;

//THIS IS THE MAIN KMEANS ALGORITHM
struct cluster* kmeans(struct point* D, int n, int k);

//ensure unique elements are picked
bool is_unique(int *past_pick, int pick, int n);

//THIS BLOCK OF FUNCTIONS USED TO UPDATE CENTROIDS

//centroid function to calculate centroid
struct point get_centroid(struct point* c, int n);

//USED TO DETERMINE ACCURACY OF THE KMEANS ALGORITHM
double Accuracy(Cluster* C);

#endif