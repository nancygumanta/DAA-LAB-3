#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

// Structure for Branch and Bound
typedef struct {
    float bound;
    float profit;
    float weight;
    int level;
} Node;

// Global variables to store best solution for backtracking
int* bestSolution;
int maxProfit = 0;

// Function to get maximum of two integers
int max(int a, int b) {
    return (a > b) ? a : b;
}

// Function for Dynamic Programming approach
int knapsackDP(int W, int wt[], int val[], int n) {
    clock_t start = clock();
    
    int** K = (int**)malloc((n + 1) * sizeof(int*));
    for (int i = 0; i <= n; i++) {
        K[i] = (int*)malloc((W + 1) * sizeof(int));
    }
    for (int i = 0; i <= n; i++) {
        for (int w = 0; w <= W; w++) {
            if (i == 0 || w == 0)
                K[i][w] = 0;
            else if (wt[i - 1] <= w)
                K[i][w] = max(val[i - 1] + K[i - 1][w - wt[i - 1]], K[i - 1][w]);
            else
                K[i][w] = K[i - 1][w];
        }
    }
    int result = K[n][W];
    for (int i = 0; i <= n; i++) {
        free(K[i]);
    }
    free(K);

    clock_t end = clock();
    printf("\nTime taken by Dynamic Programming: %f seconds\n", 
           ((double)(end - start)) / CLOCKS_PER_SEC);

    return result;
}

// Backtracking approach helper function
void knapsackBacktrackUtil(int W, int wt[], int val[], int n, int curr_weight,
                          int curr_profit, int level, int* solution) {
    if (curr_weight <= W && curr_profit > maxProfit) {
        maxProfit = curr_profit;
        for (int i = 0; i < n; i++) {
            bestSolution[i] = solution[i];
        }
    }
    if (level == n || curr_weight > W)
        return;
    solution[level] = 1;
    knapsackBacktrackUtil(W, wt, val, n, curr_weight + wt[level],
                         curr_profit + val[level], level + 1, solution);
    solution[level] = 0;
    knapsackBacktrackUtil(W, wt, val, n, curr_weight,
                         curr_profit, level + 1, solution);
}
int knapsackBacktrack(int W, int wt[], int val[], int n) {
    clock_t start = clock();
    
    int* solution = (int*)calloc(n, sizeof(int));
    bestSolution = (int*)calloc(n, sizeof(int));
    maxProfit = 0;

    knapsackBacktrackUtil(W, wt, val, n, 0, 0, 0, solution);

    free(solution);
    int result = maxProfit;
    free(bestSolution);

    clock_t end = clock();
    printf("Time taken by Backtracking: %f seconds\n", 
           ((double)(end - start)) / CLOCKS_PER_SEC);

    return result;
}

// Function to calculate bound for Branch and Bound
float bound(Node u, int n, int W, int wt[], int val[]) {
    if (u.weight >= W)
        return 0;

    float profit_bound = u.profit;
    int j = u.level + 1;
    float totweight = u.weight;

    while ((j < n) && (totweight + wt[j] <= W)) {
        totweight += wt[j];
        profit_bound += val[j];
        j++;
    }

    if (j < n)
        profit_bound += (W - totweight) * ((float)val[j] / wt[j]);

    return profit_bound;
}
// Branch and Bound approach
int knapsackBranchAndBound(int W, int wt[], int val[], int n) {
    clock_t start = clock();
    Node* pq = (Node*)malloc(1000 * sizeof(Node));
    int pq_size = 0;
    Node u, v;
    u.level = -1;
    u.profit = u.weight = 0;
    u.bound = bound(u, n, W, wt, val);
    float maxProfit = 0;
    pq[pq_size++] = u;
    while (pq_size > 0) {
        int max_idx = 0;
        for (int i = 1; i < pq_size; i++) {
            if (pq[i].bound > pq[max_idx].bound)
                max_idx = i;
        }

        u = pq[max_idx];
        for (int i = max_idx; i < pq_size - 1; i++) {
            pq[i] = pq[i + 1];
        }
        pq_size--;
        if (u.bound > maxProfit) {
            v.level = u.level + 1;
            v.weight = u.weight + wt[v.level];
            v.profit = u.profit + val[v.level];
            if (v.weight <= W && v.profit > maxProfit)
                maxProfit = v.profit;
            v.bound = bound(v, n, W, wt, val);
            if (v.bound > maxProfit)
                pq[pq_size++] = v;
            v.weight = u.weight;
            v.profit = u.profit;
            v.bound = bound(v, n, W, wt, val);
            if (v.bound > maxProfit)
                pq[pq_size++] = v;
        }
    }
    free(pq);
    clock_t end = clock();
    printf("Time taken by Branch and Bound: %f seconds\n", 
           ((double)(end - start)) / CLOCKS_PER_SEC);
    return maxProfit;
}

void generateTestData(int n, int maxWeight, int maxValue, 
                     int wt[], int val[]) {
    for (int i = 0; i < n; i++) {
        wt[i] = rand() % maxWeight + 1;
        val[i] = rand() % maxValue + 1;
    }
}

int main() {
    int n, W;
    printf("Enter number of items: ");
    scanf("%d", &n);
    printf("Enter knapsack capacity: ");
    scanf("%d", &W);

    // Dynamically allocate arrays
    int* wt = (int*)malloc(n * sizeof(int));
    int* val = (int*)malloc(n * sizeof(int));

    // Generate random test data
    srand(time(NULL));
    generateTestData(n, 50, 100, wt, val);

    printf("\nGenerated Test Data:");
    printf("\nWeights: ");
    for (int i = 0; i < n; i++)
        printf("%d ", wt[i]);
    printf("\nValues: ");
    for (int i = 0; i < n; i++)
        printf("%d ", val[i]);
    printf("\n");

    // Compare all three approaches
    printf("\nComparing different approaches:\n");
    int resultDP = knapsackDP(W, wt, val, n);
    int resultBacktrack = knapsackBacktrack(W, wt, val, n);
    int resultBnB = knapsackBranchAndBound(W, wt, val, n);

    printf("\nResults:");
    printf("\nDynamic Programming: %d", resultDP);
    printf("\nBacktracking: %d", resultBacktrack);
    printf("\nBranch and Bound: %d\n", resultBnB);

    // Free allocated memory
    free(wt);
    free(val);

    return 0;
}
