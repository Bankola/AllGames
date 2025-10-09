#ifndef FUNCS_H
#define FUNCS_H

// Основные функции
int end_program();
void print_end_menu(int score, int total, int wins, int defeats);
void start_main_game();
void incorrect_input();
void InputInfoToFile(int score, int total, int wins, int defeats);

// Настройки
void setting_colors(int* Flag, int* score, int* total, int* wins, int* defeats, int* user_choice);
void change_difficult(int* Flag, int* difficult, int* user_choice);
void settings_menu(int* score, int* total, int* wins, int* defeats, int* difficult, int* Flag, int* user_choice);

// Игровые меню
void play_menu(int* score, int* total, int* wins, int* defeats, int* difficult, int* Flag, int* user_choice);
void guess_game_menu(int* score, int* total, int* wins, int* defeats, int* difficult, int* Flag, int* user_choice);
void BullsCowsMenu(int* score, int* total, int* wins, int* defeats, int* user_choice, int* Flag);
void MainMenu();
void StartStatistics();

// Компьютерный режим
void computer_mode_hard(int* score, int* total, int* wins, int* defeats);
void computer_mode_normal(int* score, int* total, int* wins, int* defeats);
void computer_mode_easy(int* score, int* total, int* wins, int* defeats);
void play_computer_mode(int* score, int* total, int* wins, int* defeats, int difficult);
int get_back_choice(int* user_choice);

//Быки и коровы
void StartBullsCows(int* score, int* total, int* wins, int* defeats, int* user_choice, int* Flag);
int UserNumberDivision(int* user_number);
int ComputerNumberDivision(int* computer_number);
int CountBulls(int user_number, int computer_number);
int CountCows(int user_number, int computer_number);
#endif