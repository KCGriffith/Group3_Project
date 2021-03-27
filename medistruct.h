#ifndef MY_MEDISTRUCT_H
#define MY_MEDISTRUCT_H

typedef struct point{
    int id_num; 
    double att[9];  //short for attributes. 
    int lable; 
} Point;

typedef struct cluster{
	/*This will act as a list of points.
	  It will also keep track of how many
	  points are in a cluster.
	  */
	int n; //Number of elements determined during randCluster and tightenCluster.
	struct point *c;
} Cluster;

typedef struct minimum{
    struct point chosen; 
    int k_index; //Keeps track of starting cluster. 
    int k_target; 
    double ed; //ed stands for Euclidean distance.
}Minimum;

//THIS BLOCK OF FUNCTIONS HANDLES PRINTING DIFFERENT STRUCT TYPES

//print cluster
void print_cluster(struct cluster *C, int k);

//print centroid
void print_centroid(Point* cent, int k);

//print points
void print_point(struct point *c);

//THESE FUNCTIONS ARE USED FOR EXTRACTING DATA 

struct point* read(FILE *inFile, Point* D, int *valid);

//THIS IS THE SECTION OF FUNCTIONS THAT HANDELS INITIALIZAITION

struct point init_point(int id_num, double att[], int lable);

//cluster initializer I don't know what this is for.
struct cluster init_cluster(struct point *D, int n);

//Initialize minimum
Minimum init_minimum(Point x, int a, int b, double dist);

#endif