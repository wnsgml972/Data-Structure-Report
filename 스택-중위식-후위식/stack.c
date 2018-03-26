#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_EQUATION 100

typedef int element;
typedef struct StackNode
{
	element item;
	struct StackNode *link;	//�ڱ� ���� ����ü
} StackNode;

typedef struct
{
	StackNode *top;	//������ ���� ������ ���
}StackType;
// ���Ḯ��Ʈ ������ ������ ����

void init(StackType *s)
{
	s->top = NULL; //������ NULL�� �ʱ�ȭ
}

int is_empty(StackType *s)
{
	if (s->top == NULL)	//������ NULL�̸� ����ִ� ����!
		return 1;
	else
		return 0;
}

void push(StackType *s, element item)
{
	StackNode *temp = (StackNode *)malloc(sizeof(StackNode));	//��� ����
	if (temp == NULL)
	{
		fprintf(stderr, "�޸� �Ҵ� ����\n");
		return;
	}
	temp->item = item;	//����� item�� ����
	temp->link = s->top;	//top�� temp�� ����Ű���� ��
	s->top = temp;	//top�� temp, ���� �������� �������Ƿ�
}

element pop(StackType *s)
{
	if (is_empty(s))	//��������� ����
	{
		fprintf(stderr, "������ ����ֽ��ϴ�\n");
		exit(1);
	}
	else
	{
		StackNode *temp = s->top;	//���� ���� ���
		element item;

		item = s->top->item;
		s->top = s->top->link;	//top��带 ���� ���� �ٲ�

		free(temp);	//���� ���� ��� ����
		return item;	//���� ���� �� ��ȯ
	}	
}

element peek(StackType *s)
{
	if (is_empty(s))	//��������� ����
	{
		fprintf(stderr, "������ ����ֽ��ϴ�\n");
		exit(1);
	}
	else
	{
		return s->top->item;	//���� ���� �� ��ȯ
	}
}

int prec(char op)	//�������� �켱������ ���Ѵ�
{
	switch (op)
	{
	case '(': case ')':
		return 0;
	case '+': case '-':
		return 1;
	case '*': case '/':
		return 2;
	}
	return -1;
}
// ���� ǥ��� -> ���� ǥ�������, infix�� ����ϱ� ���� �� ���� �����Ѵ�!, ���� ǥ��� ���ڿ��� �ޱ� ����
void infix_to_postfix(char infix[], char exp[])
{
	int i = 0, j = -1;
	char ch, top_op;
	int len = strlen(exp);
	StackType *s = (StackType *)malloc(sizeof(StackType));
	if (s == NULL)
	{
		fprintf(stderr, "�޸� �Ҵ� ����\n");
		exit(1);
	}

	init(s);
	for (i = 0;i < len;i++)
	{
		ch = exp[i];
		switch (ch)
		{
		case '+': case '-': case '*': case '/':	//������
			while (!is_empty(s) && (prec(ch) <= prec(peek(s))))	//���ÿ� �ִ� �������� �켱������ �� ũ�ų� ������ ���, �� *,/ ����
			{
				infix[++j] = peek(s);
				printf("%c", pop(s));
			}
			push(s, ch);
			break;
		case '(':
			push(s, ch);
			break;
		case ')':
			top_op = pop(s);	//������ ��ȣ �ٷ� ����
			while (top_op != '(')	//���� ��ȣ�� ���������� �� ����ع���, �� ��ȣ�� ������ ���� ����!
			{
				infix[++j] = top_op;
				printf("%c", top_op);
				top_op = pop(s);
			}
			break;
		default:
			infix[++j] = ch;
			printf("%c", ch);	//�ǿ�����
			break;
		}
	}
	while (!is_empty(s))	//�����ִ� �����ڵ� ���!
	{
		infix[++j] = peek(s);
		printf("%c", pop(s));
	}
	infix[++j] = '\0'; //�������� �ι��ڸ� �ٿ��ش�!
}

int eval(char exp[])	//������ ��� �� ��ȯ
{
	int op1, op2, value, i = 0; // �ǿ����� 1,2, ���û����� ���� ����
	int len = strlen(exp);
	char ch;
	StackType *s = (StackType *)malloc(sizeof(StackType));
	if (s == NULL)
	{
		fprintf(stderr, "�޸� �Ҵ� ����\n");
		exit(1);
	}

	init(s);
	for (i = 0;i < len;i++)
	{
		ch = exp[i];
		if (ch != '+' && ch != '-' && ch != '*' && ch != '/')	//�Է��� �ǿ������̸�
		{
			value = ch - '0';	//���ڸ� ���� �ۿ� �ȴ�
			push(s, value);	//�� �� push
		}
		else  //�Է��� �����ڶ��
		{
			op2 = pop(s);		//���� ��
			op1 = pop(s);		//�Ʒ� ��,	�Ʒ����� ������ ����ϱ� ������ op2���� pop

			switch (ch)	//���!
			{
			case '+':
				push(s, op1 + op2);
				break;
			case '-':
				push(s, op1 - op2);
				break;
			case '*':
				push(s, op1 * op2);
				break;
			case '/':
				push(s, op1 / op2);
				break;
			}
		}
	}
	return pop(s);	//���ÿ� �����ִ� ��� �� ��ȯ!
}

int main()
{
	char buf[MAX_EQUATION];		//�Է��� ������
	char temp[MAX_EQUATION];	//���������� �ٲ� ���� ���� temp

	printf("����������������������������������������������������\n");
	printf("��   ����� : �ڷᱸ��   ������ : ������ ������   ��\n");
	printf("����������������������������������������������������\n");
	printf("��     �й� : 1392056        �̸� : ������        ��\n");
	printf("����������������������������������������������������\n");
	printf("Press The Enter Key.........\n");
	
	getchar();	//enter �ϸ� ����!
	while (1)
	{
		printf("\n(999 �Է� �� ����, ���ڸ� ���ڸ� �Է� ����!)\n");
		printf("������ �Է�: ");
		scanf("%s", buf);
		if (atoi(buf) == 999)
			break;
		printf("������ : ");
		infix_to_postfix(temp, buf);	//temp�� ������ ����
		printf(" = %d\n", eval(temp));	//���
	}
	return 0;
}