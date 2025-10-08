#pragma once
//#pragma once
#ifndef FUNCS_H
#define FUNCS_H


void print_end_menu(int score, int total, int wins, int defeats);
int end_program();
void start_main_game();
void incorrect_input();
void setting_colors(int* Flag, int* score, int* total, int* wins, int* defeats, int* user_choice);
void change_difficult(int* Flag, int* difficult, int* user_choice);
void settings_menu(int* score, int* total, int* wins, int* defeats, int* difficult, int* Flag, int* user_choice);
#endif
