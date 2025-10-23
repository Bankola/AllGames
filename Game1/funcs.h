#ifndef FUNCS_H
#define FUNCS_H

// Основные функции
int EndProgram();
void PrintEndMenu(int score, int total, int wins, int defeats);
void StartMainGame();
void IncorrectInput();
void InputInfoToFile(int score, int total, int wins, int defeats);

// Настройки
void SettingColors(int* Flag, int* score, int* total, int* wins, int* defeats, int* user_choice);
void ChangeDifficult(int* Flag, int* difficult, int* user_choice);
void SettingsMenu(int* score, int* total, int* wins, int* defeats, int* difficult, int* Flag, int* user_choice);

// Игровые меню
void GamesMenu(int* score, int* total, int* wins, int* defeats, int* difficult, int* Flag, int* user_choice);
void GuessGameMenu(int* score, int* total, int* wins, int* defeats, int* difficult, int* Flag, int* user_choice);
void BullsCowsMenu(int* score, int* total, int* wins, int* defeats, int* user_choice, int* Flag);
void MainMenu();
void StartProgram();

// Компьютерный режим
void ComputerModeHard(int* score, int* total, int* wins, int* defeats);
void ComputerModeNormal(int* score, int* total, int* wins, int* defeats);
void ComputerModeEasy(int* score, int* total, int* wins, int* defeats);
void PlayComputerMode(int* score, int* total, int* wins, int* defeats, int difficult);
int GetBackChoice(int* user_choice);

//Быки и коровы
void StartBullsCows(int* score, int* total, int* wins, int* defeats, int* user_choice, int* Flag);
int UserNumberDivision(int* user_number);
int ComputerNumberDivision(int* computer_number);
int CountBulls(int user_number, int computer_number);
int CountCows(int user_number, int computer_number);
#endif