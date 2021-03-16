#include <stdio.h>

// point has x and y component
struct point
{
    double x, y;
};

centroid function to calculate centroid
struct point centroid(struct point c[], int n)
{
    //centroid as a point
    struct point cen;

    //initialize centroid
    cen.x = 0, cen.y = 0;

    for (int j = 0; j < n ; j++)
    {
        cen.x += c[j].x;
        cen.y += c[j].y;
    }

    //average of all the data points
    cen.x = cen.x / n;
    cen.y = cen.y / n;
    
    //return centroid
    return cen;
}

//main to test centroid function
int main(void)
{
    int size;
    printf("Size of cluster\n");
    scanf("%d", &size);
    struct point c[size];
    for (int i = 0; i < size; i++)
    {
        printf("Enter x and y\n");
        scanf("%lf %lf", &c[i].x, &c[i].y);
    }
    struct point cen;
    cen = centroid (c, size);
    printf("The centroid of cluster is (%.2lf, %.2lf) \n" , cen.x, cen.y);
    return 0;
}