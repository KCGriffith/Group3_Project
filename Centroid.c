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
    struct point [a] clu;
};

struct Centroid
{
    // centroid is of point data type
    struct point cen;
}

//generates centroid
struct point Centroid (struct point clu[int n], int n)
{

    //dividing the cluster's data points by the number of data points in the cluster
    for (int i = 0; i < n; i++;)
    {
        cen.point.x += cluster[i].x; 
        Centroid.y += cluster[i].y;
    } 
    centroid.x /= cluster.n; 
    centroid.y /= cluster.n;
    
    return centroid;
};