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
    //size of cluster
    int n;
    point clu [n];
};

struct Centroid
{
    point cen [100];  //n determines the size of this array.
}
//generates centroid
point *Centroid(cluster * cluster, int num_data_points)
{
    int size, a;
    scanf ("%i", &size);
    double centroid [size];
    int num_data_points, num_clusters;

    //dividing the cluster's data points by the number of data points in the cluster
    for (int i = 0; i < num_clusters; i++;)
    {
        
        Centroid.x += cluster[i].x; 
        Centroid.y += cluster[i].y;
    } 
    centroid.x /= cluster.n; 
    centroid.y /= cluster.n;
    
    return centroid;

};