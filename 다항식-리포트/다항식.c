#define _CRT_SECURE_NO_WARNINGS //visual studio 2015 버젼으로 짠점 양해 부탁드립니다.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_POLY 30
#define COMPARE(a,b) ((a)<(b) ? '<' : (a)==(b) ? '=' : '>')		//b가 더 크면 <, 같으면 =, a가 더크면 >

typedef struct PolyNode
{
	int coef;	//계수
	int degree;	//지수
	struct PolyNode *link;
} PolyNode;

PolyNode* PolyAdd(PolyNode *a, PolyNode *b);	//두 방정식 더하기
PolyNode* PolySub(PolyNode *a, PolyNode *b);	//두 방정식 빼기
PolyNode* CreatPoly(char *str);					//하나의 방정식 생성
void Attach(int coe, int deg, PolyNode **p);	//노드 추가
void Display(PolyNode *head);					//다항식의 모양으로 출력
void ShowAdd(PolyNode *a, PolyNode *b);			//Add 시작 출력
void ShowSub(PolyNode *a, PolyNode *b);			//Sub 시작 출력
void ShowRet(PolyNode *a);						//결과값 출력

int main()
{
	PolyNode *A, *B, *ret;			//다항식 A, B와 합과 차를 받을 ret
	int sel, control;				//program선택과 반복분 조절을 위한 control
	char a[MAX_POLY], b[MAX_POLY];	//다항식 입력을 위한 문자열

	printf("┌────────────────────────┐\n");
	printf("│   과목명 : 자료구조   교수명 : 강희중 교수님   │\n");
	printf("├────────────────────────┤\n");
	printf("│     학번 : 1392056        이름 : 김준희        │\n");
	printf("└────────────────────────┘\n");
	printf("Press The Enter Key.........\n");
	getchar();	//enter 하면 시작!

	while (1)
	{
		control = 1;	//control 1로 초기화

		printf("┌──────────────────────────────────┐\n");
		printf("│                   Polynomial's Add and Sub Program                 │\n");
		printf("├──────────────────────────────────┤\n");
		printf("│      1.Poly Add      2.Poly Sub      3.Roll Back      4.Exit       │\n");
		printf("└──────────────────────────────────┘\n");

		printf("ex) 2x^3+3x\n");
		printf("Input First Polynomial >> ");
		scanf("%s", a);
		A = CreatPoly(a);

		printf("Input Second Polynomial >> ");
		scanf("%s", b);
		B = CreatPoly(b);

		printf("Select Program >> ");
		scanf("%d", &sel);

		while (control)
		{
			switch (sel)
			{
			case 1:
				ret = PolyAdd(A, B);
				ShowAdd(A, B);
				ShowRet(ret);
				printf("Select Program >> ");
				scanf("%d", &sel);
				break;
			case 2:
				ret = PolySub(A, B);
				ShowSub(A, B);
				ShowRet(ret);
				printf("Select Program >> ");
				scanf("%d", &sel);
				break;
			case 3:
				control = 0;	//control을 0으로 초기화해 반복문을 빠져나옴
				break;
			case 4:
				printf("Good Bay!!\n");
				return 0;		//프로그램 종료
			}
		}
	}

	free(A);
	free(B);
	free(ret);

	return 0;
}

PolyNode* PolyAdd(PolyNode *a, PolyNode *b)
{
	int sum;
	PolyNode *ret, *head;
	ret = head = (PolyNode *)malloc(sizeof(PolyNode));

	while (a && b)
	{
		switch (COMPARE(a->degree, b->degree))	//a와 b의 지수 비교
		{
		case '<':	//a < b
			Attach(b->coef, b->degree, &ret);
			b = b->link;
			break;
		case '=':	//a == b
			sum = a->coef + b->coef;
			if (sum)
				Attach(sum, a->degree, &ret);
			a = a->link;
			b = b->link;
			break;
		case '>':	//a > b
			Attach(a->coef, a->degree, &ret);
			a = a->link;
		}
	}

	//a와 b의 남은 노드를 다 처리함
	while (a != NULL)
	{
		Attach(a->coef, a->degree, &ret);
		a = a->link;
	}
	while (b != NULL)
	{
		Attach(b->coef, b->degree, &ret);
		b = b->link;
	}

	head = head->link;
	return head;
}

PolyNode* PolySub(PolyNode *a, PolyNode *b)
{
	int sub;
	PolyNode *ret, *head;
	ret = head = (PolyNode *)malloc(sizeof(PolyNode));

	while (a && b)
	{
		switch (COMPARE(a->degree, b->degree))
		{
		case '<':
			Attach(-b->coef, b->degree, &ret);		//a다항식 -b 다항식 이므로 b다항식은 계수에 -를 붙여서 노드에 추가한다
			b = b->link;
			break;
		case '=':
			sub = a->coef - b->coef;
			if (sub)
				Attach(sub, a->degree, &ret);
			a = a->link; 
			b = b->link;
			break;
		case '>':
			Attach(a->coef, a->degree, &ret);
			a = a->link;
		}
	}

	//a와 b의 남은 노드를 다 처리함
	while (a != NULL)
	{
		Attach(a->coef, a->degree, &ret);
		a = a->link;
	}
	while (b != NULL)
	{
		Attach(-b->coef, b->degree, &ret);	//b는 -되므로 계수에 -를 붙인다!
		b = b->link;
	}

	head = head->link;
	return head;
}

PolyNode* CreatPoly(char *str)
{
	PolyNode *p, *head;			// 사용할 포인터와 헤드 포인터
	int i, j, k;				// 반복문에 쓰임
	int c_idx = 0, d_idx = 0;	//계수 인덱스, 지수 인덱스
	int coe, deg;				// 계수, 지수

	head = p = (PolyNode *)malloc(sizeof(PolyNode));

	for (i = 0;i < MAX_POLY;i++)
	{
		// x에 지수가 있을경우
		if (str[i] == 'x' && str[i+1] == '^')		
		{
			// 계수 부분
			coe = atoi(&str[c_idx]);	//계수는 먼저 받음, 주소값으로 받아 문자가 나오기전까지의 값을 정수로 받음

			if(str[c_idx] == '-')		//만약 str[c_idx]가 '-'인데
				if (coe == 0)			//거기서 coe값이 0일경우 -x일 경우밖에 없다!
					coe = -1;			//그렇다면 결과값은 -1
			if (coe < 0)				//헌데 만약 마이너스라면 계수 인덱스 + 1 -> 뒤에나오는 이프문에서 증가를 안시키기 때문
				c_idx++;

			for (j = c_idx;j < MAX_POLY;j++)//포문에 첫 시작은 계수 인덱스
			{
				if (str[j] == '+')			//계수가 양수일경우
				{
					c_idx = j + 1;			//그 다음부터 다시 포문 돌림
					break;
				}
				else if (str[j] == '-')		//계수가 음수일경우
				{
					c_idx = j;				//그 인덱스 그대로 받음 -> -값을 위에서 정수로 변환시켜야 하기 때문
					break;
				}
			}

			// 지수 부분
			d_idx = i + 2;					//만약 if문에서 str[i+1] == '^' 에서 멈춘다면 정수 인덱스는 i+2
			deg = atoi(&str[d_idx]);		//그 값을 정수로 변환

			if (coe == 0)					//만약 coe 값이 0일경우 ex)x^2, x 등등
				coe = 1;					//계수는 1
			Attach(coe, deg, &p);			//노드 추가
		}
		// x에 지수가 없을경우
		else if (str[i] == 'x' && str[i + 1] != '^')
		{
			// 계수 부분, 방식은 위에와 같습니다.
			coe = atoi(&str[c_idx]);	

			if (str[c_idx] == '-')
				if (coe == 0)
					coe = -1;
			if (coe < 0)
				c_idx++;

			for (j = c_idx;j < MAX_POLY;j++)
			{
				if (str[j] == '+')			//계수가 양수일경우
				{
					c_idx = j + 1;
					break;
				}
				else if (str[j] == '-')		//계수가 음수일경우
				{
					c_idx = j;
					break;
				}
			}
			// 지수가 없으므로 즉 '^'가 없으므로 지수는 1!
			deg = 1;

			if (coe == 0)
				coe = 1;
			Attach(coe, deg, &p);	//노드 추가
		}
		// 정수 부분
		else if (str[i] == '\0')		//제일 끝까지 가서
		{
			k = i;	// 그 배열 인덱스를 k에 받음
			while (1)
			{
				k--;	//k를 먼저 -1 -> 널문자부터 계산할 필요 x
				if (str[k] == 'x')	//상수가 없을 때
					break;
				if (str[k] == '+')		//양수 일때
				{
					coe = atoi(&str[k + 1]);	//그 다음 인덱스부터 변환
					deg = 0;					//정수이므로 지수는 0
					Attach(coe, deg, &p);		//노드추가
					break;
				}
				if (str[k] == '-')		//음수 일때
				{
					coe = atoi(&str[k]);		//음수이므로 현재 인덱스부터 변환
					deg = 0;					//정수이므로 지수는 0
					Attach(coe, deg, &p);		//노드추가
					break;
				}
				if (k == 0)				//반복문 돌면서 아무것도 해당 안될때 즉 그냥 양의 정수 ex)300, 30, 24
				{
					coe = atoi(str);	//아무것도 없는 단지 정수이므로 문자열을 바로 정수로 바꿈
					deg = 0;
					Attach(coe, deg, &p);
					break;
				}
			}
		}
	}

	head = head->link;
	return head;
}

void Attach(int coe, int deg, PolyNode **p)
{
	PolyNode *temp = (PolyNode *)malloc(sizeof(PolyNode));

	temp->coef = coe;
	temp->degree = deg;
	temp->link = NULL;

	(*p)->link = temp;
	*p = temp;
}

void Display(PolyNode *head)
{
	PolyNode *a = head;

	int cnt = 0;	// 첫 째 항을 세기위한 cnt, 만약 첫째 항이면 앞에 +를 붙이지마라! -> 첫번째 수는 +가 안붙고 나머지는 붙기 때문

	while (a != NULL)
	{
		cnt++;
		if (a->coef > 0 && a->degree == 0)		//양의 정수 일때
		{
			if(cnt == 1)
				printf("%d", a->coef);
			else
				printf("+%d", a->coef);
		}
		if (a->coef < 0 && a->degree == 0)		//음의 정수 일때
		{
			printf("%d", a->coef);
		}
		else if (a->coef == 1 && a->degree == 1) //x 일때, 양수
		{
			if (cnt == 1)
				printf("x");
			else
				printf("+x");
		}
		else if (a->coef == -1 && a->degree == 1) //-x 일때, 음수
		{
			printf("-x");
		}
		else if (a->coef == 1 && a->degree > 1)	//x^(?) 일때, 양수
		{
			if (cnt == 1)
				printf("x^%d", a->degree);
			else
				printf("+x^%d", a->degree);
		}
		else if (a->coef == 1 && a->degree > 1)	//-x^(?) 일때, 음수
		{
			printf("x^%d", a->degree);
		}
		else if (a->coef > 1 && a->degree == 1)	//(?)x 일때, 양수
		{
			if (cnt == 1)
				printf("%dx", a->coef);
			else
				printf("+%dx", a->coef);
		}
		else if (a->coef < 0 && a->degree == 1)	//(?)x 일때, 음수
		{
			printf("%dx", a->coef);
		}
		else if (a->coef > 1 && a->degree > 1)	//(?)x^(?) 일때, 양수
		{
			if (cnt == 1)
				printf("%dx^%d", a->coef, a->degree);
			else
				printf("+%dx^%d", a->coef, a->degree);
		}
		else if (a->coef < 0 && a->degree > 1)	//(?)x^(?) 일때, 음수
		{
			printf("%dx^%d", a->coef, a->degree);
		}
		a = a->link;
	}
}

void ShowAdd(PolyNode *a, PolyNode *b)
{
	printf("┌──────────────────────────────────┐\n");
	printf("│                            Polynomial ADD                          │\n");
	printf("└──────────────────────────────────┘\n");
	printf(" ["); Display(a); printf("]   ADD   ["); Display(b); printf("]\n");
}

void ShowSub(PolyNode *a, PolyNode *b)
{
	printf("┌──────────────────────────────────┐\n");
	printf("│                            Polynomial SUB                          │\n");
	printf("└──────────────────────────────────┘\n");
	printf(" ["); Display(a); printf("]   SUB   ["); Display(b); printf("]\n");
}

void ShowRet(PolyNode *a)
{
	printf("┌────────────────────────────────────\n");
	printf("│\n");
	printf("│▶         "); Display(a); printf("\n");
	printf("│\n");
	printf("└────────────────────────────────────\n");
}