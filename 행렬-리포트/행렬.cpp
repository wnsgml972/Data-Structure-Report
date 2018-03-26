#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

typedef struct
{
	int row; //행의 개수
	int col; //열의 개수
	int num; //항의 개수
}SparseMatrix;

void matrix();	//행렬 함수
void ShowMatrix(int **matrix, int rows, int cols);	//행렬을 보여주는 함수
void CleanBuffer();	//버퍼에 남아있는 것을 다 지우는 함수

int main()
{
	char res;			//선택!
	int done = 1;		//무한루프를 이용하기 위한 변수
	int sel = 1;		//무한루프를 이용하기 위한 변수

	while (done)
	{
		while (sel)
		{
			printf("다음중 1가지를 선택하시오 :\n\n");
			printf("  1. 행렬 프로그램\n\n");
			printf("  2. 프로그램 종료\n\n");
			printf("1번과 2번 어느것을 선택하시겠습니까? <1, 2>: ");
			res = getchar();	//res에 받음
			printf("\n");

			if (res >= '1' && res <= '2')	//res에 받은게 1이나 2면 이프문으로!
			{
				switch (res)
				{
				case '1':
					matrix();				//res에 받은게 1이면 행렬함수 실행
					sel = 0;				//무한루프 도는것을 멈추기 위한 sel = 0
					break;
				case '2':
					printf("프로그램을 종료합니다.\n");
					return 0;				//2를 입력시 프로그램 종료
				}
			}
			CleanBuffer();					//남아있는 버퍼를 다 지움
		}

		printf("프로그램을 계속 반복해서 이용하시겠습니까? <yes면 Y, no면 N 입력>: ");
		res = getchar();		//역시 res에 입력
		printf("\n");
		res = toupper(res);		//toupper함수를 사용해 대 소문자의 구별을 없앤다.

		switch (res)
		{
		case 'Y':
			sel = 1;			//res가 'Y'이면 "sel = 1" 즉 다시 위의 와일문을 돌게한다.
			break;
		case 'N':
			done = 0;
			printf("프로그램을 종료합니다.\n");	//res가 'N'이면 현재 "done = 0" 즉 무한루프를 빠져나가며 프로그램 종료
			break;
		}
		CleanBuffer();			//남아있는 버퍼를 다 지움
	}

	return 0;
}

void matrix()
{
	int **matrix;			//동적할당을 위한 행렬 더블 포인터
	int rows, cols;			//행 열의 개수
	int i, j;				//이차원 배열의 인덱스
	int cnt = 0;			//0이아닌 요소를 세기위한 count변수
	SparseMatrix *s_matrix; // 구조체 포인터 변수

	printf("(행)을 입력하시오: ");
	scanf_s("%d", &rows);
	printf("(열)을 입력하시오: ");
	scanf_s("%d", &cols);
	printf("\n");

	//2차원 배열을 동적할당을 받음
	matrix = (int**)malloc(sizeof(int*)*rows);
	for (i = 0;i < rows;i++)
		matrix[i] = (int*)malloc(sizeof(int)*cols);

	//이차원 배열의 요소 입력
	for (i = 0;i < rows;i++)
		for (j = 0; j < cols;j++)
		{
			printf("%d행 %d열의 요소 입력: ", i + 1, j + 1);
			scanf_s("%d", &matrix[i][j]);
		}

	ShowMatrix(matrix, rows, cols);		//행렬을 보여줌

	//0이아닌 요소를 셈
	for (i = 0;i<rows;i++)
		for (j = 0;j<cols;j++)
			if (matrix[i][j] != 0)
				cnt++;

	s_matrix = (SparseMatrix*)malloc(sizeof(int)*cnt);		//2번째 방식의 동적할당

	//0이아닌 요소를 구조체에 대입함
	for (i = 0;i < rows;i++)
		for (j = 0;j < cols;j++)
		{
			if (matrix[i][j] != 0)
			{
				s_matrix->row = i;
				s_matrix->col = j;
				s_matrix->num = matrix[i][j];
			}
		}

	printf("행렬 자체를 저장하는 방식의 메모리 사용량: %d\n", sizeof(int)*rows*cols);				//첫번째 방식의 메모리를 보여줌
	printf("0이 아닌 요소만을 저장하는 방식의 메모리 사용량: %d\n\n", sizeof(SparseMatrix)*cnt);	//두번째 방식의 메모리를 보여줌

	//6개까지 메모리상의 주소를 출력해 행우선인지 열우선인지 확인함
	cnt = 0;
	for (i = 0;i < rows;i++)
	{
		for (j = 0;j < cols;j++)
		{
			cnt++;
			printf("mat[%d][%d]: %d (%p)\n", i, j, cnt, &matrix[i][j]);
			if (cnt == 6)
			{
				i = rows;
				j = cols;
			}
		}
	}
	printf("\n");
}

void ShowMatrix(int **matrix, int rows, int cols)		//행렬을 보여주는 함수
{
	int i, j;

	printf("\n<Show Matrix>\n");
	for (i = 0;i < rows;i++)
	{
		for (j = 0;j < cols;j++)
		{
			printf("%4d", matrix[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}

void CleanBuffer()
{
	while (getchar() != '\n');		//입력 버퍼에 '\n'이 읽힐때까지 읽어라 즉 입력버퍼를 비움
}