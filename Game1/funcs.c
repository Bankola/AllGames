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