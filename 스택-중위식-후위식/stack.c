#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_EQUATION 100

typedef int element;
typedef struct StackNode
{
	element item;
	struct StackNode *link;	//자기 참조 구조체
} StackNode;

typedef struct
{
	StackNode *top;	//스택의 제일 마지막 노드
}StackType;
// 연결리스트 형태의 스택을 만듬

void init(StackType *s)
{
	s->top = NULL; //스택을 NULL로 초기화
}

int is_empty(StackType *s)
{
	if (s->top == NULL)	//스택이 NULL이면 비어있는 상태!
		return 1;
	else
		return 0;
}

void push(StackType *s, element item)
{
	StackNode *temp = (StackNode *)malloc(sizeof(StackNode));	//노드 생성
	if (temp == NULL)
	{
		fprintf(stderr, "메모리 할당 에러\n");
		return;
	}
	temp->item = item;	//노드의 item값 대입
	temp->link = s->top;	//top이 temp를 가리키도록 함
	s->top = temp;	//top은 temp, 제일 마지막에 들어왔으므로
}

element pop(StackType *s)
{
	if (is_empty(s))	//비어있으면 종료
	{
		fprintf(stderr, "스택이 비어있습니다\n");
		exit(1);
	}
	else
	{
		StackNode *temp = s->top;	//제일 위에 노드
		element item;

		item = s->top->item;
		s->top = s->top->link;	//top노드를 다음 노드로 바꿈

		free(temp);	//제일 위에 노드 삭제
		return item;	//제일 위에 값 반환
	}	
}

element peek(StackType *s)
{
	if (is_empty(s))	//비어있으면 종료
	{
		fprintf(stderr, "스택이 비어있습니다\n");
		exit(1);
	}
	else
	{
		return s->top->item;	//제일 위에 값 반환
	}
}

int prec(char op)	//연산자의 우선순위를 정한다
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
// 중위 표기식 -> 후위 표기식으로, infix에 출력하기 전에 그 값을 저장한다!, 후위 표기식 문자열을 받기 위해
void infix_to_postfix(char infix[], char exp[])
{
	int i = 0, j = -1;
	char ch, top_op;
	int len = strlen(exp);
	StackType *s = (StackType *)malloc(sizeof(StackType));
	if (s == NULL)
	{
		fprintf(stderr, "메모리 할당 에러\n");
		exit(1);
	}

	init(s);
	for (i = 0;i < len;i++)
	{
		ch = exp[i];
		switch (ch)
		{
		case '+': case '-': case '*': case '/':	//연산자
			while (!is_empty(s) && (prec(ch) <= prec(peek(s))))	//스택에 있는 연산자의 우선순위가 더 크거나 같으면 출력, 즉 *,/ 먼저
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
			top_op = pop(s);	//오른쪽 괄호 바로 빼고
			while (top_op != '(')	//왼쪽 괄호를 만날때까지 다 출력해버림, 즉 괄호는 어차피 제일 먼저!
			{
				infix[++j] = top_op;
				printf("%c", top_op);
				top_op = pop(s);
			}
			break;
		default:
			infix[++j] = ch;
			printf("%c", ch);	//피연산자
			break;
		}
	}
	while (!is_empty(s))	//남아있는 연산자들 출력!
	{
		infix[++j] = peek(s);
		printf("%c", pop(s));
	}
	infix[++j] = '\0'; //마지막에 널문자를 붙여준다!
}

int eval(char exp[])	//후위식 결과 값 반환
{
	int op1, op2, value, i = 0; // 피연산자 1,2, 스택삽입을 위한 변수
	int len = strlen(exp);
	char ch;
	StackType *s = (StackType *)malloc(sizeof(StackType));
	if (s == NULL)
	{
		fprintf(stderr, "메모리 할당 에러\n");
		exit(1);
	}

	init(s);
	for (i = 0;i < len;i++)
	{
		ch = exp[i];
		if (ch != '+' && ch != '-' && ch != '*' && ch != '/')	//입력이 피연산자이면
		{
			value = ch - '0';	//한자리 숫자 밖에 안댐
			push(s, value);	//그 값 push
		}
		else  //입력이 연산자라면
		{
			op2 = pop(s);		//위에 꺼
			op1 = pop(s);		//아래 꺼,	아래에서 위에를 계산하기 때문에 op2먼저 pop

			switch (ch)	//계산!
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
	return pop(s);	//스택에 남아있는 결과 값 반환!
}

int main()
{
	char buf[MAX_EQUATION];		//입력할 중위식
	char temp[MAX_EQUATION];	//후위식으로 바뀐 것을 받을 temp

	printf("┌────────────────────────┐\n");
	printf("│   과목명 : 자료구조   교수명 : 강희중 교수님   │\n");
	printf("├────────────────────────┤\n");
	printf("│     학번 : 1392056        이름 : 김준희        │\n");
	printf("└────────────────────────┘\n");
	printf("Press The Enter Key.........\n");
	
	getchar();	//enter 하면 시작!
	while (1)
	{
		printf("\n(999 입력 시 종료, 한자리 숫자만 입력 가능!)\n");
		printf("중위식 입력: ");
		scanf("%s", buf);
		if (atoi(buf) == 999)
			break;
		printf("후위식 : ");
		infix_to_postfix(temp, buf);	//temp에 후위식 저장
		printf(" = %d\n", eval(temp));	//출력
	}
	return 0;
}