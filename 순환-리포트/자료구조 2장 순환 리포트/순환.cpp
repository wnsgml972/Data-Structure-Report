#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int Max(int *arr, int len);
int Min(int *arr, int len);
int Second_Max(int *arr, int len);
int Second_Min(int *arr, int len);
int CompareBig(int a, int b);
int CompareSma(int a, int b);

int main()
{
	int arr[100];					//100���� ������ �Է¹��� �� �ִ� �迭 ����
	int len, i, x;
	double duration;
	clock_t start, finish;			//����ð��� ������ start�� finish

	while (1)
	{
		printf("�����Ϸ��� 1�� �����ÿ�. ");
		scanf_s("%d", &x);
		system("cls");					//ȭ�� Ŭ����

		if (x == 1)						//������� ���ÿ� ���� �ݺ� ����, 1�� �����ϸ� ���α׷� ����
			exit(0);

		printf("�迭�� �����Ϸ��� ������ ��: ");
		scanf_s("%d", &len);			//�迭�� ���� �Է�

		for (i = 0;i < len;i++)			//�迭�� ���̸�ŭ ����
		{
			printf("�Է�: ");
			scanf_s("%d", &arr[i]);
		}

		printf("�迭 ���: ");
		for (i = 0;i < len;i++)			//�迭 ���
			printf("%d ", arr[i]);
		printf("\n\n");

		len -= 1;						//���� �迭�� ���̰� 5�̸� �迭�� �� �� ���� arr[4]�̹Ƿ� 1���� �����ش�
		


		start = clock();							//����ð� ����
		printf("�ִ�: %d\n", Max(arr, len));		//�迭�� �ִ� ��� -> �迭�� �迭�� �ǳ� �ε����� ����
		finish = clock();							//����ð� ���� ��
		duration = (double)(finish - start) / CLOCKS_PER_SEC;					//(finish-start)���� CLOCKS_PER_SEC���� ������ �ʴ����� �ð��� ����
		printf("�ִ� �Լ��� ����ð���: %f �� �Դϴ�.\n\n", duration);		//����ð� ���, �ؿ��� ���� ������� ����ð� ����

		start = clock();
		printf("�ּڰ�: %d\n", Min(arr, len));		//�迭�� �ּڰ� ��� -> �迭�� �迭�� �ǳ� �ε����� ����
		finish = clock();
		duration = (double)(finish - start) / CLOCKS_PER_SEC;
		printf("�ּڰ� �Լ��� ����ð���: %f �� �Դϴ�.\n\n", duration);

		start = clock();
		printf("�ι�° �ִ�: %d\n", Second_Max(arr, len));		//�迭�� �ι�° �ִ� ���
		finish = clock();
		duration = (double)(finish - start) / CLOCKS_PER_SEC;
		printf("�ι�° �ִ� �Լ��� ����ð���: %f �� �Դϴ�.\n\n", duration);

		start = clock();
		printf("�ι�° �ּڰ�: %d\n", Second_Min(arr, len));		//�迭�� �ι�° �ּڰ� ���
		finish = clock();
		duration = (double)(finish - start) / CLOCKS_PER_SEC;
		printf("�ι�° �ּڰ� �Լ��� ����ð���: %f �� �Դϴ�.\n\n", duration);
	}

	return 0;
}

int CompareBig(int a, int b)			//a�� b�� �� ū�� ����
{
	return (a >= b) ? a : b;
}

int CompareSma(int a, int b)			//a�� b�� �� ������ ����
{
	return (a <= b) ? a : b;
}

int Max(int *arr, int len)
{
	if (len == 0)						//�迭�� ���̰� 1�ϰ�� arr[0] ����
		return arr[0];
	else													//����Լ� �̿� len=0 �̵ɶ����� ���� arr[0]���� arr[len]
		return CompareBig(Max(arr, len - 1), arr[len]);		//���� ���� ���� ū���� �����Ѵ�
}

int Min(int *arr, int len)
{
	if (len == 0)						//�迭�� ���̰� 1�ϰ�� arr[0] ����
		return arr[0];
	else													//����Լ� �̿� len=0 �̵ɶ����� ���� arr[0]���� arr[len]
		return CompareSma(Min(arr, len - 1), arr[len]);		//���� ���� ���� �������� �����Ѵ�
}

int Second_Max(int *arr, int len)
{
	int max, min, i;

	if (len == 0)
		return arr[0];
	else
		max = CompareBig(Max(arr, len - 1), arr[len]);		//�迭�� �ִ��� max�� �޴´�.

	if (len == 0)
		return arr[0];
	else
		min = CompareSma(Min(arr, len - 1), arr[len]);		//�迭�� �ּڰ��� min�� �޴´�.

	for (i = 0;i <= len;i++)
		if (max == arr[i])									//�迭�� �ִ��� ã�´�.
			arr[i] = min;									//�迭�� �ִ񰪿� �ּڰ� ����!

	if (len == 0)
		return arr[0];
	else													//�� ���� �ִ��� ã����� �ι�° �ִ��� ����!
		return CompareBig(Max(arr, len - 1), arr[len]);
}

int Second_Min(int *arr, int len)
{
	int max, min, i;

	if (len == 0)
		return arr[0];
	else
		max = CompareBig(Max(arr, len - 1), arr[len]);		//���������� �迭�� �ִ��� max�� �޴´�.

	if (len == 0)
		return arr[0];
	else
		min = CompareSma(Min(arr, len - 1), arr[len]);		//���������� �迭�� �ּڰ��� min�� �޴´�.

	for (i = 0;i <= len;i++)
		if (min == arr[i])									//�迭�� �ּڰ��� ã�´�.
			arr[i] = max;									//�迭�� �ּڰ��� �ִ� ����!

	if (len == 0)
		return arr[0];
	else													//�� ���� �ּڰ��� ã����� �ι�° �ּڰ��� ����!
		return CompareSma(Min(arr, len - 1), arr[len]);
}