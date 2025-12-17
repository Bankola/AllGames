#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>  
#include "funcs.h"

#define FIELD_SIZE 3
#define EMPTY_CELL ' '

int random_initialized = 0;

void clear_screen() {
    system("cls");  
}

void delay(int milliseconds) {
    Sleep(milliseconds); 
}

void initialize_game(char*** field, char* player_char, char* computer_char, int* player_turn) {
    *field = (char**)malloc(FIELD_SIZE * sizeof(char*));
    for (int i = 0; i < FIELD_SIZE; i++) {
        (*field)[i] = (char*)malloc(FIELD_SIZE * sizeof(char));
        for (int j = 0; j < FIELD_SIZE; j++) {
            (*field)[i][j] = EMPTY_CELL;
        }
    }

    if (coin_toss()) {
        *player_char = 'X';
        *computer_char = 'O';
        *player_turn = 1; 
        printf("You are playing as X (crosses) and move first!\n");
    }
    else {
        *player_char = 'O';
        *computer_char = 'X';
        *player_turn = 0; 
        printf("You are playing as O (noughts). Computer moves first!\n");
    }
    delay(2000);  
    clear_screen();
}

void cleanup_game(char** field) {
    if (field != NULL) {
        for (int i = 0; i < FIELD_SIZE; i++) {
            free(field[i]);
        }
        free(field);
    }
}

int coin_toss() {
    if (!random_initialized) {
        srand(time(NULL));
        random_initialized = 1;
    }
    return rand() % 2 == 0;
}

void draw_field(char** field) {
    clear_screen();
    printf("=== Tic-Tac-Toe ===\n\n");
    printf("   0   1   2\n");
    printf("  --- --- ---\n");

    for (int i = 0; i < FIELD_SIZE; i++) {
        printf("%d|", i);
        for (int j = 0; j < FIELD_SIZE; j++) {
            printf(" %c |", field[i][j]);
        }
        printf("\n");
        printf("  --- --- ---\n");
    }
    printf("\n");
}

int is_valid_move(char** field, int row, int col) {
    if (row >= 0 && row < FIELD_SIZE &&
        col >= 0 && col < FIELD_SIZE &&
        field[row][col] == EMPTY_CELL) {
        return 1;
    }
    return 0;
}

int make_move(char** field, int row, int col, char symbol) {
    if (is_valid_move(field, row, col)) {
        field[row][col] = symbol;
        return 1;
    }
    return 0;
}

void make_player_move(char** field, char player_char) {
    int row, col;
    int valid_move = 0;

    while (!valid_move) {
        printf("Your turn. Enter row and column (0-2): ");
        if (scanf_s("%d %d", &row, &col) != 2) {
            printf("Invalid input. Try again.\n");
            while (getchar() != '\n');
            continue;
        }

        if (make_move(field, row, col, player_char)) {
            valid_move = 1;
        }
        else {
            printf("Invalid move. Try again.\n");
        }
    }

    draw_field(field);
    delay(1000);  
}

int check_win(char** field, char symbol) {
    for (int i = 0; i < FIELD_SIZE; i++) {
        if (field[i][0] == symbol && field[i][1] == symbol && field[i][2] == symbol) {
            return 1;
        }
    }

    for (int j = 0; j < FIELD_SIZE; j++) {
        if (field[0][j] == symbol && field[1][j] == symbol && field[2][j] == symbol) {
            return 1;
        }
    }

    if (field[0][0] == symbol && field[1][1] == symbol && field[2][2] == symbol) {
        return 1;
    }

    if (field[0][2] == symbol && field[1][1] == symbol && field[2][0] == symbol) {
        return 1;
    }

    return 0;
}

int check_draw(char** field) {
    for (int i = 0; i < FIELD_SIZE; i++) {
        for (int j = 0; j < FIELD_SIZE; j++) {
            if (field[i][j] == EMPTY_CELL) {
                return 0;
            }
        }
    }
    return 1;
}

int count_empty_cells(char** field) {
    int count = 0;
    for (int i = 0; i < FIELD_SIZE; i++) {
        for (int j = 0; j < FIELD_SIZE; j++) {
            if (field[i][j] == EMPTY_CELL) {
                count++;
            }
        }
    }
    return count;
}

int minimax(char** field, int depth, int is_maximizing, char computer_char, char player_char) {
    if (check_win(field, computer_char)) {
        return 10 - depth;
    }
    if (check_win(field, player_char)) {
        return depth - 10;
    }
    if (check_draw(field)) {
        return 0;
    }

    if (is_maximizing) {
        int max_eval = -1000;
        for (int i = 0; i < FIELD_SIZE; i++) {
            for (int j = 0; j < FIELD_SIZE; j++) {
                if (field[i][j] == EMPTY_CELL) {
                    field[i][j] = computer_char;
                    int eval = minimax(field, depth + 1, 0, computer_char, player_char);
                    field[i][j] = EMPTY_CELL;
                    if (eval > max_eval) {
                        max_eval = eval;
                    }
                }
            }
        }
        return max_eval;
    }
    else {
        int min_eval = 1000;
        for (int i = 0; i < FIELD_SIZE; i++) {
            for (int j = 0; j < FIELD_SIZE; j++) {
                if (field[i][j] == EMPTY_CELL) {
                    field[i][j] = player_char;
                    int eval = minimax(field, depth + 1, 1, computer_char, player_char);
                    field[i][j] = EMPTY_CELL;
                    if (eval < min_eval) {
                        min_eval = eval;
                    }
                }
            }
        }
        return min_eval;
    }
}

int* find_best_move(char** field, char computer_char, char player_char) {
    int best_val = -1000;
    static int best_move[2];
    best_move[0] = -1;
    best_move[1] = -1;

    for (int i = 0; i < FIELD_SIZE; i++) {
        for (int j = 0; j < FIELD_SIZE; j++) {
            if (field[i][j] == EMPTY_CELL) {
                field[i][j] = computer_char;
                int move_val = minimax(field, 0, 0, computer_char, player_char);
                field[i][j] = EMPTY_CELL;

                if (move_val > best_val) {
                    best_move[0] = i;
                    best_move[1] = j;
                    best_val = move_val;
                }
            }
        }
    }
    return best_move;
}

void make_computer_move(char** field, char computer_char, char player_char, int difficulty) {
    printf("Computer is thinking...\n");
    delay(1500);  

    if (difficulty == 1) {
        int row, col;
        do {
            row = rand() % FIELD_SIZE;
            col = rand() % FIELD_SIZE;
        } while (!is_valid_move(field, row, col));

        make_move(field, row, col, computer_char);
        printf("Computer moved: %d %d\n", row, col);
    }
    // 70% optimal, 30% random
    else if (difficulty == 2) {
        if (rand() % 100 < 70) {
            int* best_move = find_best_move(field, computer_char, player_char);
            if (best_move[0] != -1 && best_move[1] != -1) {
                make_move(field, best_move[0], best_move[1], computer_char);
                printf("Computer moved: %d %d\n", best_move[0], best_move[1]);
            }
        }
        else {
            int row, col;
            do {
                row = rand() % FIELD_SIZE;
                col = rand() % FIELD_SIZE;
            } while (!is_valid_move(field, row, col));

            make_move(field, row, col, computer_char);
            printf("Computer moved: %d %d\n", row, col);
        }
    }
    else if (difficulty == 3) {
        int* best_move = find_best_move(field, computer_char, player_char);
        if (best_move[0] != -1 && best_move[1] != -1) {
            make_move(field, best_move[0], best_move[1], computer_char);
            printf("Computer moved: %d %d\n", best_move[0], best_move[1]);
        }
    }

    draw_field(field);
    delay(1000);
}

void play_game(int* difficulty) {
    char** field = NULL;
    char player_char, computer_char;
    int player_turn;

    clear_screen();
    printf("=== Tic-Tac-Toe ===\n");
    printf("Difficulty level: ");
    switch (*difficulty) {
    case 1: printf("Easy\n"); break;
    case 2: printf("Medium\n"); break;
    case 3: printf("Hard\n"); break;
    }

    initialize_game(&field, &player_char, &computer_char, &player_turn);

    int game_over = 0;

    while (!game_over) {
        draw_field(field);

        if (player_turn) {
            make_player_move(field, player_char);

            if (check_win(field, player_char)) {
                draw_field(field);
                printf("Congratulations! You won!\n");
                game_over = 1;
            }
            else if (check_draw(field)) {
                draw_field(field);
                printf("Draw!\n");
                game_over = 1;
            }
            else {
                player_turn = 0;
            }
        }
        else {
            make_computer_move(field, computer_char, player_char, *difficulty);

            if (check_win(field, computer_char)) {
                draw_field(field);
                printf("Computer won!\n");
                game_over = 1;
            }
            else if (check_draw(field)) {
                draw_field(field);
                printf("Draw!\n");
                game_over = 1;
            }
            else {
                player_turn = 1;
            }
        }
    }

    delay(2000);  
    cleanup_game(field);
    printf("Thank you for playing!\n");
}