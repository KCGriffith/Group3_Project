#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<stdbool.h>

typedef struct point
{
    int id_num;
    double att[9];
    int lable;
} Point;

void print_point(struct point *c)
{
    printf("(%d ", c->id_num);
    for (int v = 0; v < 9; v++)
    {
        printf("%lf, ", c->att[v]);
    }
    printf("%d)", c->lable);
}

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
    print_point(&temp);
    printf("\n");
    return temp;
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

int main()
{
    FILE *inFile;
    struct point *p = (Point*)calloc(699, sizeof(Point*));
    int valid = 699;
    p = read(inFile, p, &valid);
    
    struct point* D = (Point*)calloc(valid, sizeof(Point));
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
    
    for (int i = 0; i< valid; i++)
    {
        print_point((D+i));
        printf("\n");
    }
    
    printf("The valid number of entries is : %d", valid);
    return 0;
}
