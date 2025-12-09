#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "funcs.h"
#include "utilities.h"
#define HIDDEN '-'
#define EMPTY ' '
#define SIZE 10

int StartMEMO(int* difficult) {
    srand(time(NULL));
    char board[10];//Все карты, по типу A,B,C и т.д.
    int revealed[10] = { 0 }; //массив вскрытых карт, 0-закрыта, 1-вскрыта
    int score = 0;
    int attempts = 0;
    int pairsFound = 0;
    int max_attempts;

    if (*difficult == 1) {
        max_attempts = 6;
    }
    else if (*difficult == 2) {
        max_attempts = 8;
    }
    else {
        max_attempts = 15;
    }

    printf("=== MEMO GAME ===\n");
    printf("Find all pairs of identical symbols!\n");
    printf("The cards are numbered from 1 to 10.\n");
    printf("Maximum attempts: %d\n\n", max_attempts);

    InitializeBoard(board);

    while (pairsFound < SIZE / 2 && attempts < max_attempts) {
#ifdef DEBUG
        printf("THE MASSIVE: ");
        for (int i = 0; i < SIZE; i++) {
            printf("%c ", board[i]);
        }
        printf("\n");
#endif
        printf("\nCurrent field:\n");
        PrintBoard(board, revealed);
        printf("\nPoints: %d, Attempts: %d/%d\n", score, attempts, max_attempts);

        if (MakeMove(board, revealed)) {
            score++;
            pairsFound++;
            printf("You've found a pair! Points: %d\n", score);
        }
        else {
            printf("The cards didn't match. Try again!\n");
        }

        attempts++;

        if (attempts >= max_attempts && pairsFound < SIZE / 2) {
            break;
        }

        Delay(2000);
        ClearScreen();
    }

    if (pairsFound == SIZE / 2) {
        printf("\nCONGRATULATIONS! You've found all the pairs!\n");
        printf("Final score: %d points\n", score);
        printf("Number of attempts: %d/%d\n", attempts, max_attempts);
    }
    else {
        printf("\nYour attempts are over!\n");
        printf("You found %d out of %d pairs\n", pairsFound, SIZE / 2);
        printf("Final score: %d points\n", score);
        printf("Attempts used: %d/%d\n", attempts, max_attempts);
    }

    return 0;
}

void Shuffle(char* mass, int size) {
    int i, j;
    char tmp;
    for (i = 0; i < size; i++) {
        j = rand() % size;
        tmp = mass[i];
        mass[i] = mass[j];
        mass[j] = tmp;
    }
}

void InitializeBoard(char* board) {
    char symbols[SIZE] = { 'A', 'A', 'B', 'B', 'C', 'C', 'D', 'D', 'E', 'E' };
    Shuffle(symbols, SIZE);

    for (int i = 0; i < SIZE; i++) {
        board[i] = symbols[i];
    }
}

void PrintBoard(char* board, int* revealed) {
    printf("+----+----+----+----+----+----+----+----+----+----+\n");
    printf("|");
    for (int i = 0; i < SIZE; i++) {
        printf(" %2d |", i + 1);
    }
    printf("\n+----+----+----+----+----+----+----+----+----+----+\n");
    printf("|");
    for (int i = 0; i < SIZE; i++) {
        if (revealed[i]) {
            printf("  %c |", board[i]);
        }
        else {
            printf("  ? |");
        }
    }
    printf("\n+----+----+----+----+----+----+----+----+----+----+\n");
}

int CheckInfo(int* revealed) {  // Изменен тип параметра с char* на int*
    int card;
    while (1) {
        printf("\nSelect the card (1-10): ");
        if (scanf_s("%d", &card) != 1) {
            printf("Input error! Enter a number between 1 and 10.\n");
            while (getchar() != '\n');
            continue;
        }
        if (card < 1 || card > 10) {  // Исправлено: было card < 0
            printf("Input error! Enter a number between 1 and 10.\n");
            continue;  // Исправлено: был return 0
        }
        if (revealed[card - 1]) {
            printf("This card is already open! Select another one.\n");
            continue;  // Исправлено: был return 0
        }
        return card;
    }
}
int CheckResult(int card1, int card2, char* board, int* revealed) {
    if (board[card1 - 1] == board[card2 - 1]) {
        printf("\nCOINCIDENCE! The cards remain open.\n");
        return 1;
    }
    else {
        printf("\nNOT MATCHED. The cards are hidden again.\n");
        revealed[card1 - 1] = 0;
        revealed[card2 - 1] = 0;
        return 0;
    }
}
int MakeMove(char* board, int* revealed) {
    int card1 = CheckInfo(revealed);
    if (card1 == 0) return 0;  
    ChooseFirstCard(card1, board, revealed);

    int card2 = CheckInfo(revealed);
    if (card2 == 0) {
        revealed[card1 - 1] = 0;
        return 0;
    }
    ChooseSecondCard(card1, card2, board, revealed);

    if (CheckResult(card1, card2, board, revealed)) {
        return 1;
    }
    else {
        return 0;
    }
}

void ChooseFirstCard(int card1, char* board, int* revealed) {  
    revealed[card1 - 1] = 1;
    ClearScreen();
    printf("\nThe first card: %c\n", board[card1 - 1]);
    printf("Current field:\n");
    PrintBoard(board, revealed);
}

void ChooseSecondCard(int card1, int card2, char* board, int* revealed) {  
    revealed[card2 - 1] = 1;
    ClearScreen();
    printf("\nFirst card: %c, Second card: %c\n",
        board[card1 - 1], board[card2 - 1]);
    printf("Current field:\n");
    PrintBoard(board, revealed);
}

int AllCardsFound(int* revealed) {
    for (int i = 0; i < SIZE; i++) {
        if (!revealed[i]) {
            return 0;
        }
    }
    return 1;
}

void Delay(int milliseconds) {
#ifdef _WIN32
    Sleep(milliseconds);
#else
    usleep(milliseconds * 1000);
#endif
}

void ClearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}