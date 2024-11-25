#include <stdio.h>
struct Activity 
{
    int start, finish;
};
int RECURSIVE_ACTIVITY_SELECTOR(struct Activity activities[], int s, int f, int n) 
{
    int m = s + 1;
    while (m <= n && activities[m].start < activities[s].finish) 
    {
        m++;
    }
    if (m <= n) 
    {
        return 1 + RECURSIVE_ACTIVITY_SELECTOR(activities, m, f, n); 
    } 
    else 
    {
        return 0; 
    }
}

int main() {
    struct Activity activities[] = {{1, 4}, {3, 5}, {0, 6}, {5, 7}, {3, 8}, {5, 9}, {8, 11}};
    int n = sizeof(activities) / sizeof(activities[0]);
    int maxActivities = RECURSIVE_ACTIVITY_SELECTOR(activities, 0, n - 1, n);
    printf("Maximum number of activities: %d\n", maxActivities);
    return 0;
}
