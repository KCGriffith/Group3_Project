#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <float.h>
#include "medistruct.h"
#include "E_calc.h"


//THIS BLOCK OF FUNCTIONS IS USED FOR CALCULAITION

double eCalculator(Cluster *C, Point c[], int k){ 
    double Total;
    Total = sumCluster(C, c[0]);
    for(int i = 1; i < k; i++){
        Total += sumCluster(C+i, c[i]);
    }
    return Total; 
}

double sumCluster(Cluster* C, Point cent){ //cent is our centroid
    double total = pow(2, distanceCalculator(&C->c[0], &cent)); //It is the value to be returned. 
    for(int l = 1; l < C->n; l++){
        total += pow(2, distanceCalculator(&C->c[l], &cent));
    }
    return total;
}

double distanceCalculator(Point *A, Point *B){
    return sqrt(pointSummation(A, B));
}

double pointSummation(Point *A, Point *B){
    double total;
    total = 0;
    for(int v = 0; v < 9; v++){
        double difference = fabs(A->att[v]) - (B->att[v]);
        total += pow(2, difference);
    }
    return total;
} 

//THESE FUNCTIONS ARE USED FOR FINDING WHAT POINT SHOULD BE EXCHANGED

struct minimum Minimize(Cluster* C, Point* cent, int k){
	double att[9] = {0, 0, 0, 0, 0, 0, 0, 0, 0};
	Point p = init_point(0, att, 0);
    struct minimum min = init_minimum(p, 0, 0, -1);
    struct minimum temp = init_minimum(p, 0, 0, -1);
    for(int l = 0; l < k; l++){
    	temp = Minimum_find(C+l, cent, min, k, l);
    	if(temp.ed > -1 && temp.ed < min.ed){
    		//min = temp;
    		min.chosen = temp.chosen;
            min.k_index = temp.k_index;
            min.k_target = temp.k_target;
            min.ed = temp.ed;
    	}
    }
    return min;
}

struct minimum Minimum_find(Cluster* C, Point* cent, struct minimum min, int k, int currentClust){
    double BestPlace[k];
    int loc;
    //Check if the cluster has one element
    if(C->n > 1){
    	for(int g = 0; g < C->n; g++){
    		for(int i = 0; i < k; i++){ //This creates a table of distances that we can choose from.
    			BestPlace[i] = distanceCalculator(&C->c[g], &cent[i]);
    		}
    		loc = 0;
    		for(int i = 1; i < k; i++){ //This is when we find the locaition of the best candidate.
    			if(BestPlace[i] < BestPlace[loc] && i != currentClust){ loc = i; }
    		}
        	if(loc != currentClust){
            	if(min.ed <= 0){
                	min = init_minimum(C->c[g], currentClust, loc, BestPlace[k]);
            	} else if(min.ed >= 0){
            		if(min.ed > BestPlace[k]){
                		min.chosen = C->c[g];
                		min.k_index = currentClust;
                		min.k_target = loc;
                		min.ed = BestPlace[loc];
            		}

            	}
        	}
    	}
    }

    return min;
}

//THESE FUNCTIONS ARE USED TO EXCHANGE POINTS BETWEEN CLUSTERS

Cluster* tightenCluster(Cluster* C, Point* cent, int k){
    struct minimum min = Minimize(C, cent, k);
    if(min.ed >= 0){
    	int k_index = min.k_index;
		int k_target = min.k_target;
    	C = point_reassignment(C, min.chosen, k_index, k_target, k);
    }

	return C;
}

Cluster* assign_points(Point p, Cluster* C, Point cent[], int k){
	double minimum = DBL_MAX;
	int target;
	Cluster clust[k];
	//This for loop finds the minimum.
	for(int i = 0; i < k; i++){
		double candidate = distanceCalculator(&p, &cent[i]);
		if(candidate < minimum){
			target = i;
			minimum = candidate;
		}
	}

	//This for loop finds the target location to allocate.
	for(int i = 0; i < k; i++){

		if(i != target){ //i is the other cluster.
			clust[i] = init_cluster((C+i)->c, (C+i)->n);
		} else {
			int v = (C+i)->n + 1, lastindex = v-1;
			Point* d = (Point*)calloc(v, sizeof(Point));
			for(int l = 0; l < (C+i)->n; l++){
				*(d+l) = (C+i)->c[l];
			}
			*(d+lastindex) = p;
			clust[i] = init_cluster(d, v);
		}
	}

	free(C);
	C = (Cluster*)calloc(k, sizeof(Cluster));
	for(int i = 0; i < k; i++){
		*(C+i) = clust[i];
	}

	return C;
}

Cluster* point_reassignment(Cluster* C, Point chosen, int start, int target, int k){
	int target_n, start_n;
	Cluster ctemp[k];

	target_n = ((C+target)->n)+1;
	start_n = ((C+start)->n)-1;
	for(int l = 0; l < k; l++){
		if(l == target){
			Point* D = (Point*)calloc(target_n, sizeof(Point));
			for(int i = 0; i < target_n; i++){
				if(i < target_n-1){
					*(D+i) = (C+target)->c[i];
				} else{
					*(D+i) = chosen;
				}
			}
			ctemp[target] = init_cluster(D, target_n);
		} else if(l == start){
			Point* D = (Point*)calloc(start_n, sizeof(Point));
			int v = 0, j = 0;
			for(int i = 0; i < (C+start)->n; i++){
				if(!compare_points((C+start)->c[v], chosen)){
					*(D+j) = (C+start)->c[v];
					v++;
					j++;
				} else {
					v++;
				}
			}
			ctemp[start] = init_cluster(D, start_n);
		} else {
			int v = (C+l)->n;
			int unchanged = l;
			Point* D = (Point*)calloc(v, sizeof(Point));
			for(int i = 0; i < v; i++){
				*(D+i) = (C+unchanged)->c[i];
			}
			ctemp[unchanged] = init_cluster(D, v);
		}
	}

	
	free(C);
	C = (Cluster*)calloc(k, sizeof(Cluster));
	for(int i = 0; i < k; i++){
		*(C+i) = ctemp[i];
	}

	return C;
}

//BOOL FUNCTION USED TO COMPARE POINTS TO END KMEANS FUNCTION

//Check to end kmean function.
bool shouldHalt(struct point old_centroid[], struct point centroid[], int k)
{
    for (int i = 0; i < k; i++)
    {
        if (!compare_points(old_centroid[i], centroid[i]))
        {
            return false;
        }
    }
    return true;
}

//Used to compare individual points
bool compare_points(struct point a, struct point b){
    //Returns whether two points are equal.
    for(int v = 0; v < 9; v++){
        if (a.att[v] != b.att[v]){
            return false;
        }
	}
	return true;
}