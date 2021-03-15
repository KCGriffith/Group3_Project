#include <stdio.h>

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
