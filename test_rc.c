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

//if i have array of struck cluster C[k] and I fill in the values for all k clusters
//then C[0].n != C[1].n 
//If I edit C[0] then it won't change C[1]

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


//Takes a point and assigns it to a new cluster.
void point_reassignment(struct cluster start, struct cluster target, struct point chosen);

bool compare_points(struct point a, struct point b);

int main(void){
	time_t t;
	srand((unsigned)time(&t));
	int n = 8, k = 3;
	double x[8] = {2, 2, 8, 5, 7, 6, 1, 4};
	double y[8] = {10, 5, 4, 8, 5, 4, 2, 9};
	struct point *D = calloc(n, sizeof(Point));

	for(int i = 0; i < n; i++){
		*(D+i) = init_point(x[i], y[i]);
	}

	struct cluster *C = malloc(k * sizeof(Cluster));

	C = rand_Cluster(D, n, k);

	print_cluster(C, k);

	struct point find = {2, 10};
	int i = 0, l = 0, v = 0;

	for(i = 0; i < k; i++){
		for(l = 0; l < (C+i)->n; l++);
			struct point temp = (C+i)->c[l];
			if(compare_points(temp, find)){
				break;
			}
	}

	if(i == k-1){
		v = i - 1;
	} else {
		v = i + 1;
	}

	point_reassignment(*(C+i), *(C+v), find);

	print_cluster(C, k);

	return 0;
}

//point initializer
struct point init_point(double x, double y){
	printf("I did try to init the poin\n");
	return (Point) {x, y};
}

//cluster initializer I don't know what this is for.
struct cluster init_cluster(struct point *D, int n){
	return (Cluster) {n, D};
}

//Random Cluster function
struct cluster* rand_Cluster(struct point *D, int n, int k){
	int hm = 0, lower = 1, whatleft, *last_picked = calloc(n, sizeof(n)), v = 0, pick;  //These are the integer values
	struct cluster *clust = malloc(k * sizeof(Cluster)), tclust[k]; //These are the cluster variables
	struct point *temp = calloc(n, sizeof(Point)); //these are the point variables

	for(int z = 0; z < n; z++){  
		//An index cannot be negative so all of the 
		//initial values for last_picked needs to be set to a negative value.
		*(last_picked+z) = -1;
	}

	//We need to know how many data points are left
	//By the time we are ready to initialize the final cluster.
	whatleft = n;

	for(int l = 0; l < k; l++){

		//Utilizing pointer arithmatic to make sure that 
		//temp is not pointing at allocated memory that has a value.
		temp += hm;

		//hm = 0 when l = 0.
		//When l != 0 then hm has some non zero value.
		//We take the difference of whatsleft and hm
		//Gives an accurate assement of how many 
		//Data points are left.
		whatleft = whatleft - hm;

		//Upper is boundary value between indexes.
		int upper = (n-1) - hm;

		while(true){
			//It stands that the expression upper > whatleft can't be true.
			//I know the way I wrote it is weird but it made sense at the time.
			//If the expression mentioned earlier is true then we need to decrement upper
			//If we don't do this things go wrong understandably.
			if(whatleft - upper <= 0){
				upper -= 1;
			} else {break;}
		}

		//If we are at the last cluster then we need
		//To assign it with whatever data points are left
		//Otherwise we take a random value.
		if(l == k-1){
			hm = whatleft;
		} else {
			hm = (rand() % (upper-lower+1))+lower;   //How many elements in the cluster
		}

		//Now we need to pick what data points
		//Are assigned to the list of data points that
		//Goes to the current cluster.
		for(int m = 0; m < hm; m++){  

			//We are going to initially pick a random value.
			pick = rand() % n;

			while(is_unique(last_picked, pick, n) || (pick > n)) { pick = (rand()%n); } //If the index is not unique we take another random index until we find a unique 
			//We want temp at m to take the value from D at pick.
			*(temp+m) = *(D+pick);
			//We now add pick to the array of last picked.
			*(last_picked+v) = pick;
			v += 1;

		}

		//Now we initialize the cluster at l within the array.
		tclust[l] = init_cluster(temp, hm);

	}

	//Here we are just pointing whats in the array into the dynamic array.
	for(int i = 0; i < k; i++){
		*(clust+i) = tclust[i];
	}
	//The reason I have two different types of array has to do with the trouble I was
	//having with pointers.


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
void print_cluster(struct cluster *C, int k){
	//It turns out that all my problems stemed from this function.
	printf("I got here\n");
	for(int i = 0; i < k; i++){
		printf("cluster %d: ", i);
		for(int l = 0; l < (C+i)->n; l++){
			print_point((C+i)->c+l);
		}
		printf("\n");
	}
	printf("\n");
}

void print_point(struct point *c){
	printf("(%lf, %lf), ", c->x, c->y);
}

//Takes a point and assigns it to a new cluster.
void point_reassignment(struct cluster start, struct cluster target, struct point chosen){
	printf("I made it here.\n");
	printf("I'm gonna try printing a point ");
	print_point(&start.c[1]);
	printf("Did it work?\n");
	bool found = false;
	//First we need to assign the point to the new cluster
	target.n++;
	int target_n = target.n;

	target.c = realloc(target.c, sizeof(Point)*target_n);

	//For simplicity sake we put chosen at the end of target cluster's list of points.

	target.c[target_n-1] = init_point(chosen.x, chosen.y);

	printf("I stoped here\n");

	for(int i = 0; i < start.n; i++){
		if(compare_points(start.c[i], chosen)){ //We found where the point is in the start cluster.
			found = true;
		}
		if(found && i < start.n){
			start.c[i] = start.c[i+1];
		}
	}

	start.n--;
	start.c = (struct point *) realloc(start.c, start.n);
}

bool compare_points(struct point a, struct point b)
{
    //Returns whether two points are equal.
    if (a.x == b.x && a.y == b.y)
        return true;
    else
    {
        return false;
    }
}
