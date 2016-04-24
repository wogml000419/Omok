#include<stdio.h>
#define size 20

void TurnChange(char *ptr)
{
	*ptr = (*ptr == 'O') ? 'X' : 'O';
}
void ShowPlate(char(*plate)[20])
{
	int x, y;
	printf("%-3c", plate[0][0]);
	for (x = 1; x < size; x++)
		printf("%-3d", x);
	putchar('\n');

	for (y = 1; y < size; y++)
	{
		printf("%-3d", plate[y][0]);
		for (x = 1; x < size; x++)
		{
			printf("%-3c", plate[y][x]);
		}
		putchar('\n');
	}
}
int Win(char c)
{
	TurnChange(&c);
	printf("=======%c 승!======= \n",c);
	return 1;
}
int WinOrNot(char plate[][20], int y, int x)
{
	int i, j;
	int trig = 0;
	TurnChange(&plate[0][0]);
	for (i = x - 4; i <= x + 4; i++)  //가로 검사
	{
		if (plate[y][x] == plate[y][i])
			trig++;
		else
			trig = 0;

		if (trig >= 5)
			return Win(plate[0][0]);
	}
	trig = 0;

	for (j = y - 4; j <= y + 4; j++) //세로 검사
	{
		if (plate[y][x] == plate[j][x])
			trig++;
		else
			trig = 0;
		
		if (trig >= 5)
			return Win(plate[0][0]);
	}
	trig = 0;

	j = y - 4;
	for (i = x - 4; i <= x + 4; )  //오른쪽 아래 대각선
	{
		if ((i == 0) && (j == 0))
			trig = 0;
		if (plate[y][x] == plate[j][i])
			trig++;
		else
			trig = 0;

		if (trig >= 5)
			return Win(plate[0][0]);
		j++;
		i++;
	}
	trig = 0;

	j = y - 4;
	for (i = x + 4; i >= x - 4; i--) //왼쪽 아래 대각선
	{
		if (plate[y][x] == plate[j][i])
			trig++;
		else
			trig = 0;

		if (trig >= 5)
			return Win(plate[0][0]);
		j++;
	}
	return 0;
}
int main(void)
{
	char plate[20][20];
	int x, y;
	
	for(x=1; x<size; x++)
		plate[0][x] = x;
	for(y=1; y<size; y++)
		plate[y][0] = y;
	for(x=1; x<size; x++)
		for(y=1; y<size; y++)
			plate[y][x] = '.';

	plate[0][0] = 'O';

	while(1)
	{
		ShowPlate(plate);

		printf("좌표? ");
		scanf("%d %d", &x, &y);

		if(plate[y][x] != '.')
			printf("잘못된 좌표 입력, 턴 넘어감 \n");
		else
			plate[y][x] = plate[0][0];

		if( WinOrNot(plate, y, x) )
		{
			ShowPlate(plate);
			return 0;
		}
	}
}