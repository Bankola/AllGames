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
void ChooseCard(int card, char* board, char* revealed, char* text);
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
int MakeMoveSapper(char** mine_field, char** display_field, char** state_field,
    int rows, int cols, int mines_count, int* flags_count,
    int row, int col, char command, int* TrueFlagsCount);
void RecursiveReveal(char** mine_field, char** display_field, char** state_field, int rows, int cols, int row, int col);
int CheckGameWin(char** mine_field, char** state_field, int rows, int cols, int mines_count, int flags_count, int TrueFlagsCount);
int CountBombsAround(char** mine_field, int row, int col, int rows, int cols);
int IsValidCell(int row, int col, int rows, int cols);

//Крестики нолики
void clear_screen();
void delay(int milliseconds);
void play_game(int* difficulty);
void initialize_game(char*** field, char* player_char, char* computer_char, int* player_turn);
void cleanup_game(char** field);
int coin_toss();
void draw_field(char** field);
int is_valid_move(char** field, int row, int col);
int make_move(char** field, int row, int col, char symbol);
void make_player_move(char** field, char player_char);
int check_win(char** field, char symbol);
int check_draw(char** field);
int count_empty_cells(char** field);
int minimax(char** field, int depth, int is_maximizing, char computer_char, char player_char);
int* find_best_move(char** field, char computer_char, char player_char);
void make_computer_move(char** field, char computer_char, char player_char, int difficulty);

#endif