#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#include "funcs.h"
#define DEBUG
int StartSapper(int* difficulty) {

    int rows, cols, mines_count;

    if (*difficulty == 2) {
        rows = 10;
        cols = 10;
        mines_count = 10;
    }
    else if (*difficulty == 1) {
        rows = 16;
        cols = 16;
        mines_count = 40;
    }
    else {
        rows = 5;
        cols = 5;
        mines_count = 5;
    }
    char** mine_field = CreateMineField(rows, cols, mines_count);
    char** display_field = CreateDisplayField(rows, cols);
    char** state_field = CreateStateField(rows, cols);

    srand(time(NULL));
    CreateMines(mine_field, rows, cols, mines_count);
    CalculateNumbers(mine_field, rows, cols);

    int flags_count = 0;
    int game_over = 0;
    int win = 0;
    while (!game_over && !win) {
        system("cls");
#ifdef DEBUG
        printf("DEBUG MODE ONLY\n");
        PrintField(mine_field, rows, cols, 1);
#endif
        printf("=== Sapper ===\n");
        printf("Size: %dx%d, Mines: %d\n", rows, cols, mines_count);
        printf("Flags: %d/%d\n\n", flags_count, mines_count);

        PrintField(display_field, rows, cols, 1);

        printf("Commands:\n");
        printf("  O - Open\n");
        printf("  F - Set/Delete Flag\n");
        printf("\nFormat: row col command\n");
        printf("Example: 5 3 O\n\n");

        int input_row, input_col;
        char input_command;

        printf("Your choice: ");
        if (scanf_s("%d %d %c", &input_row, &input_col, &input_command) != 3) {
            printf("\nInput Error!\n");
            ClearInput();
            printf("Use Enter to continue..\n");
            getchar();
            continue;
        }

        input_command = toupper(input_command);

        if (input_row < 1 || input_row > rows || input_col < 1 || input_col > cols) {
            printf("\nError! Input coordinates 1-%d и 1-%d\n", rows, cols);
            printf("Use Enter to continue..\n");
            ClearInput();
            getchar();
            continue;
        }

        if (input_command != 'O' && input_command != 'F') {
            printf("\nError! Unknown command\n");
            printf("Use Enter to continue..\n");
            ClearInput();
            getchar();
            continue;
        }

        int move_result = MakeMoveSapper(mine_field, display_field, state_field,
            rows, cols, mines_count, &flags_count,
            input_row, input_col, input_command);

        if (move_result == 1) { 
            game_over = 1;
            system("cls");
            printf("\n=== End ===\n");
            printf("You find the mine in (%d, %d)!\n\n", input_row, input_col);

            for (int i = 0; i < rows; i++) {
                for (int j = 0; j < cols; j++) {
                    if (mine_field[i][j] == 'X') {
                        display_field[i][j] = 'X';
                    }
                }
            }
            display_field[input_row - 1][input_col - 1] = '!'; 

            PrintField(display_field, rows, cols, 1);
        }
        else if (move_result == 0) { 
            win = CheckGameWin(mine_field, state_field, rows, cols, mines_count, flags_count);

            if (win) {
                system("cls");
                printf("\n=== WIN! ===\n");
                printf("You find all mines on shield!\n\n");
                PrintField(display_field, rows, cols, 1);
            }
        }
        else {
            printf("Use Enter to continue..\n");
            ClearInput();
            getchar();
        }
    }

    ClearField(mine_field, rows);
    ClearField(display_field, rows);
    ClearField(state_field, rows);
    ClearInput();
    getchar();

    return 0;
}

void RecursiveReveal(char** mine_field, char** display_field, char** state_field, int rows, int cols, int row, int col) {

    if (!IsValidCell(row, col, rows, cols)) {
        return;
    }

    if (state_field[row][col] == '1' || state_field[row][col] == 'F') {
        return;
    }

    state_field[row][col] = '1';
    display_field[row][col] = mine_field[row][col];

    if (mine_field[row][col] == 'X') {
        return;
    }

    if (mine_field[row][col] == '0') {
        for (int di = -1; di <= 1; di++) {
            for (int dj = -1; dj <= 1; dj++) {
                if (di == 0 && dj == 0) {
                    continue;
                }

                int new_row = row + di;
                int new_col = col + dj;

                RecursiveReveal(mine_field, display_field, state_field,
                    rows, cols, new_row, new_col);
            }
        }
    }
}

int CountBombsAround(char** mine_field, int row, int col, int rows, int cols) {
    int count = 0;

    for (int di = -1; di <= 1; di++) {
        for (int dj = -1; dj <= 1; dj++) {
            if (di == 0 && dj == 0) {
                continue;
            }

            int new_row = row + di;
            int new_col = col + dj;

            if (IsValidCell(new_row, new_col, rows, cols)) {
                if (mine_field[new_row][new_col] == 'X') {
                    count++;
                }
            }
        }
    }

    return count;
}

int IsValidCell(int row, int col, int rows, int cols) {
    return (row >= 0 && row < rows && col >= 0 && col < cols);
}

int MakeMoveSapper(char** mine_field, char** display_field, char** state_field,
    int rows, int cols, int mines_count, int* flags_count,
    int row, int col, char command) {

    int r = row - 1;
    int c = col - 1;

    switch (command) {
    case 'O':
        if (state_field[r][c] == '1') {
            printf("That`s already open!\n");
            return -1;
        }

        if (state_field[r][c] == 'F') {
            printf("Delete Flag before do that!\n");
            return -1;
        }

        if (mine_field[r][c] == 'X') {
            return 1;
        }

        RecursiveReveal(mine_field, display_field, state_field, rows, cols, r, c);

        return 0;

    case 'F':
        if (state_field[r][c] == '1') {
            printf("You can`t set flag at this position!\n");
            return -1;
        }

        if (state_field[r][c] == 'F') {
            state_field[r][c] = '0';
            display_field[r][c] = '.';
            (*flags_count)--;
            printf("Flag delete from (%d, %d)\n", row, col);
        }
        else {
            state_field[r][c] = 'F';
            display_field[r][c] = 'F';
            (*flags_count)++;
            printf("Flag set on (%d, %d)\n", row, col);
        }

        return 0;

    default:
        return -1;
    }
}

char** CreateMineField(int rows, int cols, int mines_count) {
    char** field = (char**)malloc(rows * sizeof(char*));
    if (!field) return NULL;

    for (int i = 0; i < rows; i++) {
        field[i] = (char*)malloc(cols * sizeof(char));
        if (!field[i]) {
            for (int j = 0; j < i; j++) free(field[j]);
            free(field);
            return NULL;
        }

        for (int j = 0; j < cols; j++) {
            field[i][j] = '0';
        }
    }

    return field;
}

char** CreateDisplayField(int rows, int cols) {

    char** field = (char**)malloc(rows * sizeof(char*));

    if (!field) return NULL;

    for (int i = 0; i < rows; i++) {
        field[i] = (char*)malloc(cols * sizeof(char));
        if (!field[i]) {
            for (int j = 0; j < i; j++) free(field[j]);
            free(field);
            return NULL;
        }

        for (int j = 0; j < cols; j++) {
            field[i][j] = '.';
        }
    }

    return field;
}

char** CreateStateField(int rows, int cols) {
    char** field = (char**)malloc(rows * sizeof(char*));
    if (!field) return NULL;

    for (int i = 0; i < rows; i++) {
        field[i] = (char*)malloc(cols * sizeof(char));
        if (!field[i]) {
            for (int j = 0; j < i; j++) free(field[j]);
            free(field);
            return NULL;
        }

        for (int j = 0; j < cols; j++) {
            field[i][j] = '0';
        }
    }

    return field;
}

void CreateMines(char** mine_field, int rows, int cols, int mines_count) {
    int mines_placed = 0;

    while (mines_placed < mines_count) {
        int r = rand() % rows;
        int c = rand() % cols;

        if (mine_field[r][c] != 'X') {
            mine_field[r][c] = 'X';
            mines_placed++;
        }
    }
}

void CalculateNumbers(char** mine_field, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (mine_field[i][j] != 'X') {
                int count = CountBombsAround(mine_field, i, j, rows, cols);
                if (count > 0) {
                    mine_field[i][j] = '0' + count;
                }
            }
        }
    }
}

void ClearField(char** field, int rows) {
    if (!field) return;

    for (int i = 0; i < rows; i++) {
        free(field[i]);
    }
    free(field);
}

void PrintField(char** field, int rows, int cols, int show_numbers) {
    //show_numbers - это флаг, показывать ли координаты €чейки
    if (show_numbers) {
        printf("   ");
        for (int j = 0; j < cols; j++) {
            printf("%2d ", j + 1);
        }
        printf("\n");

        printf("   ");
        for (int j = 0; j < cols; j++) {
            printf("---");
        }
        printf("\n");
    }

    for (int i = 0; i < rows; i++) {
        if (show_numbers) {
            printf("%2d|", i + 1);
        }
        else {
            printf("  |");
        }

        for (int j = 0; j < cols; j++) {
            printf(" %c ", field[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

int CheckGameWin(char** mine_field, char** state_field,
    int rows, int cols, int mines_count, int flags_count) {

    int correctly_flagged = 0;
    int all_safe_opened = 1;

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (mine_field[i][j] == 'X') {
                if (state_field[i][j] == 'F') {
                    correctly_flagged++;
                }
            }
            else {
                if (state_field[i][j] != '1') {
                    all_safe_opened = 0;
                }
            }
        }
    }

    return (correctly_flagged == mines_count && flags_count == mines_count) || all_safe_opened;
}

void ClearInput() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}
