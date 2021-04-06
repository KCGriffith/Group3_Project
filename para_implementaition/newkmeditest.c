#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <float.h>

//kmeans.c

typedef struct point
{
    int id_num;
    double att[9]; //short for attributes.
    int lable;
} Point;

typedef struct cluster
{
    /*This will act as a list of points.
	  It will also keep track of how many
	  points are in a cluster.
	  */
    int n; //Number of elements determined during randCluster and tightenCluster.
    struct point *c;
} Cluster;

typedef struct minimum
{
    Point chosen;
    int k_index; //Keeps track of starting cluster.
    int k_target;
    double ed; //ed stands for Euclidean distance.
} Minimum;

//medistruct.c

int MAX_VALUE = 699;

//THIS BLOCK OF FUNCTIONS HANDLES PRINTING DIFFERENT STRUCT TYPES

//print cluster
void print_cluster(struct cluster *C, int k)
{
    //It turns out that all my problems stemed from this function.
    for (int i = 0; i < k; i++)
    {
        printf("Cluster %d:\n ", i + 1);
        for (int l = 0; l < (C + i)->n; l++)
        {
            print_point((C + i)->c + l);
        }
        printf("\n");
    }
    printf("\n");
}

//print centroid
void print_centroid(Point *cent, int k)
{
    printf("{");
    for (int i = 0; i < k; i++)
    {
        print_point(cent + i);
    }
    printf("}");
}

//print points
void print_point(struct point *c)
{
    printf("%d: (", c->id_num);
    for (int v = 0; v < 9; v++)
    {
        printf("%lf, ", c->att[v]);
    }
    printf(") LABLE: %d\n", c->lable);
}

//print minimum
void print_minimum(Minimum min)
{
    printf("I CHOSE THIS POINT AS THE MINIMUM: ");
    print_point(&min.chosen);
    printf("The chosen point is at cluster %d\n", min.k_index);
    printf("The chosen point is being assigned to cluster %d\n", min.k_target);
    printf("This is the score: %lf\n", min.ed);
}

//THESE FUNCTIONS ARE USED FOR EXTRACTING DATA

struct point *read(FILE *inFile, Point *D, int *valid)
{
    struct point list[MAX_VALUE];
    //inFile = fopen("test-data.data", "r");
    inFile = fopen("breast-cancer-wisconsin.data", "r");
    char c = ' ';
    while (c != EOF)
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
            fscanf(inFile, "%d", &list[i].lable);
            c = getc(inFile);
        }
    }

    for (int i = 0; i < MAX_VALUE; i++)
    {
        *(D + i) = list[i];
    }

    return D;
}

//THIS IS THE SECTION OF FUNCTIONS THAT HANDELS INITIALIZAITION

struct point init_point(int id_num, double att[], int lable)
{
    Point temp;
    double MAX = 10, MIN = 1;
    temp.id_num = id_num;
    for (int i = 0; i < 9; i++)
    {
        temp.att[i] = att[i];
    }
    for (int i = 0; i < 9; i++)
    {
        temp.att[i] = (temp.att[i] - MIN) / (MAX - MIN);
    }
    temp.lable = lable;
    return temp;
}

//cluster initializer I don't know what this is for.
struct cluster init_cluster(struct point *D, int n)
{
    return (Cluster){n, D};
}

//Initialize minimum
Minimum init_minimum(Point x, int a, int b, double dist)
{
    return (Minimum){x, a, b, dist};
}

// e_calc.c

//THIS BLOCK OF FUNCTIONS IS USED FOR CALCULAITION

double eCalculator(Cluster *C, Point c[], int k)
{
    double Total;
    Total = sumCluster(C, c[0]);
    for (int i = 1; i < k; i++)
    {
        Total += sumCluster(C + i, c[i]);
    }
    return Total;
}

double sumCluster(Cluster *C, Point cent)
{                                                               //cent is our centroid
    double total = pow(2, distanceCalculator(&C->c[0], &cent)); //It is the value to be returned.
    for (int l = 1; l < C->n; l++)
    {
        total += pow(2, distanceCalculator(&C->c[l], &cent));
    }
    return total;
}

double distanceCalculator(Point *A, Point *B)
{
    return sqrt(pointSummation(A, B));
}

double pointSummation(Point *A, Point *B)
{
    double total;
    total = 0;
    for (int v = 0; v < 9; v++)
    {
        double difference = fabs(A->att[v]) - (B->att[v]);
        total += pow(2, difference);
    }
    return total;
}

//THESE FUNCTIONS ARE USED FOR FINDING WHAT POINT SHOULD BE EXCHANGED

struct minimum Minimize(Cluster *C, Point *cent, int k)
{
    double att[9] = {0, 0, 0, 0, 0, 0, 0, 0, 0};
    Point p = init_point(0, att, 0);
    struct minimum min = init_minimum(p, 0, 0, -1);
    struct minimum temp = init_minimum(p, 0, 0, -1);
    for (int l = 0; l < k; l++)
    {
        temp = Minimum_find(C + l, cent, min, k, l);
        if (temp.ed > -1 && temp.ed < min.ed)
        {
            //min = temp;
            min.chosen = temp.chosen;
            min.k_index = temp.k_index;
            min.k_target = temp.k_target;
            min.ed = temp.ed;
        }
    }
    return min;
}

struct minimum Minimum_find(Cluster *C, Point *cent, struct minimum min, int k, int currentClust)
{
    double BestPlace[k];
    int loc;
    //Check if the cluster has one element
    if (C->n > 1)
    {
        for (int g = 0; g < C->n; g++)
        {
            for (int i = 0; i < k; i++)
            { //This creates a table of distances that we can choose from.
                BestPlace[i] = distanceCalculator(&C->c[g], &cent[i]);
            }
            loc = 0;
            for (int i = 1; i < k; i++)
            { //This is when we find the locaition of the best candidate.
                if (BestPlace[i] < BestPlace[loc] && i != currentClust)
                {
                    loc = i;
                }
            }
            if (loc != currentClust)
            {
                if (min.ed <= 0)
                {
                    min = init_minimum(C->c[g], currentClust, loc, BestPlace[k]);
                }
                else if (min.ed >= 0)
                {
                    if (min.ed > BestPlace[k])
                    {
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

Cluster *tightenCluster(Cluster *C, Point *cent, int k)
{
    struct minimum min = Minimize(C, cent, k);
    if (min.ed >= 0)
    {
        int k_index = min.k_index;
        int k_target = min.k_target;
        C = point_reassignment(C, min.chosen, k_index, k_target, k);
    }

    return C;
}

Cluster *assign_points(Point p, Cluster *C, Point cent[], int k)
{
    double minimum = DBL_MAX;
    int target;
    Cluster clust[k];
    //This for loop finds the minimum.
    for (int i = 0; i < k; i++)
    {
        double candidate = distanceCalculator(&p, &cent[i]);
        if (candidate < minimum)
        {
            target = i;
            minimum = candidate;
        }
    }

    //This for loop finds the target location to allocate.
    for (int i = 0; i < k; i++)
    {

        if (i != target)
        { //i is the other cluster.
            clust[i] = init_cluster((C + i)->c, (C + i)->n);
        }
        else
        {
            int v = (C + i)->n + 1, lastindex = v - 1;
            Point *d = (Point *)calloc(v, sizeof(Point));
            for (int l = 0; l < (C + i)->n; l++)
            {
                *(d + l) = (C + i)->c[l];
            }
            *(d + lastindex) = p;
            clust[i] = init_cluster(d, v);
        }
    }

    free(C);
    C = (Cluster *)calloc(k, sizeof(Cluster));
    for (int i = 0; i < k; i++)
    {
        *(C + i) = clust[i];
    }

    return C;
}

Cluster *point_reassignment(Cluster *C, Point chosen, int start, int target, int k)
{
    int target_n, start_n;
    Cluster ctemp[k];

    target_n = ((C + target)->n) + 1;
    start_n = ((C + start)->n) - 1;
    for (int l = 0; l < k; l++)
    {
        if (l == target)
        {
            Point *D = (Point *)calloc(target_n, sizeof(Point));
            for (int i = 0; i < target_n; i++)
            {
                if (i < target_n - 1)
                {
                    *(D + i) = (C + target)->c[i];
                }
                else
                {
                    *(D + i) = chosen;
                }
            }
            ctemp[target] = init_cluster(D, target_n);
        }
        else if (l == start)
        {
            Point *D = (Point *)calloc(start_n, sizeof(Point));
            int v = 0, j = 0;
            for (int i = 0; i < (C + start)->n; i++)
            {
                if (!compare_points((C + start)->c[v], chosen))
                {
                    *(D + j) = (C + start)->c[v];
                    v++;
                    j++;
                }
                else
                {
                    v++;
                }
            }
            ctemp[start] = init_cluster(D, start_n);
        }
        else
        {
            int v = (C + l)->n;
            int unchanged = l;
            Point *D = (Point *)calloc(v, sizeof(Point));
            for (int i = 0; i < v; i++)
            {
                *(D + i) = (C + unchanged)->c[i];
            }
            ctemp[unchanged] = init_cluster(D, v);
        }
    }

    free(C);
    C = (Cluster *)calloc(k, sizeof(Cluster));
    for (int i = 0; i < k; i++)
    {
        *(C + i) = ctemp[i];
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
bool compare_points(struct point a, struct point b)
{
    //Returns whether two points are equal.
    for (int v = 0; v < 9; v++)
    {
        if (a.att[v] != b.att[v])
        {
            return false;
        }
    }
    return true;
}

//kmeansf.c
//THIS IS THE MAIN KMEANS ALGORITHM
struct cluster *kmeans(struct point *D, int n, int k)
{

    time_t t;
    srand((unsigned)time(&t));

    int pick, last_picked[n]; //These insure unique values go into the clusters.
    printf("IM n IN KMEANS: %d\n", n);
    double E = DBL_MAX, E_previous = DBL_MAX;
    //Initializaition
    struct cluster *C = (Cluster *)calloc(k, sizeof(Cluster));
    struct point centroid[k]; //This initializes the centroid list.

    for (int z = 0; z < n; z++)
    {
        //An index cannot be negative so all of the
        //initial values for last_picked needs to be set to a negative value.
        last_picked[z] = -1;
    }

    for (int i = 0; i < k; i++)
    {
        //We are going to initially pick a random value.
        pick = rand() % n;

        while (!is_unique(last_picked, pick, n) || (pick > n))
        {
            pick = (rand() % n);
        } //If the index is not unique we take another random index until we find a unique
        //We want temp at m to take the value from D at pick.
        centroid[i] = *(D + pick);

        //We now add pick to the array of last picked.
        last_picked[i] = pick;
        *(C + i) = init_cluster((D + i), 1); //The first point of each cluster is pointing at the address of memory for centroid array.
    }

    //Book Keeping
    struct point old_centroids[k], temp_centroids[k];
    int w = 0, o = 2, amount = 0;

    while (!shouldHalt(old_centroids, centroid, k) || amount != n)
    {

        Cluster *temp = (Cluster *)calloc(k, sizeof(Cluster));
        E_previous = E;
        for (int i = 0; i < k; i++)
        {
            old_centroids[i] = centroid[i];
        }

        while (!is_unique(last_picked, w, n) && w < n)
        {
            w++;
        }

        //We need to know when all points have been assigned to a cluster.
        if (w < n)
        {
            C = assign_points(D[w], C, centroid, k);
            last_picked[o] = w;
            w++;
            o++;
            for (int i = 0; i < k; i++)
            {
                centroid[i] = get_centroid((C + i)->c, (C + i)->n);
            }
        }
        else
        {   //If we have assigned the points we need to adjust the clusters.
            //Reassign objects to the cluster.

            for (int i = 0; i < k; i++)
            { //This allows us to see if we improve the cluster without causing change.
                *(temp + i) = *(C + i);
            }

            temp = tightenCluster(temp, centroid, k);
            for (int i = 0; i < k; i++)
            {
                temp_centroids[i] = get_centroid((temp + i)->c, (temp + i)->n);
            }

            E = eCalculator(temp, temp_centroids, k);
            //printf("E_previous: %lf vs E: %lf: %d\n", E_previous, E, E < E_previous);
            if (E < E_previous)
            { //If the score is improved then we change the main cluster
                //printf("IM HERE!\n");
                for (int i = 0; i < k; i++)
                {
                    *(C + i) = *(temp + i);
                }

                for (int i = 0; i < k; i++)
                {
                    centroid[i] = temp_centroids[i];
                }

            } //We are done otherwise.

            free(temp);
        }
        amount = 0;
        for (int i = 0; i < k; i++)
        {
            amount += (C + i)->n;
        }
    }

    return C;
}

//ensure unique elements are picked
bool is_unique(int *past_pick, int pick, int n)
{
    for (int i = 0; i < n; i++)
    {
        if (*(past_pick + i) == pick)
        {
            return false;
        }
    }
    return true;
}
//THIS BLOCK OF FUNCTIONS USED TO UPDATE CENTROIDS

//centroid function to calculate centroid
struct point get_centroid(struct point *c, int n)
{
    //centroid as a point
    struct point cen;
    if (n == 1)
    {
        for (int v = 0; v < 9; v++)
        {
            cen.att[v] = c->att[v];
        }
        return cen;
    }

    for (int v = 0; v < 9; v++)
    {
        cen.att[v] = (c)->att[v];
    }
    for (int j = 1; j < n; j++)
    {
        for (int v = 0; v < 9; v++)
        {
            cen.att[v] += (c + j)->att[v];
        }
    }
    //average of all the data points
    for (int j = 0; j < n; j++)
    {
        for (int v = 0; v < 9; v++)
        {
            cen.att[v] = cen.att[v] / n;
        }
    }
    //return centroid
    return cen;
}

//USED TO DETERMINE ACCURACY OF THE KMEANS ALGORITHM
double Accuracy(Cluster *C)
{

    double TP, FP, TN, FN;
    TP = 0;
    FP = 0;
    TN = 0;
    FN = 0;
    for (int i = 0; i < C->n; i++)
    {
        switch (C->c[i].lable)
        {
        case 2:
            FP = FP + 1;
        case 4:
            TP = TP + 1;
        }
    }
    for (int i = 0; i < (C + 1)->n; i++)
    {
        switch ((C + 1)->c[i].lable)
        {
        case 2:
            FN = FN + 1;
        case 4:
            TN = TN + 1;
        }
    }

    printf("TP: %lf\n", TP);
    printf("FP: %lf\n", FP);
    printf("TN: %lf\n", TN);
    printf("FN: %lf\n", FN);

    double ALL = C->n + (C + 1)->n;
    return (TP + TN) / ALL;
}

int main(int argc, char *argv[])
{
    //For the time being ignore the fact C has to be initialized as a list.
    //At least until the data structure is in place.
    int MAX_VALUE = 699;

    FILE *inFile;
    struct point *p = (Point *)calloc(MAX_VALUE, sizeof(Point));
    int valid = MAX_VALUE;
    p = read(inFile, p, &valid);
    Cluster *result = (Cluster *)calloc(2, sizeof(Cluster));
    int k = 2;

    struct point *D = (Point *)calloc(valid, sizeof(Point));
    bool val = true;
    int count = 0;

    printf("valid: %d\n", valid);

    for (int i = 0; i < valid; i++)
    {
        for (int l = 0; l < 9; l++)
        {
            if ((p + count)->att[l] == 0)
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
        if (val)
        {
            *(D + i) = init_point((p + count)->id_num, (p + count)->att, (p + count)->lable);
            count++;
        }
    }

    result = kmeans(D, valid, k);
    printf("This clustering accuracy = %lf\n", Accuracy(result));

    return 0;
}