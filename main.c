
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <time.h>

#define WIDTH 40
#define HEIGHT 20
#define MAX_SNAKE 100

int snakeX[MAX_SNAKE];
int snakeY[MAX_SNAKE];

int snakeLength;
int foodX;
int foodY;
int score;
int gameOver;

char direction;

void setup(void)
{
    snakeLength = 3;
    score = 0;
    gameOver = 0;
    direction = 'd';

    // Starting position
    snakeX[0] = WIDTH / 2;
    snakeY[0] = HEIGHT / 2;

    snakeX[1] = snakeX[0] - 1;
    snakeY[1] = snakeY[0];

    snakeX[2] = snakeX[0] - 2;
    snakeY[2] = snakeY[0];

    // Random food
    foodX = rand() % (WIDTH - 2) + 1;
    foodY = rand() % (HEIGHT - 2) + 1;
}

void draw(void)
{
    system("cls");

    printf("==========================================\n");
    printf("              TERMINAL SNAKE              \n");
    printf("==========================================\n");

    for (int y = 0; y < HEIGHT; y++)
    {
        for (int x = 0; x < WIDTH; x++)
        {
            int printed = 0;

            // Walls
            if (x == 0 || x == WIDTH - 1 ||
                y == 0 || y == HEIGHT - 1)
            {
                printf("#");
                printed = 1;
            }

            // Food
            if (!printed && x == foodX && y == foodY)
            {
                printf("*");
                printed = 1;
            }

            // Snake
            if (!printed)
            {
                for (int i = 0; i < snakeLength; i++)
                {
                    if (snakeX[i] == x && snakeY[i] == y)
                    {
                        if (i == 0)
                            printf("O");
                        else
                            printf("o");

                        printed = 1;
                        break;
                    }
                }
            }

            // Empty space
            if (!printed)
                printf(" ");
        }

        printf("\n");
    }

    printf("\nScore: %d\n", score);
    printf("Controls: W A S D or Arrow Keys\n");
}

void input(void)
{
    if (_kbhit())
    {
        int key = _getch();

        // WASD controls
        if ((key == 'w' || key == 'W') && direction != 's')
            direction = 'w';

        else if ((key == 's' || key == 'S') && direction != 'w')
            direction = 's';

        else if ((key == 'a' || key == 'A') && direction != 'd')
            direction = 'a';

        else if ((key == 'd' || key == 'D') && direction != 'a')
            direction = 'd';

        // Arrow keys
        else if (key == 224)
        {
            key = _getch();

            if (key == 72 && direction != 's')
                direction = 'w';

            else if (key == 80 && direction != 'w')
                direction = 's';

            else if (key == 75 && direction != 'd')
                direction = 'a';

            else if (key == 77 && direction != 'a')
                direction = 'd';
        }
    }
}

void update(void)
{
    // Move the body
    for (int i = snakeLength - 1; i > 0; i--)
    {
        snakeX[i] = snakeX[i - 1];
        snakeY[i] = snakeY[i - 1];
    }

    // Move the head
    if (direction == 'w')
        snakeY[0]--;

    else if (direction == 's')
        snakeY[0]++;

    else if (direction == 'a')
        snakeX[0]--;

    else if (direction == 'd')
        snakeX[0]++;
}

void checkCollision(void)
{
    // Wall collision
    if (snakeX[0] <= 0 ||
        snakeX[0] >= WIDTH - 1 ||
        snakeY[0] <= 0 ||
        snakeY[0] >= HEIGHT - 1)
    {
        gameOver = 1;
    }

    // Self collision
    for (int i = 1; i < snakeLength; i++)
    {
        if (snakeX[0] == snakeX[i] &&
            snakeY[0] == snakeY[i])
        {
            gameOver = 1;
        }
    }

    // Food collision
    if (snakeX[0] == foodX &&
        snakeY[0] == foodY)
    {
        if (snakeLength < MAX_SNAKE)
            snakeLength++;

        score++;

        // Generate new food
        foodX = rand() % (WIDTH - 2) + 1;
        foodY = rand() % (HEIGHT - 2) + 1;
    }
}

int main(void)
{
    srand((unsigned int)time(NULL));

    int playAgain = 1;

    while (playAgain)
    {
        setup();

        while (!gameOver)
        {
            draw();
            input();
            update();
            checkCollision();

            // Game gets faster as score increases
            int delay = 150 - (score * 5);

            if (delay < 50)
                delay = 50;

            Sleep(delay);
        }

        draw();

        printf("\n");
        printf("==========================================\n");
        printf("               GAME OVER!                 \n");
        printf("==========================================\n");
        printf("Final Score: %d\n", score);
        printf("\n");
        printf("Press R to play again or Q to quit.\n");

        char choice;

        do
        {
            choice = _getch();

        } while (choice != 'r' &&
                 choice != 'R' &&
                 choice != 'q' &&
                 choice != 'Q');

        if (choice == 'q' || choice == 'Q')
            playAgain = 0;
    }

    system("cls");

    printf("Thanks for playing Terminal Snake!\n");
    printf("Final score: %d\n", score);

    printf("\nPress Enter to exit...");
    getchar();
    getchar();


    return 0;
}

