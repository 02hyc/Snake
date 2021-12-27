#include <stdio.h>
#include <Windows.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <mmsystem.h>
#pragma comment(lib, "Winmm.lib")

const int Height = 25;
const int Width = 60;
const int x_start = 30;
const int y_start = 3;
char where_to_go;
int start = 0;
bool foodmore = 1;
int Speed = 300;
int SCORE = 0;
int SELECTION = 0;
char pause;
char is_exit;

struct Snake
{
    int x_snake_body[1000];
    int y_snake_body[1000];
    int snakeLen;
} Snake;

struct where_is_food
{
    int x_food;
    int y_food;
} Where_is_food;

void LinkingStart(int x, int y);
void Initial(void);
void Map_creat(void);
void Snake_first(void);
void Moving(void);
void Moving_reverse(void);
void Random_food(void);
void Gamerun(void);
bool Gameover(void);

int main(void)
{

    Initial();
    Gamerun();

    return 0;
}

void Initial(void)
{
    printf("\n\n\n\n\n");
    Sleep(2);
    printf("\t\t\t\t\t  Enjoy This Game!\n\n");
    Sleep(2);
    printf("\t\t\t\t\t    Retro Snake.\n\n");
    Sleep(2);
    printf("\t\t\t\t\t Created By Yukino.\n\n");
    Sleep(2);
    printf("\t\tPress 'n' to start the normal game and Press 'r' to play the reverse one.\n\n");
    Sleep(2);
}

void Gamerun(void)
{
    while (!_kbhit())
    {
        fflush(stdin);
        char mode = _getch();
        if (mode == 'n')
        {
            SELECTION = 0;
            break;
        }
        if (mode == 'r')
        {
            SELECTION = 1;
            break;
        }
    }

    Sleep(500);

    for (int i = 0;; i++)
    {
        PlaySound(TEXT("bgm.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
        start = 0;
        SCORE = 0;
        foodmore = 1;
        Speed = 300;
        system("cls");
        Map_creat();
        Snake_first();
        while (1)
        {
            LinkingStart(x_start - 14, y_start);
            printf("SCORE : %d", SCORE);
            LinkingStart(x_start - 14, y_start + 2);
            printf("Pause : SPACE");
            LinkingStart(x_start - 14, y_start + 4);
            printf("EXIT : ESC");
            if (foodmore == 1)
            {
                Random_food();
            }

            if (GetAsyncKeyState(VK_ESCAPE))
            {
                system("cls");
                exit(0);
            }

            Sleep(Speed);
            if (SELECTION == 0)
            {
                Moving();
            }

            if (SELECTION == 1)
            {
                Moving_reverse();
            }

            if (Gameover() == 1)
            {
                PlaySound(TEXT("dead.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
                Sleep(5000);
                PlaySound(NULL, NULL, SND_FILENAME);
                system("cls");
                LinkingStart((Width + 2 * x_start) / 2 - 5, (Height + 2 * y_start) / 2 - 2);
                printf("You Lose It !\n");
                LinkingStart((Width + 2 * x_start) / 2 - 6, (Height + 2 * y_start) / 2);
                printf("Final Score = %d\n", SCORE);
                LinkingStart((Width + x_start) / 2 - 20, (Height + 2 * y_start) / 2 + 2);
                printf("Press ESC to exit or press ENTER to play normal or press SHIFT to play reverse.");
                break;
            }
        }

        while (1)
        {
            Sleep(100);
            if (GetAsyncKeyState(VK_ESCAPE) & 0x8000)
            {
                system("cls");
                exit(0);
            }
            if (GetAsyncKeyState(VK_RETURN) & 0x8000)
            {
                SELECTION = 0;
                break;
            }
            if (GetAsyncKeyState(VK_SHIFT) & 0x8000)
            {
                SELECTION = 1;
                break;
            }
        }
        continue;
    }
}

void LinkingStart(int x, int y)
{
    COORD pos = {
        x,
        y};
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cci;
    cci.dwSize = 100;
    cci.bVisible = FALSE;
    SetConsoleCursorInfo(hOut, &cci);
    SetConsoleCursorPosition(hOut, pos);
}

void Map_creat(void)
{

    LinkingStart((Width + x_start) / 2, (Height + y_start) / 2);
    printf("Loading......");

    for (int i = x_start - 1; i < Width + x_start + 2; i++)
    {
        LinkingStart(i, y_start - 2);
        Sleep(5);
        printf("-");
        LinkingStart(i, Height + y_start + 2);
        Sleep(5);
        printf("-");
    }

    for (int i = y_start - 2; i < Height + y_start + 1; i++)
    {
        LinkingStart(x_start - 1, i + 1);
        Sleep(10);
        printf("|");
        LinkingStart(Width + x_start + 1, i + 1);
        Sleep(10);
        printf("|");
    }

    LinkingStart((Width + x_start) / 2, (Height + y_start) / 2);
    printf("             ");
}

void Snake_first(void)
{
    Snake.x_snake_body[0] = (Width + x_start) / 2;
    Snake.y_snake_body[0] = (Height + y_start) / 2;
    Snake.snakeLen = 5;
    LinkingStart(Snake.x_snake_body[0], Snake.y_snake_body[0]);
    printf("o");
    for (int i = 1; i < 5; i++)
    {
        Snake.x_snake_body[i] = Snake.x_snake_body[i - 1];
        Snake.y_snake_body[i] = Snake.y_snake_body[i - 1] + 1;
        LinkingStart(Snake.x_snake_body[i], Snake.y_snake_body[i]);
        printf("*");
    }
}

void Moving(void)
{

    char keyboard = 0;

    if (start == 0)
    {
        where_to_go = 'w';
        start++;
    }

    if (_kbhit())
    {
        fflush(stdin);
        keyboard = _getch();
        if (keyboard == 'w' && where_to_go != 's')
        {
            where_to_go = 'w';
        }
        if (keyboard == 's' && where_to_go != 'w')
        {
            where_to_go = 's';
        }
        if (keyboard == 'a' && where_to_go != 'd')
        {
            where_to_go = 'a';
        }
        if (keyboard == 'd' && where_to_go != 'a')
        {
            where_to_go = 'd';
        }
        if (keyboard == ' ')
        {
            pause = ' ';
        }
    }
    fflush(stdin);
    if (pause == ' ')
    {
        pause = 0;
        LinkingStart(Snake.x_snake_body[Snake.snakeLen - 1], Snake.y_snake_body[Snake.snakeLen - 1]);
        printf("*");
        while (1)
        {
            Sleep(1000);
            if (_kbhit())
            {
                fflush(stdin);
                pause = _getch();
                if (pause == ' ')
                {
                    pause = 0;
                    break;
                }
                if (GetAsyncKeyState(VK_ESCAPE))
                {
                    system("cls");
                    exit(0);
                }
            }
        }
    }

    LinkingStart(Snake.x_snake_body[Snake.snakeLen - 1], Snake.y_snake_body[Snake.snakeLen - 1]);
    printf(" ");

    for (int i = Snake.snakeLen - 1; i > 0; i--)
    {
        Snake.x_snake_body[i] = Snake.x_snake_body[i - 1];
        Snake.y_snake_body[i] = Snake.y_snake_body[i - 1];
        LinkingStart(Snake.x_snake_body[i], Snake.y_snake_body[i]);
        printf("*");
    }

    if (where_to_go == 'w')
    {
        Snake.y_snake_body[0]--;
    }
    if (where_to_go == 's')
    {
        Snake.y_snake_body[0]++;
    }
    if (where_to_go == 'a')
    {
        Snake.x_snake_body[0]--;
    }
    if (where_to_go == 'd')
    {
        Snake.x_snake_body[0]++;
    }

    LinkingStart(Snake.x_snake_body[0], Snake.y_snake_body[0]);
    printf("o");

    if (Snake.x_snake_body[0] == Where_is_food.x_food && Snake.y_snake_body[0] == Where_is_food.y_food)
    {
        Snake.snakeLen++;
        SCORE++;
        foodmore = 1;
        if (Speed > 50)
        {
            Speed -= 30;
        }
    }
}

void Moving_reverse(void)
{

    if (start == 0)
    {
        where_to_go = 'a';
        start++;
    }

    if (_kbhit())
    {
        fflush(stdin);
        char keyboard = _getch();
        if (keyboard == 'w' && where_to_go != 's')
        {
            where_to_go = 'w';
        }
        if (keyboard == 's' && where_to_go != 'w')
        {
            where_to_go = 's';
        }
        if (keyboard == 'a' && where_to_go != 'd')
        {
            where_to_go = 'a';
        }
        if (keyboard == 'd' && where_to_go != 'a')
        {
            where_to_go = 'd';
        }
        if (keyboard == ' ')
        {
            pause = ' ';
        }
    }
    fflush(stdin);
    if (pause == ' ')
    {
        pause = 0;
        LinkingStart(Snake.x_snake_body[Snake.snakeLen - 1], Snake.y_snake_body[Snake.snakeLen - 1]);
        printf("*");
        while (1)
        {
            Sleep(1000);
            if (_kbhit())
            {
                fflush(stdin);
                pause = _getch();
                if (pause == ' ')
                {
                    pause;
                    break;
                }
                if (GetAsyncKeyState(VK_ESCAPE))
                {
                    system("cls");
                    exit(0);
                }
            }
        }
    }

    LinkingStart(Snake.x_snake_body[Snake.snakeLen - 1], Snake.y_snake_body[Snake.snakeLen - 1]);
    printf(" ");

    for (int i = Snake.snakeLen - 1; i > 0; i--)
    {
        Snake.x_snake_body[i] = Snake.x_snake_body[i - 1];
        Snake.y_snake_body[i] = Snake.y_snake_body[i - 1];
        LinkingStart(Snake.x_snake_body[i], Snake.y_snake_body[i]);
        printf("*");
    }

    if (where_to_go == 's')
    {
        Snake.y_snake_body[0]--;
    }
    if (where_to_go == 'w')
    {
        Snake.y_snake_body[0]++;
    }
    if (where_to_go == 'd')
    {
        Snake.x_snake_body[0]--;
    }
    if (where_to_go == 'a')
    {
        Snake.x_snake_body[0]++;
    }

    LinkingStart(Snake.x_snake_body[0], Snake.y_snake_body[0]);
    printf("o");

    if (Snake.x_snake_body[0] == Where_is_food.x_food && Snake.y_snake_body[0] == Where_is_food.y_food)
    {
        Snake.snakeLen++;
        SCORE++;
        foodmore = 1;
        if (Speed > 50)
        {
            Speed -= 30;
        }
    }
}

bool Gameover(void)
{
    for (int i = 1; i < Snake.snakeLen; i++)
    {
        if (Snake.x_snake_body[0] == Snake.x_snake_body[i] && Snake.y_snake_body[0] == Snake.y_snake_body[i])
        {
            return 1;
        }
    }
    if (Snake.x_snake_body[0] == x_start - 1 || Snake.x_snake_body[0] == Width + x_start + 1 || Snake.y_snake_body[0] == y_start - 2 || Snake.y_snake_body[0] == Height + y_start + 2)
    {
        return 1;
    }
    return 0;
}

void Random_food(void)
{
    bool in_snake = 0;
    srand(time(NULL));
    Where_is_food.x_food = rand() % (Width + 1) + x_start;
    Where_is_food.y_food = rand() % (Height - 1) + y_start + 0.5;

    for (int i = 0; i < Snake.snakeLen; i++)
    {
        if (Snake.x_snake_body[i] == Where_is_food.x_food && Snake.y_snake_body[i] == Where_is_food.y_food)
        {
            in_snake = 1;
        }
        if (in_snake == 0)
        {
            LinkingStart(Where_is_food.x_food, Where_is_food.y_food);
            printf("$");
            foodmore = 0;
        }
    }
}