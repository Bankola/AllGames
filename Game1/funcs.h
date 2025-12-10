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
int CheckInfo(int card, char* revealed);
int CheckResult(int card1, int card2, char* board, int* revealed);
void ChooseFirstCard(int card1, char* board, char* revealed);
void ChooseSecondCard(int card1, int card2, char* board, char* revealed);
void Shuffle(char* mass, int size);
void InitializeBoard(char* board);
void PrintBoard(char* board, int* revealed);
int MakeMove(char* board, int* revealed);
int AllCardsFound(int* revealed);
void Delay(int milliseconds);
void ClearScreen();

//Сапёр
char** CreateMineField(int rows, int cols, int mines_count);
char** CreateDisplayField(int rows, int cols);
char** CreateStateField(int rows, int cols);
void ClearField(char** field, int rows);
void CreateMines(char** mine_field, int rows, int cols, int mines_count);
void CalculateNumbers(char** mine_field, int rows, int cols);
void PrintField(char** field, int rows, int cols, int show_numbers);
void ClearInput();
int MakeMoveSapper(char** mine_field, char** display_field, char** state_field, int rows, int cols, int mines_count, int* flags_count, int row, int col, char command);
void RecursiveReveal(char** mine_field, char** display_field, char** state_field, int rows, int cols, int row, int col);
int CheckGameWin(char** mine_field, char** state_field, int rows, int cols, int mines_count, int flags_count);
int CountBombsAround(char** mine_field, int row, int col, int rows, int cols);
int IsValidCell(int row, int col, int rows, int cols);
#endif