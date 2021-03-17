
#include <stdio.h>
#include <stdlib.h>
#include<stdbool.h>

struct point
{
    double x, y;
};

bool compare_points(struct point a, struct point b)
{
    //Returns whether two points are equal.
    if (a.x == b.x && a.y == b.y)
        return true;
    else
    {
        return false;
    }
}

//This function helps to determine if change has occurred
bool shouldhalt(struct point old_centroid[], struct point centroid[], int k)
{
    int temp = 0;
    for (int i = 0; i < k; i++)
    {
        if (compare_points(old_centroid[i], centroid[i]))
        {
            temp += 1;
        }
    }
    if (temp == k-1)
        return true;
    else
        return false;
}

int main ()
{
    struct point a;
    struct point b;
    int k = 3;
    struct point *old_centroid;
    struct point *centroid;
    struct point od[3] = {{1,2}, {2,4}, {4,5}};
    struct point c[3] = {{1,2}, {2,4}, {3,5}};
    old_centroid = od;
    centroid = c;
    /*printf("Enter point a and b \n");
    scanf("%lf %lf %lf %lf", &a.x , &a.y , &b.x, &b.y);
    if (compare_points(a, b))
        printf("They are same points. \n");
        else
        {
            printf("They are different points. \n");
        }
    */
    // lets add some more points
    //pass the centroid array to should stop function
    if (shouldhalt(old_centroid, centroid, k))
        printf("Sorry to say but the show must go on. \n");
    else
        printf("The show must stop. \n");
    return 0;
}