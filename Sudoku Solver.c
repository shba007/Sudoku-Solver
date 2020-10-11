#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <windows.h>
#define METHOD 1

typedef struct Cell
{
	short value;
	short type; //const = 0, var =1
} cell;

int getkey();
int bound(short, short, short);
void display(cell *);
void gotoxy(short, short);

#if METHOD == 1
int check(cell *);
#elif METHOD == 2
short solve(cell *, short);
#endif

int main()
{
	short i, j, k, l, R, C, n, flag, sum;
	cell sudo[9][9];
	short digits[9], unit[3][9][9];

	//initialize to 0
	for (i = 0; i < 9; i++)
	{
		for (j = 0; j < 9; j++)
		{
			sudo[i][j].value = 0;
			sudo[i][j].type = 1;
			for (k = 0; k < 3; k++)
				unit[k][i][j] = 1;
		}
	}

	i = j = k = l = 0;

	//Input
	while (1)
	{
		display(&sudo[0][0]);
		printf("\n\n\t\tRow = %d, Column = %d", i + 1, j + 1);
		gotoxy((28 + 6 * j), (5 + 2 * i));

		k = getkey();
		if (k == -35)
			break;
		else if (k > 0 && k < 10)
		{
			sudo[i][j].value = k;
			sudo[i][j].type = 0;
			l++;
		}
		else if (k == 0)
		{
			sudo[i][j].value = 0;
			sudo[i][j].type = 1;
		}
		else if (bound(k, i, j))
		{
			switch (k)
			{
			case 72:
				i--;
				break;
			case 75:
				j--;
				break;
			case 77:
				j++;
				break;
			case 80:
				i++;
				break;
			}
		}
	}
	const short N = l;

#if METHOD == 1
	//Conflict Elemenate Algorithm 2.0
	for (i = 0; i < 9; i++)
	{
		//Row iteration
		for (j = 0; j < 9; j++)
		{
			if (sudo[i][j].type)
				continue;
			unit[0][i][sudo[i][j].value - 1] = 0;
		}
		//Column iteration
		for (j = 0; j < 9; j++)
		{
			if (sudo[j][i].type)
				continue;
			unit[1][i][sudo[j][i].value - 1] = 0;
		}
		//Box iteration
		for (j = k = 0; j < 3; j += (k + 1) / 3, k = (k + 1) % 3)
		{
			if (sudo[3 * ((short)i / 3) + j][3 * (i % 3) + k].type)
				continue;
			unit[2][i][sudo[3 * ((short)i / 3) + j][3 * (i % 3) + k].value - 1] = 0;
		}
	}

	while (1)
	{
		for (i = 0; i < 9; i++)
		{
			for (j = 0; j < 9; j++)
			{
				//Row wise iteration
				if (unit[0][i][j])
				{
					for (k = sum = 0; k < 9; k++)
					{
						if (!sudo[i][k].type)
							continue;
						if (unit[1][k][j] * unit[2][3 * ((short)i / 3) + ((short)k / 3)][j] == 1)
						{
							R = i;
							C = k;

							digits[j] = 1;
							flag = j;
							sum++;
						}
						else
							digits[j] = 0;
					}
					//Cheacking sum
					if (sum == 1)
					{
						sudo[R][C].value = flag + 1;
						sudo[R][C].type = 0;

						unit[0][R][flag] = 0;
						unit[1][C][flag] = 0;
						unit[2][3 * ((short)R / 3) + ((short)C / 3)][flag] = 0;
					}
				}
				//Display
				display(&sudo[0][0]);
				gotoxy(10, 25);
				printf("Complete %.2f %%", ((float)(n - N) / (81 - N)) * 100);
				n = check(&sudo[0][0]);
				//Check
				if (n == 81)
					goto result;
				//Column wise iteration
				if (unit[1][i][j])
				{
					for (k = sum = 0; k < 9; k++)
					{
						if (!sudo[k][i].type)
							continue;
						if (unit[0][k][j] * unit[2][3 * ((short)k / 3) + ((short)i / 3)][j] == 1)
						{
							R = k;
							C = i;

							digits[j] = 1;
							flag = j;
							sum++;
						}
						else
							digits[j] = 0;
					}
					//Cheacking sum
					if (sum == 1)
					{
						sudo[R][C].value = flag + 1;
						sudo[R][C].type = 0;

						unit[0][R][flag] = 0;
						unit[1][C][flag] = 0;
						unit[2][3 * ((short)R / 3) + ((short)C / 3)][flag] = 0;
					}
				}
				//Display
				display(&sudo[0][0]);
				gotoxy(10, 25);
				printf("Complete %.2f %%", ((float)(n - N) / (81 - N)) * 100);
				n = check(&sudo[0][0]);
				//Check
				if (n == 81)
					goto result;
				//Box wise iteration
				if (unit[2][i][j])
				{
					for (k = sum = 0; k < 3; k++)
					{
						for (l = 0; l < 3; l++)
						{
							if (!sudo[3 * (i / 3) + k][3 * (i % 3) + l].type)
								continue;
							if (unit[0][3 * (i / 3) + k][j] * unit[1][3 * (i % 3) + l][j] == 1)
							{
								R = 3 * (i / 3) + k;
								C = 3 * (i % 3) + l;

								digits[j] = 1;
								flag = j;
								sum++;
							}
							else
								digits[j] = 0;
						}
					}
					//Cheacking sum
					if (sum == 1)
					{
						sudo[R][C].value = flag + 1;
						sudo[R][C].type = 0;

						unit[0][R][flag] = 0;
						unit[1][C][flag] = 0;
						unit[2][i][flag] = 0;
					}
				}
				//Display
				display(&sudo[0][0]);
				gotoxy(10, 25);
				printf("Complete %.2f %%", ((float)(n - N) / (81 - N)) * 100);
				n = check(&sudo[0][0]);
				//Check
				if (n == 81)
					goto result;
			}
		}
	}

#elif METHOD == 2
	solve(&sudo[0][0], 0);
#endif
result:
	//Result
	display(&sudo[0][0]);
	return 0;
}
#if METHOD == 1
int check(cell *sudo)
{
	int n = 0, i, j; //n = number of non-empty cell
	for (i = 0; i < 9; i++)
	{
		for (j = 0; j < 9; j++)
			((sudo + j + 9 * i)->type == 1) ? (n = n) : (n++);
	}
	return n;
}
#elif METHOD == 2
//Recursive Conflict Algorithm 1.0
short solve(cell *sudo, short i)
{
	short j, value = 1;

	while (i < 81)
	{
		if (!(sudo + i)->type)
		{
			i++;
			continue;
		}
		//Checking
		for (j = 0; j < 9; j++)
		{
			if (value > 9)
				break;

			//Row Conflict Check	//Column Conflict Check		//Box Conflict Check
			if (((sudo + 9 * ((short)i / 9) + j)->value == value) ||
				((sudo + 9 * j + (short)i % 9)->value == value) ||
				((sudo + 27 * (i / 27) + 3 * ((i % 9) / 3) + 9 * (j / 3) + j % 3)->value == value))
			{
				value++;
				j = -1;
			}
		}

		//Evaluate
		if (value > 9)
		{
			(sudo + i)->value = 0;
			display(sudo);

			return 0;
		}
		else
		{
			(sudo + i)->value = value;
			display(sudo);

			if (!solve(sudo, i + 1))
				value++;
			else
				break;
		}
	}

	return 1;
}
#endif
int getkey()
{
	int as, sc;
	as = getch();
	sc = 0;
	if (as == 0)
	{
		sc = getch();
		return sc;
	}
	else
		return as - 48;
}

int bound(short key, short R, short C)
{
	if (key == 72 && R < 1)
		return 0;
	else if (key == 75 && C < 1)
		return 0;
	else if (key == 77 && C > 7)
		return 0;
	else if (key == 80 && R > 7)
		return 0;
	else
		return 1;
}
void display(cell *sudo)
{
	int i, j;
	system("cls");
	for (i = 0; i < 9; i++)
	{
		for (j = 0; j < 9; j++)
		{
			gotoxy((28 + 6 * j), (5 + 2 * i));
			(!(sudo + j + 9 * i)->value) ? (putchar(95)) : (printf("%d", (sudo + j + 9 * i)->value));
		}
	}
}
void gotoxy(short col, short row)
{
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD position = {col, row};
	SetConsoleCursorPosition(h, position);
}