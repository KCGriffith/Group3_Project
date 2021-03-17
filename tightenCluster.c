#include <stdio.h>
#include <math.h>

struct point
{
    double x;
    double y;
}

}
struct EucDistance(double[] item, double[] mean)
    {
      // Euclidean distance from item to mean
      // used to determine cluster assignments
      double sum = 0.0;
      for (int j = 0; j < itemLength; ++j)
        sum += (item[j] - mean[j]) * (item[j] - mean[j]);
      return sqrt(sum);
    }
    //determines the smallest distance between centroids
struct ArgMin(double[] v)
    {
      int minIdx = 0;
      double minVal = v[0];
      for (int i = 0; i < vLength; ++i)
      {
        if (v[i] < minVal)
        {
          minVal = v[i];
          minIdx = i;
        }
      }
      return minIdx;
    }
struct ComputeWithinClusterSS(double[][] data,
      double[][] means, int[] clustering)
    {
      // compute total within-cluster sum of squared differences between 
      // cluster items and their cluster means
      // this is actually the objective function, not distance
      double sum = 0.0;
      for (int i = 0; i < dataLength; ++i)
      {
        int cid = clustering[i];  // which cluster does data[i] belong to?
        sum += SumSquared(data[i], means[cid]);
      }
      return sum;
    }
struct UpdateClustering(int[] clustering,
      double[][] data, double[][] means)
    {
      // update existing cluster clustering using data and means
      // proposed clustering would have an empty cluster: return false - no change to clustering
      // proposed clustering would be no change: return false, no change to clustering
      // proposed clustering is different and has no empty clusters: return true, clustering is changed

      int K = meansLength;
      int N = dataLength;

      int[] result = new int[N];  // proposed new clustering (cluster assignments)
      bool change = false;  // is there a change to the existing clustering?
      int[] counts = new int[K];  // check if new clustering makes an empty cluster

      for (int i = 0; i < N; ++i)  // make of copy of existing clustering
        result[i] = clustering[i];

      for (int i = 0; i < dataLength; ++i)  // each data item
      {
        double[] dists = new double[K];  // dist from curr item to each mean
        for (int k = 0; k < K; ++k)
          dists[k] = EucDistance(data[i], means[k]);

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
    
    //test Euclidean function
int main() {
    double *centroid;
        int size;
        int i;
        printf(" Enter The size of the array \n");
        scanf("%d",&size);
        centroid  = (double *)malloc(size * sizeof(double));
        printf("Assigning the values using index \n");
        for(i = 0; i < size; i++)
        {
                *(centroid + i) = 4000 + i;
        }

        /* Printing the array using Index */
        for(i = 0; i < size; i++)
        {
                printf(" centroid[%d] = %f\n",i,*(centroid + i));
        }
}
