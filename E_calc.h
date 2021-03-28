#ifndef MY_E_CALC_H
#define MY_E_CALC_H
#include <stdio.h>

//THIS BLOCK OF FUNCTIONS IS USED FOR CALCULAITION

double eCalculator(Cluster *C, Point c[], int k);

double sumCluster(Cluster* C, Point cent);

double distanceCalculator(Point *A, Point *B);

double pointSummation(Point *A, Point *B);

//THESE FUNCTIONS ARE USED FOR FINDING WHAT POINT SHOULD BE EXCHANGED

struct minimum Minimize(Cluster* C, Point* cent, int k);

struct minimum Minimum_find(Cluster* C, Point* cent, struct minimum min, int k, int currentClust);

//THESE FUNCTIONS ARE USED TO EXCHANGE POINTS BETWEEN CLUSTERS

Cluster* tightenCluster(Cluster* C, Point* cent, int k);

Cluster* assign_points(Point p, Cluster* C, Point cent[], int k);

Cluster* point_reassignment(Cluster* C, Point chosen, int start, int target, int k);

//BOOL FUNCTION USED TO COMPARE POINTS TO END KMEANS FUNCTION

//Check to end kmean function.
bool shouldHalt(struct point old_centroid[], struct point centroid[], int k);

//Used to compare individual points
bool compare_points(struct point a, struct point b);

#endif