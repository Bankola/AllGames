#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "funcs.h"

int StartSapper(int* difficult) {
    printf("'O' - open\n"
        "F - set flag\n"
        "D - delete flag\n"
        "Enter the cell in the following format: i j\n"
        "i is the row number, j is the column number\n");
    int rows = 5, cols = 5;
    char** massive = CreateMassive(rows, cols);
    char** Fmassive = CreateFalseMassive(rows, cols);
    Shuffle2nd(massive, rows, cols);

    CountBombs(massive, rows, cols);

    PrintMassive(Fmassive, rows, cols);
    PrintMassive(massive, rows, cols);
    FreeMassive(massive, rows);
    FreeMassive(Fmassive, rows);
    return 0;
}

char** CreateMassive(int rows, int cols) {
    char** massive = (char**)malloc(rows * sizeof(char*));
    for (int i = 0; i < rows; i++) {
        massive[i] = (char*)malloc(cols * sizeof(char));
    }
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (j % 4 == 0) {
                massive[i][j] = 'X';  
            }
            else {
                massive[i][j] = '-';  
            }
        }
    }
    return massive;
}

char** CreateFalseMassive(int rows, int cols) {
    char** Fmassive = (char**)malloc(rows * sizeof(char*));
    for (int i = 0; i < rows; i++) {
        Fmassive[i] = (char*)malloc(cols * sizeof(char));
    }
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            Fmassive[i][j] = 'X';  
        }
    }
    return Fmassive;
}

void Shuffle2nd(char** matrix, int rows, int cols) {
    srand(time(NULL));
    for (int i = 0; i < rows * cols; i++) {
        int rand_i = rand() % rows;
        int rand_j = rand() % cols;
        int curr_i = i / cols;
        int curr_j = i % cols;

        char temp = matrix[curr_i][curr_j];
        matrix[curr_i][curr_j] = matrix[rand_i][rand_j];
        matrix[rand_i][rand_j] = temp;
    }
}

void PrintMassive(char** matrix, int rows, int cols) {
    printf("  ");
    for (int j = 0; j < cols; j++) {
        printf("%d ", j);
    }
    printf("\n");

    for (int i = 0; i < rows; i++) {
        printf("%d ", i);
        for (int j = 0; j < cols; j++) {
            printf("%c ", matrix[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

void FreeMassive(char** matrix, int rows) {
    for (int i = 0; i < rows; i++) {
        free(matrix[i]);
    }
    free(matrix);
}

int IsValidCell(int i, int j, int rows, int cols) {
    return (i >= 0 && i < rows && j >= 0 && j < cols);
}

int CountBombsAround(char** matrix, int i, int j, int rows, int cols) {
    int count = 0;

    for (int di = -1; di <= 1; di++) {
        for (int dj = -1; dj <= 1; dj++) {
            if (di == 0 && dj == 0) continue; 

            int ni = i + di;
            int nj = j + dj;

            if (IsValidCell(ni, nj, rows, cols) && matrix[ni][nj] == 'X') {
                count++;
            }
        }
    }

    return count;
}

void CountBombs(char** matrix, int rows, int cols) {
    char** result = (char**)malloc(rows * sizeof(char*));
    for (int i = 0; i < rows; i++) {
        result[i] = (char*)malloc(cols * sizeof(char));
    }

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (matrix[i][j] == 'X') {
                result[i][j] = 'X';
            }
            else {
                int bombCount = CountBombsAround(matrix, i, j, rows, cols);
                if (bombCount > 0) {
                    result[i][j] = '0' + bombCount; 
                }
                else {
                    result[i][j] = ' ';
                }
            }
        }
    }

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            matrix[i][j] = result[i][j];
        }
        free(result[i]);
    }
    free(result);
}
