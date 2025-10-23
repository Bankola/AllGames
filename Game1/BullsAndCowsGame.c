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
        printf("1.Start game \n"
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
            printf("That's button don`t working :) Try later.\n");
            break;
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


void StartBullsCows(int* score, int* total, int* wins, int* defeats, int* user_choice, int* Flag) {
    *user_choice = -1;
    srand(time(NULL));
    int count = 0;
    int user_number = -1;
    int computer_number = 1000 + rand() % 9000; 
    while (user_number != computer_number) {
        do {
            system("pause");
            system("cls");
            printf("Enter the number that you think the computer chose (1000 - 9999):\n");
            printf("Computer number was: %d\n", computer_number);
            scanf_s("%d", &user_number);
            if (user_number < 1000 || user_number > 9999) {
                printf("Incorrect input. Use number 1000 - 9999.\n");
            }
        } while (user_number < 1000 || user_number > 9999);
        count += 1;
        int bulls = CountBulls(user_number, computer_number);
        int cows = CountCows(user_number, computer_number);
        printf("Bulls: %d\n", bulls);
        printf("Cows: %d\n", cows);
    }
    printf("You're right!\n");
    if (count == 1) {
        printf("Unbelievable! On the first try!\n");
        *total += 1;
        *wins += 1;
        *score += 100;
        printf("You can try again!\n");
    }
    else if (count < 7) {
        printf("Good work!\n");
        *total += 1;
        *wins += 1;
        *score += 50;
        printf("You can try again!\n");
    }
    else if (count >= 7) {
        printf("Bad, bad ,bad!\n");
        *total += 1;
        *defeats += 1;
        *score += 25;
        printf("You can try again!\n");
    }
}//work

int UserNumberDivision(int* user_number) {
    int user_part = *user_number % 10;
    *user_number = *user_number / 10;
    return user_part;
}//work

int ComputerNumberDivision(int* computer_number) {
    int computer_part = *computer_number % 10;
    *computer_number = *computer_number / 10;
    return computer_part;
}//work

int CountBulls(int user_number, int computer_number) {
    int Bulls = 0;
    int user_temp = user_number;  
    int comp_temp = computer_number;
    while (user_temp > 0 && comp_temp > 0) {
        int a = ComputerNumberDivision(&comp_temp);  
        int b = UserNumberDivision(&user_temp);   
        if (a == b) {
            Bulls += 1;
        }
    }
    return Bulls;
}//work

int CountCows(int user_number, int computer_number) {
    int Cows = 0;
    int total_matches = 0;
    int user_temp = user_number;
    for (int i = 0; i < 4; i++) {
        int user_digit = user_temp % 10;
        user_temp = user_temp / 10;
        int comp_temp = computer_number;
        for (int j = 0; j < 4; j++) {
            int comp_digit = comp_temp % 10;
            comp_temp = comp_temp / 10;
            if (user_digit == comp_digit) {
                total_matches++;
                break; 
            }
        }
    }
    int bulls = CountBulls(user_number, computer_number);
    Cows = total_matches - bulls;
    return Cows;
}//work

void Information() {
    printf("");
}// in working