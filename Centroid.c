#include <stdio.h>
using namespace std;

//

struct point
{
    int x, y;
    num;
};

struct Cluster
{
    point clu [100];
};

struct Centroid
{
    point cen [100];
}
//generates centroid
point *Centroid(point * cluster, int num_data_points)
{
    int size, a;
    scanf ("%i", &size);
    double centroid [size];
    int num_data_points, num_clusters;

    //initalization of data points x , y and cluster
    for (int i = 0 ; i < num_data_points ; i++)
    {
        centroid[i].num = 0 ;
        centroid[i].x = 0;
        centroid[i].y = 0;  
    }
    //call random cluster function that assigns data points to random cluster
    randomCluster();

    //dividing the cluster's data points by the number of data points in the cluster
    for (int i = 0; i < num_clusters; i++;)
    {
        centroid[i].x = centroids[i].x / centroids[i].num;
        centroid[i].y = centroids[i].y / centroids[i].num;   
    }  
    
    //put nearest data points to one cluster
    for (int i = 0 ; i < num_points; i++)
    {
        
    }


    return centroid;

};