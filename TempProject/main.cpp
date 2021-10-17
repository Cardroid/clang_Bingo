#pragma warning(disable: 4996)

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define GAME_SET_SCORE 3

void Init();
void printBoard();
void deleteNumber(int num);
int checkBingo();
int userInput();

// ┌┬┐
// ├┼┤
// └┴┘
// ─│

int BOARD[5][5] = { 0, };

//int BOARD[5][5] = {
//	 1, 2, 3, 4, 5,
//	 6, 7, 8, 9,10,
//	11,12,13,14,15,
//	16,17,18,19,20,
//	21,22,23,24,25
//};

int main()
{
	srand(time(NULL));

	int bingoLine = 0;

	Init();
	printBoard();

	do
	{
		deleteNumber(userInput());

		printBoard();

		bingoLine = checkBingo();

		if (bingoLine > 0)
			printf("%d 줄 Bingo!!\n", bingoLine);

		printf("\n");
	}
	while (bingoLine < GAME_SET_SCORE);
}

void Init()
{
	int used[25] = { 0, };
	int	num, flug;

	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			flug = 0;
			num = rand() % 25 + 1;

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

void printBoard()
{
	printf("┌───┬───┬───┬───┬───┐\n");

	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			if (BOARD[i][j] < 10)
			{
				if (BOARD[i][j] == 0)
					printf("│ ■");
				else
					printf("│  %d", BOARD[i][j]);
			}
			else
				printf("│ %d", BOARD[i][j]);

			if (j == 4)
				printf("│");
		}

		if (i != 4)
			printf("\n├───┼───┼───┼───┼───┤\n");
	}

	printf("\n└───┴───┴───┴───┴───┘\n");
}

void deleteNumber(int num)
{
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
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
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
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
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
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
	for (int i = 0; i < 5; i++)
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
	for (int i = 0; i < 5; i++)
	{
		for (int j = 5 - 1; j >= 0; j--)
		{
			if (i + j == 4 && BOARD[i][j] != 0)
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
	int num;
	printf("지울 번호를 입력하세요: ");
	scanf("%d", &num);
	return num;
}