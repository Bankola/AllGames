#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "funcs.h"
#include "utilities.h"

int StartSapper(int* difficult) {
    int rows, cols, FlagsCount = 0, MinesCount;
    if (*difficult == 1) {
        rows = 10;
        cols = 10;
    }
    else if (*difficult == 2) {
        rows = 8;
        cols = 8;
    }
    else {
        rows = 5;
        cols = 5;
    }
    MinesCount = (rows * cols) / 4;
    char** massive = CreateMassive(rows, cols, MinesCount);
    char** Fmassive = CreateFalseMassive(rows, cols);
    char** reveal = CreateRevealMassive(rows, cols);
    Shuffle2nd(massive, rows, cols);
    CountBombs(massive, rows, cols);
    while (FlagsCount != MinesCount) {
        system("cls");
        int user_row, user_cols;
        char user_command;
        PrintMassive(Fmassive, rows, cols);
        printf("'O' - open\n"
            "F - set flag\n"
            "D - delete flag\n"
            "Enter the cell in the following format: i j c\n"
            "i is the row number, j is the column number, c is the command.\n"
            "Example: 1 2 O\n");
        printf("Your choice is: ");
        scanf_s("%d %d %c", &user_row, &user_cols, &user_command);
        MakeStep(rows, cols, user_row, user_cols, user_command, reveal, massive, Fmassive);
    }

#ifdef DEBUG
    printf("DEBUG MODE ONLY \n");
    PrintMassive(massive, rows, cols);
#endif
    FreeMassive(massive, rows);
    FreeMassive(Fmassive, rows);
    return 0;
}
int MakeStep(int rows, int cols, int user_row, int user_cols, int user_command, char** reveal, char** massive, char** Fmassive) {
    if (IsValidCell(rows, cols, user_row, user_cols) == 0) {
        printf("Wrong input!Try again\n");
        system("pause");
        return 0;
    }
    if (massive[user_row, user_cols] != 'X' && reveal[user_row, user_cols] != '1') {
        reveal[user_row, user_cols] = '1';
        Fmassive[user_row, user_cols] = massive[user_row, user_cols];
        PrintMassive(Fmassive, rows, cols);
    }
}
char** CreateMassive(int rows, int cols, int MinesCount) {
    char** massive = (char**)malloc(rows * sizeof(char*));
    for (int i = 0; i < rows; i++) {
        massive[i] = (char*)malloc(cols * sizeof(char));
    }
    srand(time(NULL));

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            massive[i][j] = '-';
        }
    }

    int mines_placed = 0;
    while (mines_placed < MinesCount) {
        int rand_i = rand() % rows;
        int rand_j = rand() % cols;

        if (massive[rand_i][rand_j] == '-') {
            massive[rand_i][rand_j] = 'X';
            mines_placed++;
        }
    }

    return massive;
}

char** CreateRevealMassive(int rows, int cols) {
    char** reveal = (char**)malloc(rows * sizeof(char*));
    for (int i = 0; i < rows; i++) {
        reveal[i] = (char*)malloc(cols * sizeof(char));
    }
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            reveal[i][j] = '0';
        }
    }
    return reveal;
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
        printf("%d ", j+1);
    }
    printf("\n");

    for (int i = 0; i < rows; i++) {
        printf("%d ", i+1);
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
                    result[i][j] = '0';
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
