#include <stdio.h>
#include <limits.h>
int matrixChainOrder(int p[], int n) {
    int m[n][n];
    int s[n][n];
    for (int i = 1; i < n; i++)
        m[i][i] = 0;
    for (int L = 2; L < n; L++) {
        for (int i = 1; i < n - L + 1; i++) {
            int j = i + L - 1;
            m[i][j] = INT_MAX;
            for (int k = i; k <= j - 1; k++) {
                int q = m[i][k] + m[k + 1][j] + p[i - 1] * p[k] * p[j];
                if (q < m[i][j]) {
                    m[i][j] = q;
                    s[i][j] = k;
                }
            }
        }
    }
    return m[1][n - 1];
}
void printOptimalParenthesis(int s[][10], int i, int j) {
    if (i == j)
        printf("A%d", i);
    else {
        printf("(");
        printOptimalParenthesis(s, i, s[i][j]);
        printOptimalParenthesis(s, s[i][j] + 1, j);
        printf(")");
    }
}

int main() {
    int arr[] = {1, 2, 3, 4}; 
    int n = sizeof(arr) / sizeof(arr[0]);
    int m[n][n];
    int s[n][n];
    int minCost = matrixChainOrder(arr, n);
    printf("Minimum number of multiplications is %d\n", minCost);
    printf("Optimal Parenthesization is: ");
    printOptimalParenthesis(s, 1, n - 1);
    printf("\n");
    return 0;
}
