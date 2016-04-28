#include<stdio.h>
#define size 20

void TurnChange(char *ptr)
{
	/*
	왼쪽 위에 표시되는 턴을 바꾸는 함수
	*/
	*ptr = (*ptr == 'O') ? 'X' : 'O';
}
void ShowPlate(char(*plate)[20])
{
	/*
	오목판을 보여주는 함수
	*/
	int x, y;
	printf("%-3c", plate[0][0]);		//턴 출력
	for (x = 1; x < size; x++)
		printf("%-3d", x);				//1부터 size(20) 전까지 숫자로 출력
	putchar('\n');

	for (y = 1; y < size; y++)			//1부터 size(20) 전까지 
	{
		printf("%-3d", plate[y][0]);    //제일 앞에를 숫자로 출력
		for (x = 1; x < size; x++)		//1부터 size(20) 전까지
		{
			printf("%-3c", plate[y][x]);//바둑판 출력
		}
		putchar('\n');
	}
}
int Win(char c)
{
	/*
	이겼을 때 출력하는 함수
	*/
	printf("=======%c 승!======= \n",c);
	return 1;
}
int WinOrNot(char plate[][20], int y, int x)
{
	/*
	이겼는지 졌는지 판단하는 함수
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
			return Win(plate[0][0]);	//Win() 실행
	}
	trig = 0;							//트리거 0으로 초기화

	for (j = y - 4; j <= y + 4; j++) //세로 검사 (뒤에서 4칸~앞으로 4칸)
	{
		if (plate[y][x] == plate[j][x])	//처음 시작과 현재 위치가 같다면
			trig++;						//트리거++
		else							//다르다면
			trig = 0;					//트리거를 0으로 초기화
		
		if (trig >= 5)					//검사했을 때 트리거가 5보다 크다면
			return Win(plate[0][0]);	//Win() 실행
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
			return Win(plate[0][0]);	//Win() 실행
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
			return Win(plate[0][0]);	//Win() 실행
		j++;
	}
	return 0;
}
int main(void)
{
	char plate[20][20];					//오목판 배열
	int x, y;
	
	for(x=1; x<size; x++)				//1부터 19까지 
		plate[0][x] = x;				//제일 윗줄에 1~19 순서대로 대입
	for(y=1; y<size; y++)				//1부터 19까지
		plate[y][0] = y;				//제일 왼쪽에 1~19 순서대로 대입
	for(x=1; x<size; x++)
		for(y=1; y<size; y++)
			plate[y][x] = '.';			//나머지는 다 .으로 채움

	plate[0][0] = 'O';					//턴은 O 먼저 시작

	while(1)
	{
		ShowPlate(plate);				//오목판을 보여줌

		printf("좌표? ");
		scanf("%d %d", &x, &y);			//좌표 입력

		if(plate[y][x] != '.')			//좌표가 비어있지 않으면
			printf("잘못된 좌표 입력, 턴 넘어감 \n");//넘어감
		else							//비어있으면
			plate[y][x] = plate[0][0];  //돌을 놓음

		if( WinOrNot(plate, y, x) )		//만약 게임이 끝났으면
		{
			ShowPlate(plate);			//바둑판을 보여주고
			return 0;					//끝냄
		}
		TurnChange(&plate[0][0]);		//턴 바꿈
	}
}