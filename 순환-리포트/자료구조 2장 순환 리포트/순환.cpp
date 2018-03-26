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
	int arr[100];					//100개의 정수를 입력받을 수 있는 배열 선언
	int len, i, x;
	double duration;
	clock_t start, finish;			//실행시간을 측정할 start와 finish

	while (1)
	{
		printf("종료하려면 1을 누르시오. ");
		scanf_s("%d", &x);
		system("cls");					//화면 클리어

		if (x == 1)						//사용자의 선택에 따른 반복 수행, 1을 선택하면 프로그램 종료
			exit(0);

		printf("배열에 저장하려는 데이터 수: ");
		scanf_s("%d", &len);			//배열의 길이 입력

		for (i = 0;i < len;i++)			//배열의 길이만큼 저장
		{
			printf("입력: ");
			scanf_s("%d", &arr[i]);
		}

		printf("배열 출력: ");
		for (i = 0;i < len;i++)			//배열 출력
			printf("%d ", arr[i]);
		printf("\n\n");

		len -= 1;						//만약 배열의 길이가 5이면 배열의 맨 끝 값은 arr[4]이므로 1을빼 맞춰준다
		


		start = clock();							//실행시간 측정
		printf("최댓값: %d\n", Max(arr, len));		//배열의 최댓값 출력 -> 배열과 배열의 맨끝 인덱스를 전달
		finish = clock();							//실행시간 측정 끝
		duration = (double)(finish - start) / CLOCKS_PER_SEC;					//(finish-start)값을 CLOCKS_PER_SEC으로 나눠서 초단위의 시간값 대입
		printf("최댓값 함수의 실행시간은: %f 초 입니다.\n\n", duration);		//실행시간 출력, 밑에도 같은 방식으로 실행시간 측정

		start = clock();
		printf("최솟값: %d\n", Min(arr, len));		//배열의 최솟값 출력 -> 배열과 배열의 맨끝 인덱스를 전달
		finish = clock();
		duration = (double)(finish - start) / CLOCKS_PER_SEC;
		printf("최솟값 함수의 실행시간은: %f 초 입니다.\n\n", duration);

		start = clock();
		printf("두번째 최댓값: %d\n", Second_Max(arr, len));		//배열의 두번째 최댓값 출력
		finish = clock();
		duration = (double)(finish - start) / CLOCKS_PER_SEC;
		printf("두번째 최댓값 함수의 실행시간은: %f 초 입니다.\n\n", duration);

		start = clock();
		printf("두번째 최솟값: %d\n", Second_Min(arr, len));		//배열의 두번째 최솟값 출력
		finish = clock();
		duration = (double)(finish - start) / CLOCKS_PER_SEC;
		printf("두번째 최솟값 함수의 실행시간은: %f 초 입니다.\n\n", duration);
	}

	return 0;
}

int CompareBig(int a, int b)			//a와 b중 더 큰값 리턴
{
	return (a >= b) ? a : b;
}

int CompareSma(int a, int b)			//a와 b중 더 작은값 리턴
{
	return (a <= b) ? a : b;
}

int Max(int *arr, int len)
{
	if (len == 0)						//배열의 길이가 1일경우 arr[0] 리턴
		return arr[0];
	else													//재귀함수 이용 len=0 이될때까지 가서 arr[0]부터 arr[len]
		return CompareBig(Max(arr, len - 1), arr[len]);		//까지 비교해 제일 큰값을 리턴한다
}

int Min(int *arr, int len)
{
	if (len == 0)						//배열의 길이가 1일경우 arr[0] 리턴
		return arr[0];
	else													//재귀함수 이용 len=0 이될때까지 가서 arr[0]부터 arr[len]
		return CompareSma(Min(arr, len - 1), arr[len]);		//까지 비교해 제일 작은값을 리턴한다
}

int Second_Max(int *arr, int len)
{
	int max, min, i;

	if (len == 0)
		return arr[0];
	else
		max = CompareBig(Max(arr, len - 1), arr[len]);		//배열의 최댓값을 max에 받는다.

	if (len == 0)
		return arr[0];
	else
		min = CompareSma(Min(arr, len - 1), arr[len]);		//배열의 최솟값을 min에 받는다.

	for (i = 0;i <= len;i++)
		if (max == arr[i])									//배열의 최댓값을 찾는다.
			arr[i] = min;									//배열의 최댓값에 최솟값 대입!

	if (len == 0)
		return arr[0];
	else													//그 다음 최댓값을 찾을경우 두번째 최댓값을 리턴!
		return CompareBig(Max(arr, len - 1), arr[len]);
}

int Second_Min(int *arr, int len)
{
	int max, min, i;

	if (len == 0)
		return arr[0];
	else
		max = CompareBig(Max(arr, len - 1), arr[len]);		//마찬가지로 배열의 최댓값을 max에 받는다.

	if (len == 0)
		return arr[0];
	else
		min = CompareSma(Min(arr, len - 1), arr[len]);		//마찬가지로 배열의 최솟값을 min에 받는다.

	for (i = 0;i <= len;i++)
		if (min == arr[i])									//배열의 최솟값을 찾는다.
			arr[i] = max;									//배열의 최솟값에 최댓값 대입!

	if (len == 0)
		return arr[0];
	else													//그 다음 최솟값을 찾을경우 두번째 최솟값을 리턴!
		return CompareSma(Min(arr, len - 1), arr[len]);
}