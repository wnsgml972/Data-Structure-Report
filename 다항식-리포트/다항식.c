#define _CRT_SECURE_NO_WARNINGS //visual studio 2015 �������� §�� ���� ��Ź�帳�ϴ�.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_POLY 30
#define COMPARE(a,b) ((a)<(b) ? '<' : (a)==(b) ? '=' : '>')		//b�� �� ũ�� <, ������ =, a�� ��ũ�� >

typedef struct PolyNode
{
	int coef;	//���
	int degree;	//����
	struct PolyNode *link;
} PolyNode;

PolyNode* PolyAdd(PolyNode *a, PolyNode *b);	//�� ������ ���ϱ�
PolyNode* PolySub(PolyNode *a, PolyNode *b);	//�� ������ ����
PolyNode* CreatPoly(char *str);					//�ϳ��� ������ ����
void Attach(int coe, int deg, PolyNode **p);	//��� �߰�
void Display(PolyNode *head);					//���׽��� ������� ���
void ShowAdd(PolyNode *a, PolyNode *b);			//Add ���� ���
void ShowSub(PolyNode *a, PolyNode *b);			//Sub ���� ���
void ShowRet(PolyNode *a);						//����� ���

int main()
{
	PolyNode *A, *B, *ret;			//���׽� A, B�� �հ� ���� ���� ret
	int sel, control;				//program���ð� �ݺ��� ������ ���� control
	char a[MAX_POLY], b[MAX_POLY];	//���׽� �Է��� ���� ���ڿ�

	printf("����������������������������������������������������\n");
	printf("��   ����� : �ڷᱸ��   ������ : ������ ������   ��\n");
	printf("����������������������������������������������������\n");
	printf("��     �й� : 1392056        �̸� : ������        ��\n");
	printf("����������������������������������������������������\n");
	printf("Press The Enter Key.........\n");
	getchar();	//enter �ϸ� ����!

	while (1)
	{
		control = 1;	//control 1�� �ʱ�ȭ

		printf("������������������������������������������������������������������������\n");
		printf("��                   Polynomial's Add and Sub Program                 ��\n");
		printf("������������������������������������������������������������������������\n");
		printf("��      1.Poly Add      2.Poly Sub      3.Roll Back      4.Exit       ��\n");
		printf("������������������������������������������������������������������������\n");

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
				control = 0;	//control�� 0���� �ʱ�ȭ�� �ݺ����� ��������
				break;
			case 4:
				printf("Good Bay!!\n");
				return 0;		//���α׷� ����
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
		switch (COMPARE(a->degree, b->degree))	//a�� b�� ���� ��
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

	//a�� b�� ���� ��带 �� ó����
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
			Attach(-b->coef, b->degree, &ret);		//a���׽� -b ���׽� �̹Ƿ� b���׽��� ����� -�� �ٿ��� ��忡 �߰��Ѵ�
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

	//a�� b�� ���� ��带 �� ó����
	while (a != NULL)
	{
		Attach(a->coef, a->degree, &ret);
		a = a->link;
	}
	while (b != NULL)
	{
		Attach(-b->coef, b->degree, &ret);	//b�� -�ǹǷ� ����� -�� ���δ�!
		b = b->link;
	}

	head = head->link;
	return head;
}

PolyNode* CreatPoly(char *str)
{
	PolyNode *p, *head;			// ����� �����Ϳ� ��� ������
	int i, j, k;				// �ݺ����� ����
	int c_idx = 0, d_idx = 0;	//��� �ε���, ���� �ε���
	int coe, deg;				// ���, ����

	head = p = (PolyNode *)malloc(sizeof(PolyNode));

	for (i = 0;i < MAX_POLY;i++)
	{
		// x�� ������ �������
		if (str[i] == 'x' && str[i+1] == '^')		
		{
			// ��� �κ�
			coe = atoi(&str[c_idx]);	//����� ���� ����, �ּҰ����� �޾� ���ڰ� �������������� ���� ������ ����

			if(str[c_idx] == '-')		//���� str[c_idx]�� '-'�ε�
				if (coe == 0)			//�ű⼭ coe���� 0�ϰ�� -x�� ���ۿ� ����!
					coe = -1;			//�׷��ٸ� ������� -1
			if (coe < 0)				//�嵥 ���� ���̳ʽ���� ��� �ε��� + 1 -> �ڿ������� ���������� ������ �Ƚ�Ű�� ����
				c_idx++;

			for (j = c_idx;j < MAX_POLY;j++)//������ ù ������ ��� �ε���
			{
				if (str[j] == '+')			//����� ����ϰ��
				{
					c_idx = j + 1;			//�� �������� �ٽ� ���� ����
					break;
				}
				else if (str[j] == '-')		//����� �����ϰ��
				{
					c_idx = j;				//�� �ε��� �״�� ���� -> -���� ������ ������ ��ȯ���Ѿ� �ϱ� ����
					break;
				}
			}

			// ���� �κ�
			d_idx = i + 2;					//���� if������ str[i+1] == '^' ���� ����ٸ� ���� �ε����� i+2
			deg = atoi(&str[d_idx]);		//�� ���� ������ ��ȯ

			if (coe == 0)					//���� coe ���� 0�ϰ�� ex)x^2, x ���
				coe = 1;					//����� 1
			Attach(coe, deg, &p);			//��� �߰�
		}
		// x�� ������ �������
		else if (str[i] == 'x' && str[i + 1] != '^')
		{
			// ��� �κ�, ����� ������ �����ϴ�.
			coe = atoi(&str[c_idx]);	

			if (str[c_idx] == '-')
				if (coe == 0)
					coe = -1;
			if (coe < 0)
				c_idx++;

			for (j = c_idx;j < MAX_POLY;j++)
			{
				if (str[j] == '+')			//����� ����ϰ��
				{
					c_idx = j + 1;
					break;
				}
				else if (str[j] == '-')		//����� �����ϰ��
				{
					c_idx = j;
					break;
				}
			}
			// ������ �����Ƿ� �� '^'�� �����Ƿ� ������ 1!
			deg = 1;

			if (coe == 0)
				coe = 1;
			Attach(coe, deg, &p);	//��� �߰�
		}
		// ���� �κ�
		else if (str[i] == '\0')		//���� ������ ����
		{
			k = i;	// �� �迭 �ε����� k�� ����
			while (1)
			{
				k--;	//k�� ���� -1 -> �ι��ں��� ����� �ʿ� x
				if (str[k] == 'x')	//����� ���� ��
					break;
				if (str[k] == '+')		//��� �϶�
				{
					coe = atoi(&str[k + 1]);	//�� ���� �ε������� ��ȯ
					deg = 0;					//�����̹Ƿ� ������ 0
					Attach(coe, deg, &p);		//����߰�
					break;
				}
				if (str[k] == '-')		//���� �϶�
				{
					coe = atoi(&str[k]);		//�����̹Ƿ� ���� �ε������� ��ȯ
					deg = 0;					//�����̹Ƿ� ������ 0
					Attach(coe, deg, &p);		//����߰�
					break;
				}
				if (k == 0)				//�ݺ��� ���鼭 �ƹ��͵� �ش� �ȵɶ� �� �׳� ���� ���� ex)300, 30, 24
				{
					coe = atoi(str);	//�ƹ��͵� ���� ���� �����̹Ƿ� ���ڿ��� �ٷ� ������ �ٲ�
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

	int cnt = 0;	// ù ° ���� �������� cnt, ���� ù° ���̸� �տ� +�� ����������! -> ù��° ���� +�� �Ⱥٰ� �������� �ٱ� ����

	while (a != NULL)
	{
		cnt++;
		if (a->coef > 0 && a->degree == 0)		//���� ���� �϶�
		{
			if(cnt == 1)
				printf("%d", a->coef);
			else
				printf("+%d", a->coef);
		}
		if (a->coef < 0 && a->degree == 0)		//���� ���� �϶�
		{
			printf("%d", a->coef);
		}
		else if (a->coef == 1 && a->degree == 1) //x �϶�, ���
		{
			if (cnt == 1)
				printf("x");
			else
				printf("+x");
		}
		else if (a->coef == -1 && a->degree == 1) //-x �϶�, ����
		{
			printf("-x");
		}
		else if (a->coef == 1 && a->degree > 1)	//x^(?) �϶�, ���
		{
			if (cnt == 1)
				printf("x^%d", a->degree);
			else
				printf("+x^%d", a->degree);
		}
		else if (a->coef == 1 && a->degree > 1)	//-x^(?) �϶�, ����
		{
			printf("x^%d", a->degree);
		}
		else if (a->coef > 1 && a->degree == 1)	//(?)x �϶�, ���
		{
			if (cnt == 1)
				printf("%dx", a->coef);
			else
				printf("+%dx", a->coef);
		}
		else if (a->coef < 0 && a->degree == 1)	//(?)x �϶�, ����
		{
			printf("%dx", a->coef);
		}
		else if (a->coef > 1 && a->degree > 1)	//(?)x^(?) �϶�, ���
		{
			if (cnt == 1)
				printf("%dx^%d", a->coef, a->degree);
			else
				printf("+%dx^%d", a->coef, a->degree);
		}
		else if (a->coef < 0 && a->degree > 1)	//(?)x^(?) �϶�, ����
		{
			printf("%dx^%d", a->coef, a->degree);
		}
		a = a->link;
	}
}

void ShowAdd(PolyNode *a, PolyNode *b)
{
	printf("������������������������������������������������������������������������\n");
	printf("��                            Polynomial ADD                          ��\n");
	printf("������������������������������������������������������������������������\n");
	printf(" ["); Display(a); printf("]   ADD   ["); Display(b); printf("]\n");
}

void ShowSub(PolyNode *a, PolyNode *b)
{
	printf("������������������������������������������������������������������������\n");
	printf("��                            Polynomial SUB                          ��\n");
	printf("������������������������������������������������������������������������\n");
	printf(" ["); Display(a); printf("]   SUB   ["); Display(b); printf("]\n");
}

void ShowRet(PolyNode *a)
{
	printf("��������������������������������������������������������������������������\n");
	printf("��\n");
	printf("����         "); Display(a); printf("\n");
	printf("��\n");
	printf("��������������������������������������������������������������������������\n");
}