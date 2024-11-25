#include <stdio.h>
typedef struct {
    int weight;
    int value;
    float ratio; 
} Item;
int compare(const void *a, const void *b) {
    Item *item1 = (Item *)a;
    Item *item2 = (Item *)b;
    return (item2->ratio > item1->ratio) - (item2->ratio < item1->ratio);
}
float greedyKnapsack(Item items[], int n, int capacity) {
    qsort(items, n, sizeof(Item), compare);
    float totalValue = 0.0;
    for (int i = 0; i < n; i++) {
        if (items[i].weight <= capacity) {
            capacity -= items[i].weight;
            totalValue += items[i].value;
        } else {
            totalValue += items[i].value * ((float)capacity / items[i].weight);
            break;
        }
    }
    return totalValue;
}
int main() {
    Item items[] = {{10, 60}, {20, 100}, {30, 120}};
    int n = sizeof(items) / sizeof(items[0]);
    int capacity = 50;

    float maxValue = greedyKnapsack(items, n, capacity);
    printf("Maximum value in Greedy Knapsack: %.2f\n", maxValue);
    return 0;
}
