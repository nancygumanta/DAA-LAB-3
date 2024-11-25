#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Function to print the chessboard
void printBoard(int **board, int N) {
    printf("\nSolution Board:\n");
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            printf(" %c ", board[i][j] ? 'Q' : '.');
        }
        printf("\n");
    }
}
bool isSafe(int **board, int row, int col, int N) {
    int i, j;
    for (j = 0; j < col; j++) {
        if (board[row][j])
            return false;
    }
    for (i = row, j = col; i >= 0 && j >= 0; i--, j--) {
        if (board[i][j])
            return false;
    }
    for (i = row, j = col; i < N && j >= 0; i++, j--) {
        if (board[i][j])
            return false;
    }

    return true;
}
bool solveNQueens(int **board, int col, int N) {
    if (col >= N)
        return true;
    for (int row = 0; row < N; row++) {
        if (isSafe(board, row, col, N)) {
            board[row][col] = 1;
            if (solveNQueens(board, col + 1, N))
                return true;
            board[row][col] = 0; 
        }
    }
    return false;
}
int** initializeBoard(int N) {
    int** board = (int**)malloc(N * sizeof(int*));
    for (int i = 0; i < N; i++) {
        board[i] = (int*)calloc(N, sizeof(int));
    }
    return board;
}
void freeBoard(int **board, int N) {
    for (int i = 0; i < N; i++) {
        free(board[i]);
    }
    free(board);
}
int main() {
    int N;
    printf("Enter the size of the chessboard (N): ");
    scanf("%d", &N);
    if (N <= 0) {
        printf("Invalid board size!\n");
        return 1;
    }
    if (N == 2 || N == 3) {
        printf("Solution does not exist for N = %d\n", N);
        return 1;
    }
    int **board = initializeBoard(N);
    if (solveNQueens(board, 0, N)) {
        printf("\nSolution exists for N = %d", N);
        printBoard(board, N);
    } else {
        printf("\nSolution does not exist for N = %d\n", N);
    }
    freeBoard(board, N);
    return 0;
}
