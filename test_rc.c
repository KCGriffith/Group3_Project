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
	point[] cluster;
}

//point initializer
point init_point(int x, int y);

//ensure unique elements are picked
bool is_unique(int[] past_pick, pick);

//cluster initializer
cluster init_cluster(point[] D, int n);

//Random Cluster function
cluster[] rand_Cluster(point[] D, int k);

//print cluster
void print_cluster(cluster[] C);

main(void){
	int n = 8, k = 3;
	int x[] = [2, 2, 8, 5, 7, 6, 1, 4];
	int y[] = [10, 5, 4, 8, 5, 4, 2, 9];
	point D[n];

	for(int i, i <= n, i++){
		D[i] = init_point(x[i], y[i]);
	}

	C = rand_Cluster(D);

	print_cluster(C);

	return 0;
}

//point initializer
point init_point(int x, int y){
	point p = {1, 0};
	return p;
}

//cluster initializer
cluster init_cluster(point[] D, int n){
	point c[n];
	for(int i = 0; i <= n; i++){
		c[i] = D[i];
	}
	return {n, c};
}

//Random Cluster function
cluster[] rand_Cluster(point[] D, int k){
	int n = sizeof(D);
	int hm = 0; //how many?
	int lower = 2; //Gives the lower amount of elements that can be assigned to a cluster.
	int last_picked[n], v = 0;  //Used to insure elements in cluster are distinct.
	cluster clust[k]; //Return value
	for(int l = 0, l <= k, l++){
		hm = (rand() % (n-hm));   //How many elements in the cluster
		for(int m = 0, m <= hm, m++){  //Creates array used 
			point temp[hm];       //The point array that will be passed in init_cluster
			int pick = (rand() % n)
			while is_unique(pastpicked, pick){
				pick = (rand() % n);
			}
			temp[m] = D[pick];
			last_picked[v] = pick;
			v += 1;
		}
		clust[l] = init_cluster(temp, hm);

	}
	return clust;
}

//ensure unique elements are picked
bool is_unique(int[] past_pick, pick){
	int n = sizeof(past_pick);
	for(int i; i <= n; i++){
		if(pick == past_pick[i]){
			return false;
		}
	}
	return true;
}

//print cluster
void print_cluster(cluster[] C){
	for(int i = 0; i <= sizeof(C); i++){
		for(int l = 0; l <= C.n; l++){
			printf("(%d, %d), ", *C[i].(cluster+l).x, *C[i].(cluster+l).y);
		}
	}
	printf("\n");
}