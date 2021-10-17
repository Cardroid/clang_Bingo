#pragma warning(disable: 4996)

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <windows.h>

#define GAME_SET_SCORE 3
#define BOARD_SIZE 10
#define USE_RANDOM_BOARD 0

void Init(int useRandom);
void printBoard();
void deleteNumber(int num);
int checkBingo();
int userInput();
void consoleClear();

// ┌┬┐
// ├┼┤
// └┴┘
// ─│

int BOARD[BOARD_SIZE][BOARD_SIZE] = { 0, };

int main()
{
	srand(time(NULL));

	int bingoLine = 0;

	Init(USE_RANDOM_BOARD);
	printBoard();

	do
	{
		deleteNumber(userInput());

		consoleClear();

		printBoard();

		bingoLine = checkBingo();

		if (bingoLine > 0)
			printf("%d 줄 Bingo!!\n", bingoLine);
	} while (bingoLine < GAME_SET_SCORE);

	return 0;
}

void Init(int useRandom)
{
	if (useRandom == 1)
	{
		int used[BOARD_SIZE * BOARD_SIZE] = { 0, };
		int	num, flug;

		for (int i = 0; i < BOARD_SIZE; i++)
		{
			for (int j = 0; j < BOARD_SIZE; j++)
			{
				flug = 0;
				num = rand() % (BOARD_SIZE * BOARD_SIZE) + 1;

				if (used[num - 1] == 1)
				{
					j--;
					continue;
				}

				BOARD[i][j] = num;
				used[num - 1] = 1;
			}
		}
	}
	else
	{
		for (int i = 0; i < BOARD_SIZE; i++)
		{
			for (int j = 0; j < BOARD_SIZE; j++)
			{
				BOARD[i][j] = i * BOARD_SIZE + j + 1;
			}
		}
	}
}

void printBoard()
{
	printf("┌");
	for (int i = 0; i < BOARD_SIZE - 1; i++)
	{
		printf("───┬");
	}
	printf("───┐\n");

	for (int i = 0; i < BOARD_SIZE; i++)
	{
		for (int j = 0; j < BOARD_SIZE; j++)
		{
			if (BOARD[i][j] < 10)
			{
				if (BOARD[i][j] == 0)
					printf("│ ■");
				else
					printf("│  %d", BOARD[i][j]);
			}
			else if (BOARD[i][j] < 100)
				printf("│ %d", BOARD[i][j]);
			else
				printf("│%d", BOARD[i][j]);

			if (j == BOARD_SIZE - 1)
				printf("│");
		}

		if (i != BOARD_SIZE - 1)
		{
			printf("\n├");
			for (int i = 0; i < BOARD_SIZE - 1; i++)
			{
				printf("───┼");
			}
			printf("───┤\n");
		}
	}

	printf("\n└");
	for (int i = 0; i < BOARD_SIZE - 1; i++)
	{
		printf("───┴");
	}
	printf("───┘\n");
}

void deleteNumber(int num)
{
	for (int i = 0; i < BOARD_SIZE; i++)
	{
		for (int j = 0; j < BOARD_SIZE; j++)
		{
			if (BOARD[i][j] == num)
			{
				BOARD[i][j] = 0;
				return;
			}
		}
	}
}

int checkBingo()
{
	int bingo = 0;
	int flug = 0;

	// 가로줄 빙고 체크
	for (int i = 0; i < BOARD_SIZE; i++)
	{
		for (int j = 0; j < BOARD_SIZE; j++)
		{
			if (BOARD[i][j] != 0)
			{
				flug = 1;
				break;
			}
		}

		if (flug == 0)
			bingo++;

		flug = 0;
	}

	// 세로줄 빙고 체크
	for (int i = 0; i < BOARD_SIZE; i++)
	{
		for (int j = 0; j < BOARD_SIZE; j++)
		{
			if (BOARD[j][i] != 0)
			{
				flug = 1;
				break;
			}
		}

		if (flug == 0)
			bingo++;

		flug = 0;
	}

	// \ 대각선 빙고 체크
	for (int i = 0; i < BOARD_SIZE; i++)
	{
		if (BOARD[i][i] != 0)
		{
			flug = 1;
			break;
		}
	}

	if (flug == 0)
		bingo++;

	flug = 0;

	// / 대각선 빙고 체크
	for (int i = 0; i < BOARD_SIZE; i++)
	{
		for (int j = BOARD_SIZE - 1; j >= 0; j--)
		{
			if (i + j == BOARD_SIZE - 1 && BOARD[i][j] != 0)
			{
				flug = 1;
				break;
			}
		}
	}

	if (flug == 0)
		bingo++;

	return bingo;
}

int userInput()
{
	int num = 0;
	printf("지울 번호를 입력하세요: ");
	scanf("%d", &num);
	return num;
}

void consoleClear()
{
	system("cls");
}