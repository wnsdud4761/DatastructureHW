//postfix.c
#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<string.h>

#define MAX_STACK_SIZE 10
#define MAX_EXPRESSION_SIZE 20

typedef enum{
	lparen = 0,  
	rparen = 9,  
	times = 7,   
	divide = 6,  
	plus = 5,    
	minus = 4,   
	operand = 1 
} precedence;

char infixExp[MAX_EXPRESSION_SIZE];
char postfixExp[MAX_EXPRESSION_SIZE];
char postfixStack[MAX_STACK_SIZE];
int evalStack[MAX_STACK_SIZE];

int postfixStackTop = -1;
int evalStackTop = -1;

int evalResult = 0;

void postfixPush(char x);
char postfixPop();
void evalPush(int x);
int evalPop();
void getInfix();
precedence getToken(char symbol);
precedence getPriority(char x);
void charCat(char* c);
void toPostfix();
void debug();
void reset();
void evaluation();

int main()
{
	char command;

	printf("----- [?���??��] [2017038074] -----\n");
	
	do{
		printf("----------------------------------------------------------------\n");
		printf("               Infix to Postfix, then Evaluation               \n");
		printf("----------------------------------------------------------------\n");
		printf(" Infix=i,   Postfix=p,  Eval=e,   Debug=d,   Reset=r,   Quit=q \n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'i': case 'I':
			getInfix();
			break;
		case 'p': case 'P':
			toPostfix();
			break;
		case 'e': case 'E':
			evaluation();
			break;
		case 'd': case 'D':
			debug();
			break;
		case 'r': case 'R':
			reset();
			break;
		case 'q': case 'Q':
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;


}

void postfixPush(char x)
{
    postfixStack[++postfixStackTop] = x;
}

char postfixPop()
{
	char x;
    if(postfixStackTop == -1)
        return '\0';
    else {
    	x = postfixStack[postfixStackTop--];
    }
    return x;
}

void evalPush(int x)
{
    evalStack[++evalStackTop] = x;
}

int evalPop()
{
    if(evalStackTop == -1)
        return -1;
    else
        return evalStack[evalStackTop--];
}

void getInfix()
{
    printf("Type the expression >>> ");
    scanf("%s",infixExp);
}

precedence getToken(char symbol)
{
	switch(symbol) {
	case '(' : return lparen;
	case ')' : return rparen;
	case '+' : return plus;
	case '-' : return minus;
	case '/' : return divide;
	case '*' : return times;
	default : return operand;
	}
}

precedence getPriority(char x)
{
	return getToken(x);
}

void charCat(char* c)
{
	if (postfixExp == '\0')
		strncpy(postfixExp, c, 1);
	else
		strncat(postfixExp, c, 1);
}

void toPostfix()
{
	char *exp = infixExp;
	char x; 	
	while(*exp != '\0')
	{
		if(getPriority(*exp) == operand)
		{
			x = *exp;
        	charCat(&x);
		}
        else if(getPriority(*exp) == lparen) {

        	postfixPush(*exp);
        }
        else if(getPriority(*exp) == rparen)
        {
        	while((x = postfixPop()) != '(') {
        		charCat(&x);
        	}
        }
        else
        {
            while(getPriority(postfixStack[postfixStackTop]) >= getPriority(*exp))
            {
            	x = postfixPop();
            	charCat(&x);
            }
            postfixPush(*exp);
        }
        exp++;
	}

    while(postfixStackTop != -1)
    {
    	x = postfixPop();
    	charCat(&x);
    }

}

void debug()
{
	printf("\n---DEBUG\n");
	printf("infixExp =  %s\n", infixExp);
	printf("postExp =  %s\n", postfixExp);
	printf("eval result = %d\n", evalResult);

	printf("postfixStack : ");
	for(int i = 0; i < MAX_STACK_SIZE; i++)
		printf("%c  ", postfixStack[i]);

	printf("\n");

}

void reset()
{
	infixExp[0] = '\0';
	postfixExp[0] = '\0';

	for(int i = 0; i < MAX_STACK_SIZE; i++)
		postfixStack[i] = '\0';
         
	postfixStackTop = -1;
	evalStackTop = -1;
	evalResult = 0;
}
void evaluation()
{
	int opr1, opr2, i;

	int length = strlen(postfixExp);
	char symbol;
	evalStackTop = -1;

	for(i = 0; i < length; i++)
	{
		symbol = postfixExp[i];
		if(getToken(symbol) == operand) {
			evalPush(symbol - '0');
		}
		else {
			opr2 = evalPop();
			opr1 = evalPop();
			switch(getToken(symbol)) {
			case plus: evalPush(opr1 + opr2); break;
			case minus: evalPush(opr1 - opr2); break;
			case times: evalPush(opr1 * opr2); break;
			case divide: evalPush(opr1 / opr2); break;
			default: break;
			}
		}
	}
	evalResult = evalPop();
}
/*
중위 표기식을 후위 표기식으로 바꾸기 위한 프로그램
숫자나 변수일 경우 바로 출력
연산자를 만나면 스택에서 정해진 우선순위보다 높을 경우 모두 pop해서 출력 아닐 경우 연산자를 push
여는 괄호를 푸시
닫는 괄호를 만나면 여는 괄호까지 스택에 있는 것을 모두 pop
입력의 끝에서 스택에 있는 모든 것을 pop
*/

/*
command를 통해 i 입력 시 수식을 입력 받는다.
p 입력 시 후위표기식으로 저장
e 입력 시 수식 계산 값 저장
d 입력 시 중위표기식, 후위표기식, 계산값, stack의 상황을 출력
r 입력 시 모든 값들이 사라짐
q 입력 시 종료
*/
