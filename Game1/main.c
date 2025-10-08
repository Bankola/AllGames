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