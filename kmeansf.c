#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <float.h>
#include "medistruct.h"
#include "E_calc.h"
#include "kmeansf.h"

//THIS IS THE MAIN KMEANS ALGORITHM
struct cluster* kmeans(struct point* D, int n, int k){
	time_t t;
	srand((unsigned)time(&t));
	int pick, last_picked[n];  //These insure unique values go into the clusters.
	double E = DBL_MAX, E_previous = DBL_MAX;
	//Initializaition
	struct cluster* C = (Cluster*)calloc(k, sizeof(Cluster));
	struct point centroid[k]; //This initializes the centroid list.

	for(int z = 0; z < n; z++){
		//An index cannot be negative so all of the 
		//initial values for last_picked needs to be set to a negative value.
		last_picked[z] = -1;
	}

	for(int i = 0; i < k; i++){
		//We are going to initially pick a random value.
		pick = rand() % n;

		while(is_unique(last_picked, pick, n) || (pick > n)) { pick = (rand()%n); } //If the index is not unique we take another random index until we find a unique 
		//We want temp at m to take the value from D at pick.
		centroid[i] = *(D+pick);
		//printf("THIS IS THE FIRST CENTROID!\n");
		//print_point

		//We now add pick to the array of last picked.
		last_picked[i] = pick;
		*(C+i) = init_cluster(&centroid[i], 1);
	}
	
	//Book Keeping
	struct point old_centroids[k], temp_centroids[k];
	int w = 0, o = 3;
	while(!shouldHalt(old_centroids, centroid, k)){
		//printf here
		Cluster* temp = (Cluster*)calloc(k, sizeof(Cluster));
		//E_previous = E;
        for(int i = 0; i < k; i++){
            old_centroids[i] = centroid[i];
        }

		while(is_unique(last_picked, w, n) && w < n) { w++; }

        //We need to know when all points have been assigned to a cluster.
        if(w < n){	
        	C = assign_points(D[w], C, centroid, k);
        	
        	last_picked[o] = w;
        	w++;
        	o++;
        	for(int i = 0; i < k; i++){
				centroid[i] = get_centroid((C+i)->c, (C+i)->n);
			}
			
        } else { //If we have assigned the points we need to adjust the clusters.
        	//Reassign objects to the cluster.

			for(int i = 0; i < k; i++){ //This allows us to see if we improve the cluster without causing change.
				*(temp+i) = *(C+i);
			}

			temp = tightenCluster(temp, centroid, k);
			
			for(int i = 0; i < k; i++){
				temp_centroids[i] = get_centroid((temp+i)->c, (temp+i)->n);
			}
			
			E = eCalculator(temp, temp_centroids, k);
			if(E < E_previous){  //If the score is improved then we change the main cluster
				for(int i = 0; i < k; i++){
					*(C+i) = *(temp+i);
				}

				for(int i = 0; i < k; i++){
					centroid[i] = get_centroid((C+i)->c, (C+i)->n);
				}

			}//We are done otherwise.

			free(temp);
		}
	}
	//print_centroid(centroid, k);
	return C;
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
//THIS BLOCK OF FUNCTIONS USED TO UPDATE CENTROIDS

//centroid function to calculate centroid
struct point get_centroid(struct point* c, int n){ 
    //centroid as a point 
    struct point cen;
    if(n == 1){
        for(int v = 0; v < 9; v++){
            cen.att[v] = c->att[v];
        }
        return cen;
    } 
    //@@ -17,8 +17,8 @@ struct point centroid(struct point c[], int n) 
    //printf("We are iterating through %d elements.\n", n); 
    for(int v = 0; v < 9; v++){
            cen.att[v] = (c)->att[v];
        }
    for (int j = 0; j < n ; j++){
        for(int v = 0; v < 9; v++){
            cen.att[v] += (c+j)->att[v];
        } 
    } 
    //average of all the data points 
    for (int j = 0; j < n ; j++){
        for(int v = 0; v < 9; v++){
            cen.att[v] = cen.att[v]/n;
        } 
    } 
    //return centroid 
    return cen; 
}


//USED TO DETERMINE ACCURACY OF THE KMEANS ALGORITHM
double Accuracy(Cluster* C){
    double TP, FP, TN, FN;
    TP = 0;
    FP = 0;
    TN = 0;
    FN = 0;
    for(int i = 0; i < C->n; i++){
    	switch(C->c[i].lable){
    		case 2:
    			FP = FP + 1;
    		case 4:
    			TP = TP + 1;
    	}
    }
    for(int i = 0; i < (C+1)->n; i++){
    	switch((C+1)->c[i].lable){
    		case 2:
    			FN = FN + 1;
    		case 4:
    			TN = TN + 1;
    	}
    }
    double ALL = C->n + (C+1)->n;
    return (TP+TN)/ALL;
}