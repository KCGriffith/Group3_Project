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
    int size;
    // number of elements in cluster
    struct point *clu;
};

struct Centroid
{
    // centroid is of point data type
    struct point cen;
}

//generates centroid
struct point Centroid (struct point *cluster, struct point cen, int n, int num)
{
    //dividing the cluster's data points by the number of data points in the cluster
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < num; j++)
        {
            cen.x += cluster[i].x;
            cen.y += cluster[i].y;
        }
        struct point *cluster[i] = new int temp1[num];
        struct point *cluster[i] = new int temp2[num];
        cen.x /= sizeOf.(temp1);
        cen.y /= sizeOf.(temp2);
    }
    
    
    return cen;
};