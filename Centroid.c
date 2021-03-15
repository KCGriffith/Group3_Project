#include <stdio.h>

struct point
{
    double x, y;
    num;
};

struct Cluster
{
    //number of cluster
    int n;
    int a;
    // number of elements in cluster
    struct point *clu;
};

struct Centroid
{
    // centroid is of point data type
    struct point cen;
}

//generates centroid
struct point Centroid (struct point *cluster, struct point cen, int n)
{

    //dividing the cluster's data points by the number of data points in the cluster
    for (int i = 0; i < n; i++)
    {
        cen.x += cluster[i].x;
        cen.y += cluster[i].y;
    } 

    //work in progress
    cen.x /= malloc_size(*cluster).n; 
    cen.y /= cluster.n;
    
    return cen;
};