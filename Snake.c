#pragma warning(disable:4996)

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <conio.h>
#include <windows.h>
#include <stdbool.h>


void Draw( const int* snakex, const int* snakey, int headx, int heady, int fruitx, int fruity, int tail)
{
	system("cls");
	for (int i = 0; i < 20; i++)
	{
		for (int j = 0; j < 40; j++)
		{
			if (i == 0 || i == 19 || j == 0 || j == 39)
				printf("*");

			else if (i == heady && j == headx)
				printf("Q");
			else if (i == fruity && j == fruitx)
				printf("@");
			else
			{
				int pr = 0;
				for (int k = 1; k <= tail; k++)
				{
					if (j == snakex[k] && i == snakey[k])
					{
						printf("0");
						pr = 1;
					}
				}
				if (pr == 0)
					printf(" ");
			}
		}
		printf("\n");
	}

	
}
void ShiftRight(int arr[], int tail)
{
	for (int i = tail; i>=0; i--)
		*(arr + i) = *(arr + i - 1);
}
void Move(int* snakex, int* snakey, int* headxptr, int* headyptr, int* fruitxptr, int* fruityptr, int* tailptr, char* dirptr, int* scoreptr)
{
	if (_kbhit())
	{
		*dirptr = _getch();
		if (*dirptr == 'w')
		{ 
			(*headyptr)--; 
			if (*headyptr < 1) *headyptr = 18;
			else if (*headyptr > 18) *headyptr = 1;
		}
		else if (*dirptr == 's')
		{
			(*headyptr)++;
			if (*headyptr < 1) *headyptr = 18;
			else if (*headyptr > 18) *headyptr = 1;
		}
		else if (*dirptr == 'd')
		{
			(*headxptr)++; 
			if (*headxptr < 1) *headxptr = 38;
			else if (*headxptr > 38) *headxptr = 1;
		}
		else if (*dirptr == 'a')
		{
			(*headxptr)--;
			if (*headxptr < 1) *headxptr = 38;
			else if (*headxptr > 38) *headxptr = 1;
		}

		if (*headxptr == *fruitxptr && *headyptr == *fruityptr)
		{
			bool fruit_tail = true;
			(*tailptr)++;
			(*scoreptr) += 10;
			while (fruit_tail)
			{
				fruit_tail = false;
				*fruitxptr = rand() % 38 + 1;
				*fruityptr = rand() % 18 + 1;
				for(int i=0; i<=*tailptr; i++)
				if (*fruitxptr == snakex[i] && *fruityptr == snakey[i])
					fruit_tail = true;
			}
		}
		ShiftRight(snakex, *tailptr);
		ShiftRight(snakey, *tailptr);
		snakex[0] = *headxptr;
		snakey[0] = *headyptr;
	}
}



int main()
{
	char dir;
	bool lose = false;
	int snakex[100], snakey[100];
	int fruitx, fruity, headx, heady, tail = 0;
	int score = 0;
	srand(time(NULL));
	fruitx = rand() % 38 + 1;
	fruity = rand() % 18 + 1;
	headx = 20;
	heady = 10;
	snakex[0] = headx;
	snakey[0] = heady;
	while (!lose)
	{

		Draw(snakex, snakey, headx, heady, fruitx, fruity, tail);
		Move(snakex, snakey, &headx, &heady, &fruitx, &fruity, &tail, &dir, &score);
		for (int i = 1; i <= tail; i++)
		{
			if (headx == snakex[i] && heady == snakey[i])
				lose = true;
		}
		for (int i = 0; i <= tail ; i++)
			printf("%d ", snakex[i]);
		Sleep(5);
	}
	if (lose)
	{
		system("cls");
		printf("Game Over!!!!");
	}
	return 0;
}