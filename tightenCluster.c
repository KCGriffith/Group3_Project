#include <stdio.h>

using namespace std;

struct point{  //Place holder for datastructure.
	/*centroids are double values so I feel
	  it would be simpiler to record all points
	  as doubles rather than undergo in conversions
	  Also I haven't looked at the breast cancer dataset
	  and there might be double values there as well
	  so this is just future proofing on multiple fronts.*/
	int x;
    int y;
    double x;
	double y;
    num;
}

struct cluster{
	/*This will act as a list of points.
	  It will also keep track of how many
	  points are in a cluster.
	  */
	int n; //Number of elements determined during randCluster and tightenCluster.
	point cluster[n];
    int a;
    point cluster[a];
}

//Function to reassign elements
cluster[] tighten_cluster(cluster[] C);

int main(void){
	//For the time being ignore the fact C has to be initialized as a list.
	//At least until the data structure is in place.
	int k, n = /*Input data's size*/;
	point D[n] = [initPoint(/*Input data*/)*n];
	cluster result;

	printf("Input number of clusters: ");
	scanf("%d", &k);
	printf("\n");

	result = kmeans(D, k);

	printf(/*We need to workout how to output results*/);

	return 0;

}

cluster[] kmeans(point[] D, int k){
	//Initializaition
	cluster[] C = rand_Cluster(D, k);
	point centroids[k] = get_centroid(C);

	//Book Keeping
	point old_centroids[k] = void;

	while(!should_stop(old_centroids, centorids)){

		old_centroids = controids;

		//Reassign objects to the cluster.

		C = tighten_cluster(C);

		//Update the cluster means

		centroids = get_centroid(C);

	}
	return C;
}

//Random Cluster function
cluster[] rand_Cluster(point[] D, int k){}

//Check to end kmean function.
bool should_stop(point[k] old_centroids, point[k] centroids){
	if(old_centroids == void) return false;
	if(old_centroids == centroids) return true;  //== operator needs an override but it depends on the data structure we use.
	return false;
}
public void Cluster()
    {
      // init clustering[] and means[][] 
      // loop at most maxIter times
      //   update means using curr clustering
      //   update clustering using new means
      // end-loop
      // if clustering is new best, update clustering, means, counts, wcss

      int[] currClustering = new int[this.N];  // [0, 0, 0, 0, .. ]

      double[][] currMeans = new double[this.K][];
      for (int k = 0; k < this.K; ++k)
        currMeans[k] = new double[this.dim];

      if (this.initMethod == "plusplus")
        InitPlusPlus(this.data, currClustering, currMeans, this.rnd);
      else
        throw new Exception("not supported");

      bool changed;  //  result from UpdateClustering (to exit loop)
      int iter = 0;
      while (iter < this.maxIter)
      {
        UpdateMeans(currMeans, this.data, currClustering);
        changed = UpdateClustering(currClustering, 
          this.data, currMeans);
        if (changed == false)
          break;  // need to stop iterating
        ++iter;
      }

      double currWCSS = ComputeWithinClusterSS(this.data,
        currMeans, currClustering);
      if (currWCSS < this.wcss)  // new best clustering found
      {
        // copy the clustering, means; compute counts; store WCSS
        for (int i = 0; i < this.N; ++i)
          this.clustering[i] = currClustering[i];

        for (int k = 0; k < this.K; ++k)
          for (int j = 0; j < this.dim; ++j)
            this.means[k][j] = currMeans[k][j];

        this.counts = ComputeCounts(this.K, currClustering);
        this.wcss = currWCSS;
      }

    } // Cluster()
    
    private static bool UpdateClustering(int[] clustering,
      double[][] data, double[][] means)
    {
      // update existing cluster clustering using data and means
      // proposed clustering would have an empty cluster: return false - no change to clustering
      // proposed clustering would be no change: return false, no change to clustering
      // proposed clustering is different and has no empty clusters: return true, clustering is changed

      int K = means.Length;
      int N = data.Length;

      int[] result = new int[N];  // proposed new clustering (cluster assignments)
      bool change = false;  // is there a change to the existing clustering?
      int[] counts = new int[K];  // check if new clustering makes an empty cluster

      for (int i = 0; i < N; ++i)  // make of copy of existing clustering
        result[i] = clustering[i];

      for (int i = 0; i < data.Length; ++i)  // each data item
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
