#ifndef FUNCS_H
#define FUNCS_H

// Основные функции
int EndProgram();
void PrintEndMenu(int score, int total, int wins, int defeats);
void StartMainGame();
void IncorrectInput();

// Настройки
void SettingColors(int* Flag, int* score, int* total, int* wins, int* defeats, int* user_choice);
void ChangeDifficult(int* Flag, int* difficult, int* user_choice);
void SettingsMenu(int* score, int* total, int* wins, int* defeats, int* difficult, int* Flag, int* user_choice);

// Игровые меню
void GamesMenu(int* score, int* total, int* wins, int* defeats, int* difficult, int* Flag, int* user_choice);
void GuessGameMenu(int* score, int* total, int* wins, int* defeats, int* difficult, int* Flag, int* user_choice);
void BullsCowsMenu(int* score, int* total, int* wins, int* defeats, int* user_choice, int* Flag);
void StartProgram();

// Компьютерный режим
void PlayComputerMode(int* score, int* total, int* wins, int* defeats, int difficult);
int GetBackChoice(int* user_choice);

//Быки и коровы
void StartBullsCows(int* score, int* total, int* wins, int* defeats, int* user_choice, int* Flag);
int UserNumberDivision(int* user_number);
int ComputerNumberDivision(int* computer_number);
int CountBulls(int user_number, int computer_number);
int CountCows(int user_number, int computer_number);

//Мемо
int StartMEMO(int* difficult);
void Shuffle(char* mass, int size);
void InitializeBoard(char* board);
void PrintBoard(char* board, int* revealed);
int MakeMove(char* board, int* revealed);
int AllCardsFound(int* revealed);
void Delay(int milliseconds);
void ClearScreen();

//Сапёр
char** CreateRevealMassive(int rows, int cols);
char** CreateFalseMassive(int rows, int cols);
char** CreateMassive(int rows, int cols, int MinesCount);
int MakeStep(int rows, int cols, int user_row, int user_cols, int user_command, char** reveal, char** massive, char** Fmassive);
void Shuffle2nd(char** matrix, int rows, int cols);
void PrintMassive(char** matrix, int rows, int cols);
void FreeMassive(char** matrix, int rows);
void CountBombs(char** massive, int rows, int cols);
#endif