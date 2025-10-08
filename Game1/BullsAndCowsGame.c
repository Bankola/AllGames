#include "funcs.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

void BullsCowsMenu(int* score, int* total, int* wins, int* defeats, int* user_choice, int* Flag) {
	*user_choice = -1;
    while (*user_choice != 1 && *user_choice != 2 && *user_choice != 3 && *user_choice != 0) {
        system("pause");
        system("cls");
        printf("**BULLS AND COWS**\n");
        printf("1.Start game. \n"
        "2.Back\n"
        "3.Info\n"
        "0.Exit\n");
        scanf_s("%d", user_choice);
        switch (*user_choice) {
        case 1:
            StartBullsCows(score, total, wins, defeats, user_choice, Flag);
            *user_choice = -1;
            break;
        case 2:
            *user_choice = -1;
            return;
        case 3:
            printf("Info about game\n");
            break;
        case 0:
            *Flag = end_program();
            break;
        default:
            incorrect_input();
            continue;
        }
        if (*Flag == 0) {
            print_end_menu(*score, *total, *wins, *defeats);
            break;
        }
    }
}//work


void StartBullsCows(int* score, int* total, int* wins, int* defeats, int* user_choice, int* Flag) {
    *user_choice = -1;
    srand(time(NULL));
    int user_number;
    int computer_number = 1 + rand() % 10000;
    do {
        system("pause");
        system("cls");
        printf("Enter the number that you think the computer chose (1- 10000):\n");
        scanf_s("%d", &user_number);
        if (user_number < 0 || user_number > 10000) {
            printf("Incorrect input. Use number 1-10000.\n");
        }
        else {
            printf("continue");
        }
    } while (user_number < 0 || user_number> 10000);
}

//int UserNumberDivision