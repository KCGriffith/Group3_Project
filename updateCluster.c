#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#incluce <stdbool.h>

typedef struct point{  //Place holder for datastructure.
	/*centroids are double values so I feel
	  it would be simpiler to record all points
	  as doubles rather than undergo in conversions
	  Also I haven't looked at the breast cancer dataset
	  and there might be double values there as well
	  so this is just future proofing on multiple fronts.*/
	double x;
	double y;
} Point;  //(x, y) <-- That is a point.

typedef struct cluster{
	/*This will act as a list of points.
	  It will also keep track of how many
	  points are in a cluster.
	  */
	int n; //Number of elements determined during randCluster and tightenCluster.
	struct point *c;
} Cluster;  //A cluster is a list of points {(x,y), (x,y)} For example and keeps trak of how many data points it holds which is n.  In this example n = 2.

float centroidPoint1(float aa, float bb)
{
    float centroidx = aa;
    float centroidy = bb;
}
float centroidPoint2(float cc, float dd)
{
    float centroidx = cc;
    float centroidy = dd;
}
float distance_calculator1(float aa, float bb, float x1, float y1)
{
    float distance1;
    distance1 = sqrt((aa - bb) * (aa - bb) + (x1 - y1) * (x1 - y1));
    return distance1;
}
float distance_calculator2(float aa, float bb, float x2, float y2) 
{
    float distance2;
     distance2 = sqrt((aa - bb) * (aa - bb) + (x2 - y2) * (x2 - y2));
    return distance2;
}
float distance_calculator3(float aa, float bb, float x3, float y3)
{
    float distance3;
     distance3 = sqrt((aa - bb) * (aa - bb) + (x3 - y3) * (x3 - y3));
    return distance3;
}
struct point UpdateClustering(int clustering[],
      double[] data[][], double[] means[][])
    {
      // update existing cluster clustering using data and means
      // proposed clustering would have an empty cluster: return false - no change to clustering
      // proposed clustering would be no change: return false, no change to clustering
      // proposed clustering is different and has no empty clusters: return true, clustering is changed
      int meansLength;
      int dataLength;
      int K = meansLength;
      int N = dataLength;

      int result[] = result[N];  // proposed new clustering (cluster assignments)
      bool change = false;  // is there a change to the existing clustering?
      int counts[] = result[K];  // check if new clustering makes an empty cluster

      for (int i = 0; i < N; ++i)  // make of copy of existing clustering
        result[i] = clustering[i];

      for (int i = 0; i < dataLength; ++i)  // each data item
      {
        double dists[] = new double[K];  // dist from curr item to each mean
        for (int k = 0; k < K; ++k)
          dists[k] = EucDistance(struct point[i], struct point[k]);

        int cid = ArgMin(dists);  // index of the smallest distance
        result[i] = cid;
        if (result[i] != clustering[i])
          change = true;  // the proposed clustering is different for at least one item
        ++counts[cid];
      }

      if (change == false)
        return false;  // no change to clustering -- clustering has converged

      for (int k = 0; k < K; ++k)
        if (counts[k] == 0)
          return false;  // no change to clustering because would have an empty cluster

      // there was a change and no empty clusters so update clustering
      for (int i = 0; i < N; ++i)
        clustering[i] = result[i];

      return true;  // successful change to clustering so keep looping
    }

//point initializer
struct point init_point(double x, double y){
	return (Point) {x, y};
}

//cluster initializer I don't know what this is for.
struct cluster init_cluster(struct point *D, int n){
	return (Cluster) {n, D};
}

int main()
{
    float result1,result2,result3,aa,bb, a, b, c, d, e, f;
    
    printf("\nEnter The Coordinates of Centroid A:\n");
    printf("\nX - Axis Coordinate: \n");
    scanf("%f", &aa);
    printf("\nY - Axis Coordinate: \n");
    scanf("%f", &bb);    
    printf("\nEnter The Coordinates of Point 1:\n");
    printf("\nx - Axis Coordinate:\n");
    scanf("%f", &a);
    printf("\nY - Axis Coordinate: \n");
    scanf("%f", &b);
    printf("\nEnter The Coordinates of Point 2:\n");
    printf("\nX - Axis Coordinate:\n");
    scanf("%f", &c);
    printf("\nY - Axis Coordinate: \n");
    scanf("%f", &d);
    printf("\nEnter The Coordinates of Point 3:\n");
    printf("\nX - Axis Coordinate:\n");
    scanf("%f", &e);
    printf("\nY - Axis Coordinate: \n");
    scanf("%f", &f);
    result1 = distance_calculator1(aa, bb, a, b);
    result2 = distance_calculator2(aa, bb, c, d);
    result3 = distance_calculator3(aa, bb, e, f);
    printf("\nDistance between Points A, B, and C: %f %f %f \n", result1, result2, result3);
    
    int n = 8, k = 3, hm = 0; //hm keeps track of how many data point were assigned to a cluster.
	double x[8] = {2, 2, 8, 5, 7, 6, 1, 4}; //These are test values meant to be turned into data points
	double y[8] = {10, 5, 4, 8, 5, 4, 2, 9};
    struct point *D = calloc(n, sizeof(Point));  //This will hold data points until we can distribute them into clusters.
    struct cluster *C = calloc(k, sizeof(Cluster));

	for(int i = 0; i < n; i++){
		*(D+i) = init_point(x[i], y[i]);
	}
    
    for(int i = 0; i < k; i++){
        if(i == k-1){
            *(C+i) = init_cluster(D, 4)
        }
        *(C+i) = init_cluster(D, 2)
        D += 2 //This changes the address pointed to from (D+0) to (D+2) as an example.
    }
    
    
    
    return 0;
}
