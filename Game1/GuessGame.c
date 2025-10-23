#include "funcs.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>


void GuessGameMenu(int* score, int* total, int* wins, int* defeats, int* difficult, int* Flag, int* user_choice) {
    *user_choice = -1;
    while (*user_choice != 1 && *user_choice != 2 && *user_choice != 3 && *user_choice != 0) {
        system("pause");
        system("cls");
        printf("**GUESS GAME**\n");
        printf("Choose game mode:\n"
            "1.Computer mode\n"
            "2.User mode\n"
            "3.Back\n"
            "0.Exit\n");

        if (*difficult == 1) {
            printf("Difficult - HARD\n");
        }
        else if (*difficult == 2) {
            printf("Difficult - NORMAL\n");
        }
        else {
            printf("Difficult - EASY\n");
        }

        scanf_s("%d", user_choice);

        switch (*user_choice) {
        case 1:
            PlayComputerMode(score, total, wins, defeats, *difficult);
            *user_choice = -1;
            break;
        case 2:
            printf("User mode\n");
            system("pause");
            *user_choice = -1;
            break;
        case 3:
            *user_choice = -1;
            return;
        case 0:
            *Flag = EndProgram();
            break;
        default:
            IncorrectInput();
            continue;
        }

        if (*Flag == 0) {
            PrintEndMenu(*score, *total, *wins, *defeats);
            break;
        }
    }
}//work

void PlayComputerMode(int* score, int* total, int* wins, int* defeats, int difficult) {
    switch (difficult) {
    case 1:
        ComputerModeHard(score, total, wins, defeats);
        break;
    case 2:
        ComputerModeNormal(score, total, wins, defeats);
        break;
    case 3:
        ComputerModeEasy(score, total, wins, defeats);
        break;
    }
}//work

void ComputerModeHard(int* score, int* total, int* wins, int* defeats) {
    int low = 1;
    int high = 100;
    int guess;
    int attempts = 0;
    char response;

    system("cls");
    printf("***COMPUTER MODE - HARD***\n");
    printf("Pick a number between 1 and 100.\n");
    printf("Answer: 'b' - more, 'm' - less, 'y' - guessed correctly\n\n");

    while (getchar() != '\n'); // Очистка буфера

    do {
        guess = (low + high) / 2;
        attempts++;

        printf("Attempts %d: Computer: This number is %d?\n", attempts, guess);
        printf("You answer (b/m/y): ");
        scanf_s(" %c", &response);

        switch (response) {
        case 'b': case 'B':
            low = guess + 1;
            break;
        case 'm': case 'M':
            high = guess - 1;
            break;
        case 'y': case 'Y':
            printf("\nThe computer guessed your number %d in %d attempts!\n", guess, attempts);
            break;
        default:
            printf("Incorrect input! Use b/m/y\n");
            attempts--;
            continue;
        }

        if (low > high) {
            printf("\nYou're cheating!\n");
            break;
        }

    } while (response != 'y' && response != 'Y' && attempts != 6);

    // Подсчет очков для Hard
    if (response == 'y' || response == 'Y') {
        *total += 1;
        *defeats += 1;
        if (attempts < 4) {
            printf("Your score +25!\n");
            *score += 25;
        }
        else if (attempts == 5) {
            printf("Your score +50!\n");
            *score += 50;
        }
        else if (attempts == 6) {
            printf("Your score +75!\n");
            *score += 75;
        }
    }
    else {
        *total += 1;
        *wins += 1;
        printf("Computer didn't guess the number in %d attempts!\n", attempts);
    }
    InputInfoToFile(score, total, wins, defeats);
    GetBackChoice(NULL);
}//work

void ComputerModeNormal(int* score, int* total, int* wins, int* defeats) {
    int low = 1;
    int high = 100;
    int guess;
    int attempts = 0;
    char response;
    int max_attempts = 10;

    system("cls");
    printf("***COMPUTER MODE - NORMAL***\n");
    printf("Pick a number between 1 and 100.\n");
    printf("Answer: 'b' - more, 'm' - less, 'y' - guessed correctly\n\n");

    srand(time(NULL));
    while (getchar() != '\n');

    do {
        guess = low + rand() % (high - low + 1);
        attempts++;

        printf("Attempts %d: Computer: This number is %d?\n", attempts, guess);
        printf("You answer (b/m/y): ");
        scanf_s(" %c", &response);

        switch (response) {
        case 'b': case 'B':
            low = guess + 1;
            break;
        case 'm': case 'M':
            high = guess - 1;
            break;
        case 'y': case 'Y':
            printf("\nThe computer guessed your number %d in %d attempts!\n", guess, attempts);
            break;
        default:
            printf("Incorrect input! Use b/m/y\n");
            attempts--;
            continue;
        }

        if (low > high) {
            printf("\nYou're cheating!\n");
            break;
        }

    } while (response != 'y' && response != 'Y' && attempts != max_attempts);

    // Подсчет очков для Normal
    if (response == 'y' || response == 'Y') {
        *total += 1;
        *defeats += 1;
        if (attempts <= 4) {
            printf("Your score +75!\n");
            *score += 75;
        }
        else if (attempts <= 7) {
            printf("Your score +50!\n");
            *score += 50;
        }
        else {
            printf("Your score +25!\n");
            *score += 25;
        }
    }
    else {
        *total += 1;
        *wins += 1;
        printf("Computer didn't guess the number in %d attempts!\n", max_attempts);
    }
    InputInfoToFile(*score, *total, *wins, *defeats);
    GetBackChoice(NULL);
}//work

void ComputerModeEasy(int* score, int* total, int* wins, int* defeats) {
    int guess;
    int attempts = 0;
    char response;
    int max_attempts = 10;

    system("cls");
    printf("***COMPUTER MODE - EASY***\n");
    printf("Pick a number between 1 and 100.\n");
    printf("Answer: 'b' - more, 'm' - less, 'y' - guessed correctly\n\n");

    srand(time(NULL));
    while (getchar() != '\n');

    do {
        guess = 1 + rand() % 100;
        attempts++;

        printf("Attempts %d: Computer: This number is %d?\n", attempts, guess);
        printf("You answer (b/m/y): ");
        scanf_s(" %c", &response);

        switch (response) {
        case 'b': case 'B':
        case 'm': case 'M':
            break;
        case 'y': case 'Y':
            printf("\nThe computer guessed your number %d in %d attempts!\n", guess, attempts);
            break;
        default:
            printf("Incorrect input! Use b/m/y\n");
            attempts--;
            continue;
        }

    } while (response != 'y' && response != 'Y' && attempts != max_attempts);

    // Подсчет очков для Easy
    if (response == 'y' || response == 'Y') {
        *total += 1;
        *defeats += 1;
        if (attempts <= 3) {
            printf("Your score +100!\n");
            *score += 100;
        }
        else if (attempts <= 6) {
            printf("Your score +75!\n");
            *score += 75;
        }
        else if (attempts <= 8) {
            printf("Your score +50!\n");
            *score += 50;
        }
        else {
            printf("Your score +25!\n");
            *score += 25;
        }
    }
    else {
        *total += 1;
        *wins += 1;
        printf("Computer didn't guess the number in %d attempts!\n", max_attempts);
    }

    GetBackChoice(NULL);
}//work

int GetBackChoice(int* user_choice) {
    int back_choice = -1;
    while (back_choice != 1) {
        system("pause");
        system("cls");
        printf("**GUESS GAME**\n");
        printf("1. Back to menu\n");
        printf("2. Exit\n");
        scanf_s("%d", &back_choice);

        if (back_choice == 1) {
            if (user_choice) *user_choice = -1;
            return 1;
        }
        else if (back_choice == 2) {
            printf("Completion the program..\n");
            system("pause");
            system("cls");
            return 0;
        }
        else {
            printf("Incorrect input! Choose 1 or 2.\n");
            back_choice = -1;
        }
    }
    return 1;
}//work