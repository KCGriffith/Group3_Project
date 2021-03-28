/*This is the main file for testing kmeans algorithm
  Comments will act as placeholder.*/

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <float.h>

typedef struct point{
    int id_num; 
    double att[9]; //short for attributes.
    int lable;
} Point;

typedef struct cluster{
	/*This will act as a list of points.
	  It will also keep track of how many
	  points are in a cluster.
	  */
	int n; //Number of elements determined during randCluster and tightenCluster.
	struct point *c;
} Cluster;

typedef struct minimum{
    struct point chosen; 
    int k_index; //Keeps track of starting cluster. 
    int k_target; 
    double ed; //ed stands for Euclidean distance.
}Minimum;

//point initializer
struct point init_point(int id_num, double att[], int lable);

//ensure unique elements are picked
bool is_unique(int *past_pick, int pick, int n);

//cluster initializer
struct cluster init_cluster(struct point *D, int n);

//Initialize minimum
Minimum init_minimum(Point x, int a, int b, double dist);

//kmeans algorithm...
struct cluster* kmeans(Point* D, int n, int k);

//print cluster
void print_cluster(struct cluster *C, int k);

//print point support function for print_cluster
void print_point(struct point *c);

//Used to print centroids
void print_centroid(Point* cent, int k);

//Check to end kmean function.
bool shouldHalt(struct point old_centroid[], struct point centroid[], int k);

//Used to compare two points to one another.
bool compare_points(struct point a, struct point b);

//centroid function to calculate centroid
struct point get_centroid(struct point *c, int n);

//Inner exrpession of distance formula
double pointSummation(Point *A, Point *B);

//Euclidian distance formula.
double distanceCalculator(Point *A, Point *B);

//Inner expreesion of partitioning method
double sumCluster(Cluster* C, Point cent);

//Formula to find E
double eCalculator(Cluster *C, Point c[], int k);

//Used to find points that are closer to other centroids
struct minimum Minimum_find(Cluster* C, Point* cent, struct minimum min, int k, int currentClust);

//Used to cycle through clusters while calling minimum find.
struct minimum Minimize(Cluster* C, Point* cent, int k);

//This assigns new points to clusters.
Cluster* assign_points(Point p, Cluster* C, Point cent[], int k);

//This edits clusters that went through the list of points D.
Cluster* tightenCluster(Cluster* C, Point* cent, int k);

//Function to reassign elements
Cluster* point_reassignment(Cluster* C, Point chosen, int start, int target, int k);

//Used to determine accuracy.
double Accuracy(Cluster* C);

//This is used to recieve input.
struct point* read(FILE *inFile, Point* D, int *valid);

int main(int argc, char *argv[])
{
	//For the time being ignore the fact C has to be initialized as a list.
	//At least until the data structure is in place.
	FILE *inFile;
	struct point *p = (Point*)calloc(699, sizeof(Point));
	int valid = 699;
	p = read(inFile, p, &valid);
	Cluster* result = (Cluster*)calloc(2, sizeof(Cluster));
	int k = 2;

	struct point *D = (Point*)calloc(valid, sizeof(Point));
	bool val;
	int count = 0;

	for(int i = 0; i < valid; i++)
    {
        for(int l = 0; l < 9; l++)
        {
            if((p+count)->att[l] == 0)
            {
                val = false;
                count++;
                break;
            }
            else 
            { 
                val = true;
            }
        }
        if(val)
        {
        	*(D+i) = init_point((p+count)->id_num, (p+count)->att, (p+count)->lable);
        }
    }

	result = kmeans(D, valid, k);
	
	printf("This clustering accuracy = %lf\n", Accuracy(result));

	return 0;
}

struct cluster* kmeans(struct point* D, int n, int k){
	time_t t;
	srand((unsigned)time(&t));
	int pick, last_picked[n];
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
		//We now add pick to the array of last picked.
		last_picked[i] = pick;
		*(C+i) = init_cluster(&centroid[i], 1);
	}
	
	//Book Keeping
	struct point old_centroids[k], temp_centroids[k];
	int w = 0, o = 3;
	while(!shouldHalt(old_centroids, centroid, k)){
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
	print_centroid(&centroid, k);
	return C;
}


//point initializer
struct point init_point(int id_num, double att[], int lable){
    Point temp; 
    temp.id_num = id_num;
    for(int i = 0; i < 9; i++){
        temp.att[i] = att[i];
    }
    temp.lable = lable;
    return temp;
}

//cluster initializer I don't know what this is for.
struct cluster init_cluster(struct point *D, int n){
	return (Cluster) {n, D};
}

//Initialize minimum
Minimum init_minimum(Point x, int a, int b, double dist){
	return (Minimum){x, a, b, dist};
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
	for(int i = 0; i < k; i++){
		printf("cluster %d: ", i+1);
		for(int l = 0; l < (C+i)->n; l++){
			print_point((C+i)->c+l);
		}
		printf("\n");
	}
	printf("\n");
}

void print_point(struct point *c){
    printf("(%d ", c->id_num);
    for(int v = 0; v < 9; v++){
        printf("%lf, ", c->att[v]);
    }
    printf("%d)", c->lable);
}

void print_centroid(Point* cent, int k){
	printf("{");
	for(int i = 0; i < k; i++){
		print_point(cent+i);
	}
	printf("}");
}

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

double pointSummation(Point *A, Point *B){
    double total;
    for(int v = 0; v < 9; v++){
        double difference = fabs(A->att[v]) - (B->att[v]);
        total += pow(2, difference);
    }
    return total;
}

double distanceCalculator(Point *A, Point *B){
    return sqrt(pointSummation(A, B));
}

double sumCluster(Cluster* C, Point cent){ //cent is our centroid  
    double total = pow(2, distanceCalculator(&C->c[0], &cent)); //It is the value to be returned. 
    for(int l = 1; l < C->n; l++){
        total += pow(2, distanceCalculator(&C->c[l], &cent));
    }
    return total;
}

double eCalculator(Cluster *C, Point c[], int k){ 
    double Total;
    Total = sumCluster(C, c[0]);
    for(int i = 1; i < k; i++){
        Total += sumCluster(C+i, c[i]);
    }
    return Total; 
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
    			if(BestPlace[i] < BestPlace[loc]){ loc = i; }
    		}
        	if(loc != currentClust){
            	if(min.ed < 0){
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

struct minimum Minimize(Cluster* C, Point* cent, int k){
    struct minimum min;
    struct minimum temp;
    for(int l = 0; l < k; l++){
    	temp = Minimum_find(C+l, cent, min, k, l);
    	if(temp.ed > -1 && temp.ed < min.ed){
    		min = temp;
    	}
    }
    return min;
}

Cluster* assign_points(Point p, Cluster* C, Point cent[], int k){
	double minimum = DBL_MAX;
	int target;
	Cluster clust[k];
	for(int i = 0; i < k; i++){
		double candidate = distanceCalculator(&p, &cent[i]);
		if(candidate < minimum){
			target = i;
			minimum = candidate;
		}
	}
	for(int i = 0; i < k; i++){
		if(i != target){
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

Cluster* tightenCluster(Cluster* C, Point* cent, int k){
    struct minimum min = Minimize(C, cent, k);
    if(min.ed > -1){
    	int k_index = min.k_index;
		int k_target = min.k_target;
    	C = point_reassignment(C, min.chosen, k_index, k_target, k);
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

double Accuracy(Cluster* C){
	double TP, FP, TN, FN;
	TP = 0;
	FP = 0;
	TN = 0;
	FN = 0;
	for(int i = 0; i < C->n; i++){
		if(C->c[i].lable == 4){
			TP = TP + 1;
		} else { //Then lable == 2
			FP = FP + 1;
		}
	}
	for(int i = 0; i < (C+1)->n; i++){
		if(C->c[i].lable == 2){
			FN = FN + 1;
		} else { //then lable == 4
			TN = TN + 1;
		}
	}

	double ALL = C->n + (C+1)->n;
	return (TP+TN)/ALL;
}

struct point* read(FILE *inFile, Point* D, int *valid)
{
    struct point list[699];
    inFile = fopen("breast-cancer-wisconsin.data", "r");
    char c = ' ';
    while (c != EOF )
    {
        for (int i = 0; i < 699; i++)
        {
            fscanf(inFile, "%d", &list[i].id_num);
            c = getc(inFile);
            
            for (int j = 0; j < 9; j++)
            {
                c = getc(inFile);
                if (c == '?')
                {
                    list[i].att[j] = 0;
                    c = getc(inFile);
                    *valid = *valid - 1;
                }
                else
                {
                    ungetc(c, inFile);
                    fscanf(inFile, "%lf", &list[i].att[j]);
                    c = getc(inFile);
                }
            }
            fscanf(inFile, "%d" , &list[i].lable);
            c = getc(inFile);
        }
    }
    /*
    for (int i = 0; i < 699; i++)
    {
        printf(" %d ", list[i].id_num);
        for (int j = 0; j < 9; j++)
        {
            printf("%.0lf ", list[i].att[j]);
        }
        printf("%d\n", list[i].lable);
    }
    */
    for(int i = 0; i < 699; i++)
    {
        *(D+i) = list[i];
    }
    
    return D;
}
