#include "funcs.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

int end_program() {
    system("cls");
    int x = 0;
    printf("Ending the program..\n");
    system("pause");
    system("cls");
    return x;
}//work

void InputInfoToFile(int score, int total, int wins, int defeats) {
    FILE* file = NULL;
    errno_t err;
    err = fopen_s(&file, "UserStatistics.txt", "w");
    fprintf(file, "Score: %d\n"
        "Total: %d\n"
        "Wins: %d\n"
        "Defeats: %d\n",
        score, total, wins, defeats);
    fclose(file);
}
void print_end_menu(int score, int total, int wins, int defeats) {
    printf("***THE END***\n\n");
    printf("YOUR SCORE: %d\n", score);
    printf("TOTAL GAMES: %d\n", total);
    printf("WINS: %d\n", wins);
    printf("DEFEATS: %d\n", defeats);
    system("pause");
    system("cls");
}//work


void play_menu(int* score, int* total, int* wins, int* defeats, int* difficult, int* Flag, int* user_choice) {
    *user_choice = -1;
    while (*user_choice != 1 && *user_choice != 2 && *user_choice != 3 && *user_choice != 0) {
        system("pause");
        system("cls");
        printf("**GAMES MENU**\n");
        printf("1.Guess Game\n"
            "2.Main Game\n"
            "3.Bulls and Cows\n"
            "4.Back\n"
            "0.Exit\n");
        scanf_s("%d", user_choice);

        switch (*user_choice) {
        case 1:
            guess_game_menu(score, total, wins, defeats, difficult, Flag, user_choice);
            break;
        case 2:
            start_main_game();
            break;
        case 3:
            BullsCowsMenu(score, total, wins, defeats, user_choice, Flag);
            break;
        case 4:
            system("cls");
            return;
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


void incorrect_input() {
    printf("Incorrect input\n");
    system("pause");
    system("cls");
}//work


void setting_colors(int* Flag, int* score, int* total, int* wins, int* defeats, int* user_choice) {
    while (*user_choice != 1 && *user_choice != 2 && *user_choice != 3 && *user_choice != 4 && *user_choice != 0) {
        system("cls");
        printf("**COLORS**\n"
            "1.Blue-White system\n"
            "2.Green-Black system\n"
            "3.Black-Purple\n"
            "4.Back\n"
            "0.Exit\n");
        scanf_s("%d", user_choice);
        switch (*user_choice) {
        case 1:
            system("color 17");
            system("cls");
            *user_choice = -1; 
            continue;
        case 2:
            system("color 20");
            system("cls");
            *user_choice = -1;  
            continue;
        case 3:
            system("color 5");
            system("cls");
            *user_choice = -1;  
            continue;
        case 4:
            return;
        case 0:
            *Flag = end_program();
            return;  
        default:
            incorrect_input();
            *user_choice = -1;  
            continue;
        }
    }
}//work


void change_difficult(int* Flag, int* difficult, int* user_choice) {
    while (*user_choice != 1 && *user_choice != 2 && *user_choice != 3 && *user_choice != 4 && *user_choice != 0) {
        system("pause");
        system("cls");
        printf("**DIFFICULT**\n");
        printf("1.Hard\n"
            "2.Normal\n"
            "3.Easy\n"
            "4.Back\n"
            "0.Exit\n");
        if (*difficult == 1) {
            printf("Now - Hard\n");
        }
        else if (*difficult == 2) {
            printf("Now - Normal\n");
        }
        else {
            printf("Now - Easy\n");
        }
        scanf_s("%d", user_choice);
        switch (*user_choice) {
        case 1:
            *difficult = 1;//Hard
            printf("New difficulty - Hard\n");
            system("pause");
            system("cls");
            *user_choice = -1;
            continue;
        case 2:
            printf("The normal difficulty is set\n");
            *difficult = 2;//Normal
            printf("New difficulty - Normal\n");
            system("pause");
            system("cls");
            *user_choice = -1;
            continue;
        case 3:
            printf("A simple difficulty level has been set\n");
            *difficult = 3;//Easy
            printf("New difficulty - Easy\n");
            system("pause");
            system("cls");
            *user_choice = -1;
            continue;
        case 4:
            return;  
        case 0:
            *Flag = end_program();  
            return;  
        default:
            incorrect_input();
            *user_choice = -1;  
            continue;
        }
    }
}//work


void settings_menu(int* score, int* total, int* wins, int* defeats, int* difficult, int* Flag, int* user_choice) {
    *user_choice = -1;
    while (*user_choice != 1 && *user_choice != 2 && *user_choice != 3 && *user_choice != 0) {
        system("cls");
        printf("**SETTINGS**\n");
        printf("1.Difficult\n"
            "2.Color\n"
            "3.Back\n"
            "0.Exit\n");
        scanf_s("%d", user_choice);
        switch (*user_choice) {
        case 1:
            *user_choice = -1;
            change_difficult(Flag, difficult, user_choice);
            if (*user_choice == -1) {
                break;
            }
            if (*Flag == 0) {  
                print_end_menu(*score, *total, *wins, *defeats);
                return;  
            }
            break;
        case 2:
            *user_choice = -1;
            setting_colors(Flag, score, total, wins, defeats, user_choice);
            if (*user_choice == -1) {
                break;
            }
            if (*Flag == 0) {  
                print_end_menu(*score, *total, *wins, *defeats);
                return;  
            }
            break;
        case 3:
            return;  
        case 0:
            *Flag = end_program();  
            if (*Flag == 0) {
                print_end_menu(*score, *total, *wins, *defeats);
                return;
            }
            break;
        default:
            incorrect_input();
            *user_choice = -1; 
            continue;
        }
        if (*Flag == 0) {  
            print_end_menu(*score, *total, *wins, *defeats);
            return;
        }
    }
}//work


void StartStatistics() {
    int user_choice = -1;
    FILE* file = NULL;
    errno_t err;
    while (user_choice != 1 && user_choice != 2) {
        printf("**MENU**\n");
        printf("1.New Game\n"
            "2.Continue\n");
        scanf_s("%d", &user_choice);
        switch (user_choice) {
        case 1:
            err = fopen_s(&file, "UserStatistics.txt", "w");
            fclose(file);
            system("pause");
            system("cls");
            MainMenu();
            break;
        case 2:
            err = fopen_s(&file, "UserStatistics.txt", "w");
            system("pause");
            system("cls");
            MainMenu();
            fclose(file);
            break;
        default:
            incorrect_input();
            continue;
        }
    }
}

void MainMenu() {
    
    int defeats = 0;
    int wins = 0;
    int total = 0;
    int score = 0;
    int user_choice = -1;
    int Flag = 1;
    int difficult = 2; // Normal

    while (user_choice != 1 && user_choice != 2 && user_choice != 0) {
        printf("**MAIN MENU**\n");
        printf("1.Play\n"
            "2.Settings\n"
            "0.Exit\n");
        scanf_s("%d", &user_choice);

        switch (user_choice) {
        case 1:
            play_menu(&score, &total, &wins, &defeats, &difficult, &Flag, &user_choice);
            break;
        case 2:
            settings_menu(&score, &total, &wins, &defeats, &difficult, &Flag, &user_choice);
            break;
        case 0:
            Flag = end_program();
            print_end_menu(score, total, wins, defeats);
            break;
        default:
            incorrect_input();
            continue;
        }
    }
    return 0;
}