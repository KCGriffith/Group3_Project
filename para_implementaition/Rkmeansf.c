#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <float.h>
#include <mpi.h>
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
	if(world_rank == 0)
	{
		if(argc != 2)
		{
			printf("Please include an argument after the program name to list how many processes.\n");
			printf("e.g. To indicate 4 processes, run: mpirun -n 4 ./kmeans 4\n");
			exit(-1);
		}

		num_of_processes = atoi(argv[1]);

		char buffer[2];
		printf("How many clusters would you like to analyze for? ");
		scanf("%s", buffer);
		printf("\n");

		numOfClusters = atoi(buffer);
		printf("Ok %d clusters it is.\n", numOfClusters);


		// broadcast the number of clusters to all nodes
		MPI_Bcast(&numOfClusters, 1, MPI_INT, 0, MPI_COMM_WORLD);

		// allocate memory for arrays
		k_means_x = (double *)malloc(sizeof(double) * numOfClusters);
		k_means_y = (double *)malloc(sizeof(double) * numOfClusters);

		if(k_means_x == NULL || k_means_y == NULL)
		{
			perror("malloc");
			exit(-1);
		}

		printf("Reading input data from file...\n\n");

		FILE* fp = fopen("input.txt", "r");

		if(!fp)
		{
			perror("fopen");
			exit(-1);
		}

		// count number of lines to find out how many elements
		int c = 0;
		numOfElements = 0;
		while(!feof(fp))
		{
			c = fgetc(fp);
			if(c == '\n')
			{
				numOfElements++;
			}
		}

		printf("There are a total number of %d elements in the file.\n", numOfElements);

		// broadcast the number of elements to all nodes
		MPI_Bcast(&numOfElements, 1, MPI_INT, 0, MPI_COMM_WORLD);

		// allocate memory for an array of data points
		data_x_points = (double *)malloc(sizeof(double) * numOfElements);
		data_y_points = (double *)malloc(sizeof(double) * numOfElements);
		k_assignment = (int *)malloc(sizeof(int) * numOfElements);

		if(data_x_points == NULL || data_y_points == NULL || k_assignment == NULL)
		{
			perror("malloc");
			exit(-1);
		}

		// reset file pointer to origin of file
		fseek(fp, 0, SEEK_SET);

		// now read in points and fill the arrays
		int i = 0;

		double point_x=0, point_y=0;

		while(fscanf(fp, "%lf %lf", &point_x, &point_y) != EOF)
		{
			data_x_points[i] = point_x;
			data_y_points[i] = point_y;

			// assign the initial k means to zero
			k_assignment[i] = 0;
			i++;
		}

		// close file pointer
		fclose(fp);

		// randomly select initial k-means
		time_t t;
		srand((unsigned) time(&t));
		int random;
		for(int i = 0; i < numOfClusters; i++) {
			random = rand() % numOfElements;
			k_means_x[i] = data_x_points[random];
			k_means_y[i] = data_y_points[random];
		}

		printf("Running k-means algorithm for %d iterations...\n\n", MAX_ITERATIONS);
		for(int i = 0; i < numOfClusters; i++)
		{
			printf("Initial K-means: (%f, %f)\n", k_means_x[i], k_means_y[i]);
		}

		// allocate memory for receive buffers
		recv_x = (double *)malloc(sizeof(double) * ((numOfElements/num_of_processes) + 1));
		recv_y = (double *)malloc(sizeof(double) * ((numOfElements/num_of_processes) + 1));
		recv_assign = (int *)malloc(sizeof(int) * ((numOfElements/num_of_processes) + 1));

		if(recv_x == NULL || recv_y == NULL || recv_assign == NULL)
		{
			perror("malloc");
			exit(-1);
		}
	}
	else
	{	// I am a worker node

		num_of_processes = atoi(argv[1]);

		// receive broadcast of number of clusters
		MPI_Bcast(&numOfClusters, 1, MPI_INT, 0, MPI_COMM_WORLD);

		// receive broadcast of number of elements
		MPI_Bcast(&numOfElements, 1, MPI_INT, 0, MPI_COMM_WORLD);

		// allocate memory for arrays
		k_means_x = (double *)malloc(sizeof(double) * numOfClusters);
		k_means_y = (double *)malloc(sizeof(double) * numOfClusters);

		if(k_means_x == NULL || k_means_y == NULL)
		{
			perror("malloc");
			exit(-1);
		}

		// allocate memory for receive buffers
		recv_x = (double *)malloc(sizeof(double) * ((numOfElements/num_of_processes) + 1));
		recv_y = (double *)malloc(sizeof(double) * ((numOfElements/num_of_processes) + 1));
		recv_assign = (int *)malloc(sizeof(int) * ((numOfElements/num_of_processes) + 1));

		if(recv_x == NULL || recv_y == NULL || recv_assign == NULL)
		{
			perror("malloc");
			exit(-1);
		}
	}
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
