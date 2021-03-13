/*This is the main file for testing kmeans algorithm
  Comments will act as placeholder.*/

#include<stdio.h>

struct point{  //Place holder for datastructure.
	/*centroids are double values so I feel
	  it would be simpiler to record all points
	  as doubles rather than undergo in conversions
	  Also I haven't looked at the breast cancer dataset
	  and there might be double values there as well
	  so this is just future proofing on multiple fronts.*/
	double x;
	double y;
}

struct cluster{
	/*This will act as a list of points.
	  It will also keep track of how many
	  points are in a cluster.
	  */
	int n; //Number of elements determined during randCluster and tightenCluster.
	point cluster[n];
}

//point initializer
point init_point(int x, int y);

//cluster initializer
cluster init_cluster(point c[]);

//kmeans algorithm...  I don't know if this is correct syntax but I'm just communicating a list of clusters is returned by this function.
cluster[] kmeans(point[] D, int k);

//Random Cluster function
cluster[] rand_Cluster(point[] D, int k);

//Check to end kmean function.
bool should_stop(point[k] old_centroids, point[k] centroids)

//Function to calculate cluster mean.
point[] get_centroid(cluster[] C);

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

//Function to calculate cluster mean.
point[] get_centroid(cluster[] C){}

//Function to reassign elements
cluster[] tighten_cluster(cluster[] C){}