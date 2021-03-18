#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#incluce <stdbool.h>

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
    return 0;
}
