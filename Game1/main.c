#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include "funcs.h"

int main() {
    int defeats = 0;
    int wins = 0;
    int total = 0;
    int score = 0;
    int user_choice = -1;
    int Flag = 1;
    int difficult = 2; //Normal
    int door_game = -1;
    while (user_choice != 1 && user_choice != 2 && user_choice != 0) {
        printf("**MAIN MENU**\n");
        printf("1.Play\n"
            "2.Settings\n"
            "0.Exit\n");
        scanf_s("%d", &user_choice);
        switch (user_choice) {
        case 1:
            user_choice = -1;
            while (user_choice != 1 && user_choice != 2 && user_choice != 3 && user_choice != 0) {
                system("pause");
                system("cls");
                printf("**GAMES MENU**\n");
                printf("1.Guess Game\n"
                    "2.Main Game\n"
                    "3.Back\n"
                    "0.Exit\n");
                scanf_s("%d", &user_choice);
                switch (user_choice) {
                case 1:
                    user_choice = -1;
                    while (user_choice != 1 && user_choice != 2 && user_choice != 3 && user_choice != 0) {
                        system("pause");
                        system("cls");
                        printf("**GUESS GAME**\n");
                        printf("Choose game mode:\n"
                            "1.Computer mode\n"
                            "2.User mode\n"
                            "3.Back\n"
                            "0.Exit\n");
                        if (difficult == 1) {
                            printf("Difficult - HARD\n");
                        }
                        else if (difficult == 2) {
                            printf("Difficult - NORMAL\n");
                        }
                        else {
                            printf("Difficult - EASY\n");
                        }
                        scanf_s("%d", &user_choice);
                        switch (user_choice) {
                        case 1:
                            int low = 1;
                            int high = 100;
                            int guess;
                            int attempts = 0;
                            char response;
                            system("cls");
                            printf("***COMPUTER MODE***\n");
                            printf("Pick a number between 1 and 100.\n");
                            printf("Answer: 'b' - more, 'm' - less, 'y' - guessed correctly\n\n");
                            // Очистка буфера ввода
                            if (difficult == 1) {
                                while (getchar() != '\n');

                                do {
                                    guess = (low + high) / 2;
                                    attempts++;

                                    printf("Attempts %d: Computer: This number is %d?\n", attempts, guess);
                                    printf("You answer (b/m/y): ");
                                    scanf_s(" %c", &response);

                                    switch (response) {
                                    case 'b':  // Больше
                                    case 'B':
                                        low = guess + 1;
                                        break;
                                    case 'm':  // Меньше
                                    case 'M':
                                        high = guess - 1;
                                        break;
                                    case 'y':  // Угадал
                                    case 'Y':
                                        printf("\n The computer guessed your number %d in %d attempts!\n", guess, attempts);
                                        break;
                                    default:
                                        printf("Incorrect input! Use b/m/y\n");
                                        attempts--;  // Не считаем эту попытку
                                        continue;
                                    }
                                    if (low > high) {
                                        printf("\n You a lier!\n");
                                        break;
                                    }

                                } while (response != 'y' && response != 'Y' && attempts != 6);
                                if (attempts < 4) {
                                    total = total + 1;
                                    defeats = defeats + 1;
                                    printf("Your score +25!\n");
                                    score = score + 25;
                                }
                                else if (attempts == 5) {
                                    total = total + 1;
                                    defeats = defeats + 1;
                                    printf("Your score +50!\n");
                                    score = score + 50;
                                }
                                else if (attempts == 6) {
                                    total = total + 1;
                                    defeats = defeats + 1;
                                    printf("Your score +75!\n");
                                    score = score + 75;
                                }
                                else {
                                    total = total + 1;
                                    wins = wins + 1;
                                    printf("Computer didn't guess the number in %d attempts!\n", attempts);
                                }

                                int back_choice = -1;
                                while (back_choice != 1) {
                                    system("pause");
                                    system("cls");
                                    printf("**GUESS GAME**\n");
                                    printf("1. Back to menu\n");
                                    printf("2. Exit\n");
                                    scanf_s("%d", &back_choice);

                                    if (back_choice == 1) {
                                        // Возвращаемся в меню выбора режима Guess Game
                                        user_choice = -1;
                                        break;
                                    }
                                    else if (back_choice == 2) {
                                        printf("Completion the program..\n");
                                        system("pause");
                                        system("cls");
                                        printf("***THE END***\n\n");
                                        printf("YOUR SCORE: %d\n", score);
                                        printf("TOTAL GAMES: %d\n", total);
                                        printf("WINS: %d\n", wins);
                                        printf("DEFEATS: %d\n", defeats);
                                        system("pause");
                                        system("cls");
                                        return 0;
                                    }
                                    else {
                                        printf("Incorrect input! Choose 1 or 2.\n");
                                        back_choice = -1;
                                    }
                                }
                            }
                            else if (difficult == 2) {
                                srand(time(NULL));
                                while (getchar() != '\n');
                                int max_attempts = 10; // 10 попыток для Normal

                                do {
                                    // Генерируем случайное число из текущего интервала [low, high]
                                    guess = low + rand() % (high - low + 1);
                                    attempts++;

                                    printf("Attempts %d: Computer: This number is %d?\n", attempts, guess);
                                    printf("You answer (b/m/y): ");
                                    scanf_s(" %c", &response);

                                    switch (response) {
                                    case 'b':  // Больше
                                    case 'B':
                                        low = guess + 1; // Сужаем интервал снизу
                                        break;
                                    case 'm':  // Меньше
                                    case 'M':
                                        high = guess - 1; // Сужаем интервал сверху
                                        break;
                                    case 'y':  // Угадал
                                    case 'Y':
                                        printf("\nThe computer guessed your number %d in %d attempts!\n", guess, attempts);
                                        break;
                                    default:
                                        printf("Incorrect input! Use b/m/y\n");
                                        attempts--;  // Не считаем эту попытку
                                        continue;
                                    }

                                    if (low > high) {
                                        printf("\nYou're cheating!\n");
                                        break;
                                    }

                                } while (response != 'y' && response != 'Y' && attempts != max_attempts);
                                if (response == 'y' || response == 'Y') {
                                    if (attempts <= 4) {
                                        total = total + 1;
                                        defeats = defeats + 1;
                                        printf("Your score +75!\n");
                                        score = score + 75;
                                    }
                                    else if (attempts <= 7) {
                                        total = total + 1;
                                        defeats = defeats + 1;
                                        printf("Your score +50!\n");
                                        score = score + 50;
                                    }
                                    else {
                                        total = total + 1;
                                        defeats = defeats + 1;
                                        printf("Your score +25!\n");
                                        score = score + 25;
                                    }
                                }
                                else {
                                    total = total + 1;
                                    wins = wins + 1;
                                    printf("Computer didn't guess the number in %d attempts!\n", max_attempts);
                                }

                                int back_choice = -1;
                                while (back_choice != 1) {
                                    system("pause");
                                    system("cls");
                                    printf("**GUESS GAME**\n");
                                    printf("1. Back to menu\n");
                                    printf("2. Exit\n");
                                    scanf_s("%d", &back_choice);

                                    if (back_choice == 1) {
                                        // Возвращаемся в меню выбора режима Guess Game
                                        user_choice = -1;
                                        break;
                                    }
                                    else if (back_choice == 2) {
                                        printf("Completion the program..\n");
                                        system("pause");
                                        system("cls");
                                        printf("***THE END***\n\n");
                                        printf("YOUR SCORE: %d\n", score);
                                        printf("TOTAL GAMES: %d\n", total);
                                        printf("WINS: %d\n", wins);
                                        printf("DEFEATS: %d\n", defeats);
                                        system("pause");
                                        system("cls");
                                        return 0;
                                    }
                                    else {
                                        printf("Incorrect input! Choose 1 or 2.\n");
                                        back_choice = -1;
                                    }
                                }
                            }
                            else if (difficult == 3) {
                                srand(time(NULL));
                                while (getchar() != '\n');
                                int max_attempts = 10; // 10 попыток для Easy

                                do {
                                    // Генерируем случайное число от 1 до 100 (без сужения интервала)
                                    guess = 1 + rand() % 100;
                                    attempts++;

                                    printf("Attempts %d: Computer: This number is %d?\n", attempts, guess);
                                    printf("You answer (b/m/y): ");
                                    scanf_s(" %c", &response);

                                    switch (response) {
                                    case 'b':  // Больше
                                    case 'B':
                                        break;
                                    case 'm':  // Меньше
                                    case 'M':
                                        break;
                                    case 'y':  // Угадал
                                    case 'Y':
                                        printf("\nThe computer guessed your number %d in %d attempts!\n", guess, attempts);
                                        break;
                                    default:
                                        printf("Incorrect input! Use b/m/y\n");
                                        attempts--;  // Не считаем эту попытку
                                        continue;
                                    }

                                } while (response != 'y' && response != 'Y' && attempts != max_attempts);
                                if (response == 'y' || response == 'Y') {
                                    if (attempts <= 3) {
                                        total = total + 1;
                                        defeats = defeats + 1;
                                        printf("Your score +100!\n");
                                        score = score + 100;
                                    }
                                    else if (attempts <= 6) {
                                        total = total + 1;
                                        defeats = defeats + 1;
                                        printf("Your score +75!\n");
                                        score = score + 75;
                                    }
                                    else if (attempts <= 8) {
                                        total = total + 1;
                                        defeats = defeats + 1;
                                        printf("Your score +50!\n");
                                        score = score + 50;
                                    }
                                    else {
                                        total = total + 1;
                                        defeats = defeats + 1;
                                        printf("Your score +25!\n");
                                        score = score + 25;
                                    }
                                }
                                else {
                                    total = total + 1;
                                    wins = wins + 1;
                                    printf("Computer didn't guess the number in %d attempts!\n", max_attempts);
                                }

                                int back_choice = -1;
                                while (back_choice != 1) {
                                    system("pause");
                                    system("cls");
                                    printf("**GUESS GAME**\n");
                                    printf("1. Back to menu\n");
                                    printf("2. Exit\n");
                                    scanf_s("%d", &back_choice);

                                    if (back_choice == 1) {
                                        // Возвращаемся в меню выбора режима Guess Game
                                        user_choice = -1;
                                        break;
                                    }
                                    else if (back_choice == 2) {
                                        printf("Completion the program..\n");
                                        system("pause");
                                        system("cls");
                                        printf("***THE END***\n\n");
                                        printf("YOUR SCORE: %d\n", score);
                                        printf("TOTAL GAMES: %d\n", total);
                                        printf("WINS: %d\n", wins);
                                        printf("DEFEATS: %d\n", defeats);
                                        system("pause");
                                        system("cls");
                                        return 0;
                                    }
                                    else {
                                        printf("Incorrect input! Choose 1 or 2.\n");
                                        back_choice = -1;
                                    }
                                }
                            }
                            break;
                        case 2:
                            printf("User mode\n");
                            system("pause");
                            //next - game
                            user_choice = -1;
                            break;
                        case 3:
                            user_choice = -1;
                            break;
                        case 0:
                            Flag = end_program();
                            break;
                        default:
                            printf("Incorrect input\n");
                            system("pause");
                            system("cls");
                            continue;
                        }
                        if (user_choice == -1) {
                            break;
                        }
                        if (Flag == 0) {
                            print_end_menu(score, total, wins, defeats);
                            break;
                        }
                    }
                    break;
                case 2:
                    system("pause");
                    system("cls");
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
                    break;
                case 3:
                    system("cls");
                    continue;
                case 0:
                    Flag = end_program();
                    break;
                default:
                    printf("Incorrect input\n");
                    system("pause");
                    system("cls");
                    continue;
                }
                if (Flag == 0) {
                    print_end_menu(score, total, wins, defeats);
                    break;
                }
            }
            break;
        case 2:
            user_choice = -1;
            while (user_choice != 1 && user_choice != 2 && user_choice != 3 && user_choice != 0) {
                system("cls");
                printf("**SETTINGS**\n");
                printf("1.Difficult\n"
                    "2.Color\n"
                    "3.Back\n"
                    "0.Exit\n");
                scanf_s("%d", &user_choice);
                switch (user_choice) {
                case 1:
                    user_choice = -1;
                    while (user_choice != 1 && user_choice != 2 && user_choice != 3 && user_choice != 4 && user_choice != 0) {
                        system("pause");
                        system("cls");
                        printf("**DIFFICULT**\n");
                        printf("1.Hard\n"
                            "2.Normal\n"
                            "3.Easy\n"
                            "4.Back\n"
                            "0.Exit\n");
                        if (difficult == 1) {
                            printf("Now - Hard\n");
                        }
                        else if (difficult == 2) {
                            printf("Now - Normal\n");
                        }
                        else {
                            printf("Now - Easy\n");
                        }
                        scanf_s("%d", &user_choice);
                        switch (user_choice) {
                        case 1:
                            difficult = 1;//Hard
                            printf("New difficulty - Hard\n");
                            system("pause");
                            system("cls");
                            user_choice = -1;
                            continue;
                        case 2:
                            printf("The normal difficulty is set\n");
                            difficult = 2;//Normal
                            printf("New difficulty - Normal\n");
                            system("pause");
                            system("cls");
                            user_choice = -1;
                            continue;
                        case 3:
                            printf("A simple difficulty level has been set\n");
                            difficult = 3;//Easy
                            printf("New difficulty - Easy\n");
                            system("pause");
                            system("cls");
                            user_choice = -1;
                            continue;
                        case 4:
                            continue;
                        case 0:
                            Flag = end_program();
                            break;
                        default:
                            printf("Incorrect input\n");
                            system("pause");
                            system("cls");
                            continue;
                        }
                        if (user_choice == -1) {
                            break;
                        }
                        if (Flag == 0) {
                            print_end_menu(score, total, wins, defeats);
                            break;
                        }
                    }
                    break;
                case 2:
                    user_choice = -1;
                    while (user_choice != 1 && user_choice != 2 && user_choice != 3 && user_choice != 4 && user_choice != 0) {
                        system("cls");
                        printf("**COLORS**\n"
                            "1.Blue-White system\n"
                            "2.Green-Black system\n"
                            "3.Black-Purple\n"
                            "4.Back\n"
                            "0.Exit\n");
                        scanf_s("%d", &user_choice);
                        switch (user_choice) {
                        case 1:
                            system("color 17");
                            system("cls");
                            user_choice = -1;
                            continue;
                        case 2:
                            system("color 20");
                            system("cls");
                            user_choice = -1;
                            continue;
                        case 3:
                            system("color 5");
                            system("cls");
                            user_choice = -1;
                            continue;
                        case 4:
                            continue;
                        case 0:
                            Flag = end_program();
                            break;
                        default:
                            printf("Incorrect input\n");
                            system("pause");
                            system("cls");
                            continue;
                        }
                        if (user_choice == -1) {
                            break;
                        }
                        if (Flag == 0) {
                            print_end_menu(score, total, wins, defeats);
                            break;
                        }
                    }
                    break;
                case 3:
                    system("cls");
                    continue;
                case 0:
                    Flag = end_program();
                    break;
                default:
                    printf("Incorrect input\n");
                    system("pause");
                    system("cls");
                    continue;
                }
                if (Flag == 0) {
                    print_end_menu(score, total, wins, defeats);
                    break;
                }
            }
            break;
        case 0:
            Flag = end_program();
            print_end_menu(score, total, wins, defeats);
            break;
        default:
            printf("Incorrect input\n");
            system("pause");
            system("cls");
            continue;
        }
    }
}