#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <float.h>
#include "kmeansf.h"
#include "medistruct.h"


int main(int argc, char *argv[])
{
	//For the time being ignore the fact C has to be initialized as a list.
	//At least until the data structure is in place.
	int MAX_VALUE = 5;

	FILE *inFile;
	struct point *p = (Point*)calloc(MAX_VALUE, sizeof(Point));
	int valid = MAX_VALUE;
	p = read(inFile, p, &valid);
	Cluster* result = (Cluster*)calloc(2, sizeof(Cluster));
	int k = 2;

	printf("WE ARE CHECKING IF ALL POINTS WERE COLLECTED\n");
    for(int i = 0; i < valid; i++){
    	print_point((p+i));
    	printf("\n");
    }

	struct point *D = (Point*)calloc(valid, sizeof(Point));
	bool val = true;
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
        	count++;
        }
    }

	printf("WE ARE CHECKING IF ALL POINTS WERE MINIMIZED\n");
    for(int i = 0; i < valid; i++){
    	print_point((D+i));
    	printf("\n");
    }

	result = kmeans(D, valid, k);
	
	printf("This clustering accuracy = %lf\n", Accuracy(result));

	return 0;
}