#include "funcs.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

void StartMainGame() {
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