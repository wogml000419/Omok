#include <stdio.h>
#include <Windows.h>
#include <conio.h>
#define size 20

#define LEFT 75
#define RIGHT 77
#define UP 72
#define DOWN 80
#define ENTER 13

void gotoxy(int x, int y)
{
	/*
	커서의 좌표를 옮기는 함수

	옮길 x좌포와 y좌표를 인자로 받음
	*/
	COORD pos = { x, y };				//x와 y좌표를 구조체에 할당
	HANDLE hnd = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hnd, pos);	//커서 좌표를 옮김
}

void TurnChange(char *ptr)
{
	/*
	왼쪽 위에 표시되는 턴을 바꾸는 함수

	오목판 왼쪽 위의 좌표를 인자로 받음
	*/
	static HANDLE hnd;
	hnd = GetStdHandle(STD_OUTPUT_HANDLE);

	*ptr = (*ptr == 'O') ? 'X' : 'O';

	gotoxy(2, 0);							//턴이 표시되는 좌표보다 한 칸 뒤로 이동
	putchar('\b');							//한 칸을 지운 뒤
	if (*ptr == 'O')						//'O'이면
		SetConsoleTextAttribute(hnd, 0x71);	//배경과 글자색 바꿈(연한 회색, 짙은 파랑)
	else									//'X'이면
		SetConsoleTextAttribute(hnd, 0x74);	//배경과 글자색 바꿈(연한 회색, 짙은 빨강)
	putchar(*ptr);							//출력

	SetConsoleTextAttribute(hnd, 0x0F);		//배경과 글자색 복구(검정색, 흰색)
}
void ShowPlate(char(*plate)[20])
{
	/*
	오목판을 보여주는 함수

	오목판 배열을 인자로 받음
	*/
	int x, y;
	HANDLE hnd = GetStdHandle(STD_OUTPUT_HANDLE);

	system("cls");						//화면 클리어

	if (plate[0][0] == 'O')				//'O'의 턴이라면
		SetConsoleTextAttribute(hnd, 0x71); //배경과 글자색 바꿈(옅은 회색, 짙은 파랑)
	else								//'X'의 턴이라면
		SetConsoleTextAttribute(hnd, 0x74); //배경과 글자색 바꿈(옅은 회색, 짙은 빨강)
	printf("%2c ", plate[0][0]);		//턴 출력

	SetConsoleTextAttribute(hnd, 0x8F);	//배경과 글자색 바꿈(짙은 회색, 검정)
	for (x = 1; x < size; x++)
		printf("%2d ", x);				//1부터 size(20) 전까지 숫자로 출력
	putchar('\n');

	for (y = 1; y < size; y++)			
	{
		SetConsoleTextAttribute(hnd, 0x8F);//배경과 글자색 바꿈(짙은 회색, 검정)
		printf("%2d ", plate[y][0]);    //제일 앞에는 숫자로 출력
		for (x = 1; x < size; x++)		
		{
			SetConsoleTextAttribute(hnd, 0x0F);//배경과 글자색 바꿈(검정, 흰색)
			printf("%2c ", plate[y][x]);//바둑판 출력
		}
		putchar('\n');
	}
}
int Win(char c)
{
	/*
	이겼을 때 출력하는 함수

	이긴 플레이어(O 또는 X)를 인자로 받음
	*/
	printf("=======%c 승!======= \n",c);
	return 1;
}
int WinOrNot(char plate[][20], int y, int x)
{
	/*
	끝났는지 아닌지 판단하는 함수

	오목판과 y, x좌표를 인자로 받음
	끝났을 경우 1, 아니면 0을 반환
	*/
	int i, j;
	int trig = 0;

	for (i = x - 4; i <= x + 4; i++)  //가로 검사 (뒤에서 4칸~앞으로 4칸)
	{
		if (plate[y][x] == plate[y][i]) //처음 시작과 현재 위치가 같다면
			trig++;						//트리거++
		else							//다르다면
			trig = 0;					//트리거를 0으로 초기화

		if (trig >= 5)					//검사했을 때 트리거가 5보다 크다면
			return 1;
	}
	trig = 0;							//트리거 0으로 초기화

	for (j = y - 4; j <= y + 4; j++) //세로 검사 (뒤에서 4칸~앞으로 4칸)
	{
		if (plate[y][x] == plate[j][x])	//처음 시작과 현재 위치가 같다면
			trig++;						//트리거++
		else							//다르다면
			trig = 0;					//트리거를 0으로 초기화
		
		if (trig >= 5)					//검사했을 때 트리거가 5보다 크다면
			return 1;
	}
	trig = 0;							//트리거 0으로 초기화

	j = y - 4;							//대각선으로 가기 때문에, j를 미리 초기화
	for (i = x - 4; i <= x + 4; )  //오른쪽 아래 대각선
	{
		
		if (plate[y][x] == plate[j][i])	//처음 시작과 현재 위치가 같다면
			trig++;						//트리거++
		else							//다르다면
			trig = 0;					//트리거 0으로 초기화

		if ((i == 0) && (j == 0))		//좌표의 값이 턴을 표시하는 좌표(오른쪽 위)일 경우
			trig = 0;					//트리거 초기화

		if (trig >= 5)					//검사했을 때 트리거가 5보다 크다면
			return 1;
		j++;	
		i++;
	}
	trig = 0;							//트리거 0으로 초기화

	j = y - 4;							//대각선으로 가기 때문에, j를 미리 초기화
	for (i = x + 4; i >= x - 4; i--) //왼쪽 아래 대각선
	{
		if (plate[y][x] == plate[j][i])	//처음 시작과 현재 위치가 같다면
			trig++;						//트리거++
		else							//다르다면
			trig = 0;					//트리거 0으로 초기화

		if (trig >= 5)					//검사했을 때 트리거가 5보다 크다면
			return 1;
		j++;
	}
	return 0;
}
int move(char plate[][20])
{
	/*
	이동과 돌 놓기를 구현한 함수

	오목판 배열을 인자로 받음
	게임이 끝났으면 -1, 잘못된 좌표를 선택하면 1, 정상적이면 0 반환
	*/

	char clt;
	static int x = 10 * 3;							//한 칸의 가로가 3이기 때문에, 3을 곱함
	static int y = 10;
	static HANDLE hnd;
	hnd = GetStdHandle(STD_OUTPUT_HANDLE);
	
while (1)
{
	gotoxy(0, 22);							//(0, 22)지점으로 이동해서
	printf("좌표 : %-2d %-2d", x / 3, y);	//출력

	gotoxy(x+1, y);							//현재 좌표로 이동
		
	clt = _getch();					//키보드로 입력을 받음
	if (clt == -32 || clt == 0)		//입력받은 키보드가 특수 키코드이면
		clt = _getch();				//한번 더 읽어야 제대로 된 값 받음
		
	switch (clt)
	{
	case LEFT:						//왼쪽키이면
		x -= 3;						//왼쪽으로 세 칸(한 블럭)이동
		break;
	case RIGHT:						//오른쪽 키이면
		x += 3;						//오른쪽으로 세 칸(한 블럭)이동
		break;
	case UP:						//위쪽 키이면
		y -= 1;						//위로 한 칸 이동
		break;
	case DOWN:						//아래쪽 키이면
		y += 1;						//아래쪽으로 한 칸 이동
		break;
	case ENTER:						//엔터키이면
		if (plate[y][x / 3] != '.')			//좌표가 비어있지 않으면
			return 1;						//1을 반환해 오류 메세지 출력 트리거 활성화
		else								//비어있으면
		{
			plate[y][x / 3] = plate[0][0];  //돌을 놓음
			gotoxy(x + 2, y);				//돌을 놓은 곳 한칸 앞으로 이동
			putchar('\b');					//그 칸을 지움
			if (plate[0][0] == 'O')			//'O'의 턴이었으면
				SetConsoleTextAttribute(hnd, 0x09);//배경과 글자색 변경(검정, 파랑)
			else							//'X'의 턴이었으면
				SetConsoleTextAttribute(hnd, 0x0C);//배경과 글자색 변경(검정, 빨강)
			putchar(plate[0][0]);			//돌 출력

			SetConsoleTextAttribute(hnd, 0x0F);//배경과 글자색 복구(검정, 하양)
		}

		if (WinOrNot(plate, y, x / 3))		//만약 게임이 끝났으면
		{
			gotoxy(0, 20);
			Win(plate[0][0]);				//Win() 실행
			return -1;						//-1 반환
		}
		else								//끝나지 않았으면
		{
			return 0;						//0 반환
		}
	}

		
	if (x < 1*3)
		x = 19 * 3;
	else if (x > 19 * 3)
		x = 1 * 3;
	if (y < 1)
		y = 19;
	else if (y > 19)
		y = 1;
}
}
int main(void)
{
	char plate[20][20];					//오목판 배열
	int x, y;
	int trig = 0;

	for(x=1; x<size; x++)				//1부터 19까지 
		plate[0][x] = x;				//제일 윗줄에 1~19 순서대로 대입
	for(y=1; y<size; y++)				//1부터 19까지
		plate[y][0] = y;				//제일 왼쪽에 1~19 순서대로 대입
	for(x=1; x<size; x++)
		for(y=1; y<size; y++)
			plate[y][x] = '.';			//나머지는 다 .으로 채움

	plate[0][0] = 'O';					//턴은 O 먼저 시작
	ShowPlate(plate);					//오목판을 보여줌
	gotoxy(10 * 3 + 1, 10);				//(10, 10) 지점으로 커서 이동
	while(1)
	{
		trig = move(plate);				//트리거에 move()가 반환한 값 저장

		switch (trig)
		{
		case 1:							//오류 메세지 출력 트리거가 활성화돼있으면
			gotoxy(0, 21);
			printf("잘못된 좌표 입력, 턴 넘어감 \n");//오류 메세지 출력
			trig = 0;					//트리거 비활성화
			break;
		case -1:						//-1이 반환되었으면
			return 0;					//종료
		}
		TurnChange(&plate[0][0]);		//턴 바꿈
	}
}