#include <stdio.h>

struct point
{
    double x, y;
};

struct point centroid(struct point c[], int n)
{
    struct point cen;
    cen.x = 0, cen.y = 0;
    for (int j = 0; j < n ; j++)
    {
        cen.x += c[j].x;
        cen.y += c[j].y;
    }
    cen.x = cen.x / n;
    cen.y = cen.y / n;
    
    return cen;
}
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