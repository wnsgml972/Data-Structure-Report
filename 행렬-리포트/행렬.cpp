#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

typedef struct
{
	int row; //���� ����
	int col; //���� ����
	int num; //���� ����
}SparseMatrix;

void matrix();	//��� �Լ�
void ShowMatrix(int **matrix, int rows, int cols);	//����� �����ִ� �Լ�
void CleanBuffer();	//���ۿ� �����ִ� ���� �� ����� �Լ�

int main()
{
	char res;			//����!
	int done = 1;		//���ѷ����� �̿��ϱ� ���� ����
	int sel = 1;		//���ѷ����� �̿��ϱ� ���� ����

	while (done)
	{
		while (sel)
		{
			printf("������ 1������ �����Ͻÿ� :\n\n");
			printf("  1. ��� ���α׷�\n\n");
			printf("  2. ���α׷� ����\n\n");
			printf("1���� 2�� ������� �����Ͻðڽ��ϱ�? <1, 2>: ");
			res = getchar();	//res�� ����
			printf("\n");

			if (res >= '1' && res <= '2')	//res�� ������ 1�̳� 2�� ����������!
			{
				switch (res)
				{
				case '1':
					matrix();				//res�� ������ 1�̸� ����Լ� ����
					sel = 0;				//���ѷ��� ���°��� ���߱� ���� sel = 0
					break;
				case '2':
					printf("���α׷��� �����մϴ�.\n");
					return 0;				//2�� �Է½� ���α׷� ����
				}
			}
			CleanBuffer();					//�����ִ� ���۸� �� ����
		}

		printf("���α׷��� ��� �ݺ��ؼ� �̿��Ͻðڽ��ϱ�? <yes�� Y, no�� N �Է�>: ");
		res = getchar();		//���� res�� �Է�
		printf("\n");
		res = toupper(res);		//toupper�Լ��� ����� �� �ҹ����� ������ ���ش�.

		switch (res)
		{
		case 'Y':
			sel = 1;			//res�� 'Y'�̸� "sel = 1" �� �ٽ� ���� ���Ϲ��� �����Ѵ�.
			break;
		case 'N':
			done = 0;
			printf("���α׷��� �����մϴ�.\n");	//res�� 'N'�̸� ���� "done = 0" �� ���ѷ����� ���������� ���α׷� ����
			break;
		}
		CleanBuffer();			//�����ִ� ���۸� �� ����
	}

	return 0;
}

void matrix()
{
	int **matrix;			//�����Ҵ��� ���� ��� ���� ������
	int rows, cols;			//�� ���� ����
	int i, j;				//������ �迭�� �ε���
	int cnt = 0;			//0�̾ƴ� ��Ҹ� �������� count����
	SparseMatrix *s_matrix; // ����ü ������ ����

	printf("(��)�� �Է��Ͻÿ�: ");
	scanf_s("%d", &rows);
	printf("(��)�� �Է��Ͻÿ�: ");
	scanf_s("%d", &cols);
	printf("\n");

	//2���� �迭�� �����Ҵ��� ����
	matrix = (int**)malloc(sizeof(int*)*rows);
	for (i = 0;i < rows;i++)
		matrix[i] = (int*)malloc(sizeof(int)*cols);

	//������ �迭�� ��� �Է�
	for (i = 0;i < rows;i++)
		for (j = 0; j < cols;j++)
		{
			printf("%d�� %d���� ��� �Է�: ", i + 1, j + 1);
			scanf_s("%d", &matrix[i][j]);
		}

	ShowMatrix(matrix, rows, cols);		//����� ������

	//0�̾ƴ� ��Ҹ� ��
	for (i = 0;i<rows;i++)
		for (j = 0;j<cols;j++)
			if (matrix[i][j] != 0)
				cnt++;

	s_matrix = (SparseMatrix*)malloc(sizeof(int)*cnt);		//2��° ����� �����Ҵ�

	//0�̾ƴ� ��Ҹ� ����ü�� ������
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

	printf("��� ��ü�� �����ϴ� ����� �޸� ��뷮: %d\n", sizeof(int)*rows*cols);				//ù��° ����� �޸𸮸� ������
	printf("0�� �ƴ� ��Ҹ��� �����ϴ� ����� �޸� ��뷮: %d\n\n", sizeof(SparseMatrix)*cnt);	//�ι�° ����� �޸𸮸� ������

	//6������ �޸𸮻��� �ּҸ� ����� ��켱���� ���켱���� Ȯ����
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

void ShowMatrix(int **matrix, int rows, int cols)		//����� �����ִ� �Լ�
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
	while (getchar() != '\n');		//�Է� ���ۿ� '\n'�� ���������� �о�� �� �Է¹��۸� ���
}