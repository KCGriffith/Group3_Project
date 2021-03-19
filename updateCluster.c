#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>

typedef struct point{
	double x;
	double y;
} point;  //(x, y) <-- That is a point.

typedef struct cluster{
	int n; //Number of elements determined during randCluster and tightenCluster.
	struct point *c;
} cluster;

struct point pointer(struct point *c [], int n)
{
    //point
    struct point pt;

    //initialize point
    pt.x = 0, pt.y = 0;

    for (int j = 0; j < n ; j++)
    {
        pt.x += (c[j]->x);
        pt.y += (c[j]->y);
    }

    //average of all the data points
    pt.x = pt.x / n;
    pt.y = pt.y / n;
    
    //return centroid
    return pt;
}

double pointSummation(point *A, point *B){
    return pow(2, (A-B)) + pow(2, (A-B));
}

double distanceCalculator(point *A, point *B){
    return sqrt(pointSummation(A, B));
}

double sumCluster(cluster* C, point *cent){ //cent is our centroid  
    double total; //It is the value to be returned. 
    for(int l = 0; l < C->n; l++){
        total += pow(2, distanceCalculator((C+l)->c, cent));
    }
    return total;
}

double eCalculator(cluster *C, point *c, int k){ 
    double Total; 
    for(int i = 0; i < k; i++){
        Total += sumCluster(C+i, c+i);
    }
    return Total; 
}
int main() {
    int size;
    printf("Insert the number of points: \n");
    scanf("%d", &size);
    struct point c[size];
    for (int i = 0; i < size; i++)
    {
        printf("Enter x and y\n");
        scanf("%lf %lf", &c[i].x, &c[i].y);
    }
   
}
 /*struct point UpdateClustering(int clustering[],
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

*int main()
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
    printf("\nDistance between Points A, B, and C: %f %f %f \n", result1, result2, result3);*/
    
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
