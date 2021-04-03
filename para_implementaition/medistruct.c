#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <float.h>
#include "medistruct.h"

int MAX_VALUE = 699;

//THIS BLOCK OF FUNCTIONS HANDLES PRINTING DIFFERENT STRUCT TYPES

//print cluster
void print_cluster(struct cluster *C, int k){
    //It turns out that all my problems stemed from this function.
    for(int i = 0; i < k; i++){
        printf("Cluster %d:\n ", i+1);
        for(int l = 0; l < (C+i)->n; l++){
            print_point((C+i)->c+l);
        }
        printf("\n");
    }
    printf("\n");
}

//print centroid
void print_centroid(Point* cent, int k){
    printf("{");
    for(int i = 0; i < k; i++){
        print_point(cent+i);
    }
    printf("}");
}

//print points
void print_point(struct point *c){
    printf("%d: (", c->id_num);
    for(int v = 0; v < 9; v++){
        printf("%lf, ", c->att[v]);
    }
    printf(") LABLE: %d\n", c->lable);
}   

//print minimum
void print_minimum(Minimum min){
    printf("I CHOSE THIS POINT AS THE MINIMUM: ");
    print_point(&min.chosen);
    printf("The chosen point is at cluster %d\n", min.k_index);
    printf("The chosen point is being assigned to cluster %d\n", min.k_target);
    printf("This is the score: %lf\n", min.ed);
}

//THESE FUNCTIONS ARE USED FOR EXTRACTING DATA

struct point* read(FILE *inFile, Point* D, int *valid)
{
    struct point list[MAX_VALUE];
    //inFile = fopen("test-data.data", "r");
    inFile = fopen("breast-cancer-wisconsin.data", "r");
    char c = ' ';
    while (c != EOF )
    {
        for (int i = 0; i < MAX_VALUE; i++)
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

    for(int i = 0; i < MAX_VALUE; i++)
    {
        *(D+i) = list[i];
    }
    
    return D;
}

//THIS IS THE SECTION OF FUNCTIONS THAT HANDELS INITIALIZAITION

struct point init_point(int id_num, double att[], int lable){
    Point temp;
    double MAX = 10, MIN = 1;
    temp.id_num = id_num;
    for(int i = 0; i < 9; i++){
        temp.att[i] = att[i];
    }
    for(int i = 0; i < 9; i++)
    {
        temp.att[i] = (temp.att[i] - MIN)/(MAX - MIN);
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


