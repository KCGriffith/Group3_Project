#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

typedef struct point{  //Place holder for datastructure.
	/*centroids are double values so I feel
	  it would be simpiler to record all points
	  as doubles rather than undergo in conversions
	  Also I haven't looked at the breast cancer dataset
	  and there might be double values there as well
	  so this is just future proofing on multiple fronts.*/
	double x;
	double y;
} Point;

typedef struct cluster{
	/*This will act as a list of points.
	  It will also keep track of how many
	  points are in a cluster.
	  */
	int n; //Number of elements determined during randCluster and tightenCluster.
	struct point *c;
} Cluster;

//point initializer
struct point init_point(double x, double y);

//ensure unique elements are picked
bool is_unique(int *past_pick, int pick, int n);

//cluster initializer
struct cluster init_cluster(struct point *D, int n);

//Random Cluster function
struct cluster* rand_Cluster(struct point *D, int n, int k);

//print cluster
void print_cluster(struct cluster *C, int k);

//print point support function for print_cluster
void print_point(struct point *c);

int main(void){
	time_t t;
	srand((unsigned)time(&t));
	int n = 8, k = 3;
	double x[8] = {2, 2, 8, 5, 7, 6, 1, 4};
	double y[8] = {10, 5, 4, 8, 5, 4, 2, 9};
	struct point D[n];

	printf("I've started.\n");

	for(int i = 0; i < n; i++){
		D[i] = init_point(x[i], y[i]);
	}

	struct cluster* C = calloc(k, sizeof(Cluster));

	C = rand_Cluster(D, n, k);

	print_cluster(C, k);

	return 0;
}

//point initializer
struct point init_point(double x, double y){
	struct point p = {x, y};
	return p;
}

//cluster initializer I don't know what this is for.
struct cluster init_cluster(struct point *D, int n){//This function takes a list of points and the size of that list
	struct point c[n];
	for(int i = 0; i <= n; i++){
		c[i] = D[i];
	}
	struct cluster Ci= {n, c};
	return Ci;
}

//Random Cluster function
struct cluster* rand_Cluster(struct point *D, int n, int k){
	int hm = 0; //how many?
	int lower = 2; //Gives the lower amount of elements that can be assigned to a cluster.
	int *last_picked, v = 0;  //Used to insure elements in cluster are distinct.
	struct cluster *clust = calloc(k, sizeof(Cluster)); //Return value
	struct point *temp; //The point array that will be passed in init_cluster

	printf("v = %d\n", v);

	for(int l = 0; l < k; l++){

		printf("n = %d\n", n);
		printf("l = %d\n", l);

		int whatleft = n - hm;

		hm = (rand() % (whatleft-lower+1))+lower;   //How many elements in the cluster

		for(int m = 0; m <= hm; m++){  //Creates array used
			
			
			temp = calloc(hm, sizeof(Point));

			int pick = rand() % n;

			printf("pick = %d\n", pick);
			printf("Am I stuck here?\n");

			while(is_unique(last_picked, pick, n) || (pick > n)) { pick = (rand()%n); }

			printf("No\n");

			//print_point(D+pick);

			*(temp+m) = *(D+pick);
			printf("I just gave temp a value from data points\n");
			//print_point(temp+m);
			printf("v = %d\n");
			*(last_picked+v) = pick;
			printf("Just updated list.");
			v += 1;
		}


		struct cluster a = {hm, temp};
		printf("I made it here.");
		*(clust + l) = a;
		free(temp);
		printf("Did I stop here?\n");
		temp = NULL;
		printf("No I made it here\n");
		

	}

	printf("Finished creating cluster\n");
	return clust;
}

//ensure unique elements are picked
bool is_unique(int *past_pick, int pick, int n){
	bool Unique = false;

	for(int i = 0; i <= n; i++){
		if(pick == *(past_pick+i) ){
			Unique = true;
		}
	}
	return Unique;
}

//print cluster
void print_cluster(struct cluster* C, int k){
	for(int i = 0; i <= k; i++){
		printf("cluster %d: ", i);
		for(int l = 0; l <= C->n; l++){
			print_point(C[i].c+l);
		}
		printf("\n");
	}
	printf("\n");
}

void print_point(struct point *c){
	struct point a = *c;
	printf("(%lf, %lf), ", a.x, a.y);
}
