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


void print_end_menu(int score, int total, int wins, int defeats) {
    printf("***THE END***\n\n");
    printf("YOUR SCORE: %d\n", score);
    printf("TOTAL GAMES: %d\n", total);
    printf("WINS: %d\n", wins);
    printf("DEFEATS: %d\n", defeats);
    system("pause");
    system("cls");
}//work


void start_main_game() {
    system("pause");
    system("cls");
    int door_game = -1;
    while (door_game != 1 && door_game != 2 && door_game != 3) {
        system("cls");
        printf("***MAIN GAME***\n");
        printf("Welcome to my game!\n");
        printf("Choose the door\n");
        printf("=====  =====  =====\n"
            "|   |  |   |  |   |\n"
            "| 1 |  | 2 |  | 3 |\n"
            "|   |  |   |  |   |\n"
            "=====  =====  =====\n");
        scanf_s("%d", &door_game);
        switch (door_game) {
        case 1:
            printf("You died by monster!\n");
            break;
        case 2:
            printf("U find a lot of money!$$$$\n");
            break;
        case 3:
            printf("You find new 3 doors..\n");
            system("pause");
            door_game = -1;
            while (door_game != 1 && door_game != 2 && door_game != 3 && door_game != 4) {
                system("cls");
                printf("=====  =====  =====\n"
                    "|   |  |   |  |   |\n"
                    "| 1 |  | 2 |  | 3 |\n"
                    "|   |  |   |  |   |\n"
                    "=====  =====  =====\n");
                printf("Choose the door\n");
                scanf_s("%d", &door_game);
                switch (door_game) {
                case 1:
                    system("cls");
                    printf("You find a toy\n");
                    printf("   ___   \n"
                        "  |   |   \n"
                        "=========\n"
                        "| |   | |\n"
                        "| |   | |\n"
                        "| |   | |\n"
                        "+=======+\n"
                        " |     |\n"
                        " |     |\n"
                        " |     |\n"
                        "==     ==\n");
                    break;
                case 2:
                    system("cls");
                    printf("The new world\n");
                    printf("You can go out..\n");
                    break;
                case 3:
                    system("cls");
                    printf("You find your death\n");
                    break;
                case 4:
                    system("cls");
                    printf("Secret final, your family right here.\n");
                    break;
                default:
                    printf("Incorrect input\n");
                    continue;
                }
            }
            break;
        default:
            printf("Input correct number of door\n");
            continue;
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
}