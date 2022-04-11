//circularQ.c
#include <stdio.h>
#include <stdlib.h>

#define MAX_QUEUE_SIZE 4

typedef char element;
typedef struct {
	element queue[MAX_QUEUE_SIZE];
	int front, rear;
}QType;

QType *createQ(){
	QType *cQ;
	cQ = (QType *)malloc(sizeof(QType)); // QType 구조체의 크기만큼 할당
	cQ->front = 0;
	cQ->rear = 0;
	return cQ;
} //큐를 생성하는 함수 

int freeQ(QType *cQ){
	if(cQ == NULL) return 1;

	free(cQ);

	return 1;
} // 동적할당된 큐를 free시키는 함수

int isEmpty(QType *cQ){
	if(cQ->front == cQ->rear){
		printf("empty");

		return 1;
	}
	else return 0;
} // 비어있을 시 실행되는 함수

int isFull(QType *cQ){
	if(((cQ->rear+1)%MAX_QUEUE_SIZE) == cQ->front){
		printf("full");
		return 1;
	}
} // 다 찼을 시 실행되는 함수

void enQ(QType *cQ, element item){
	if(isFull(cQ)) return;
	else{
		cQ->rear = (cQ->rear + 1) % MAX_QUEUE_SIZE;
		cQ->queue[cQ->rear] = item;
	}
}

void deQ(QType *cQ, element* item){
	if(isEmpty(cQ)) return;
	else{
		cQ->front = (cQ->front + 1)%MAX_QUEUE_SIZE;
		*item = cQ->queue[cQ->front];
		return;
	}
}

void printQ(QType *cQ){
	int i, first, last;

	first = (cQ->front + 1)%MAX_QUEUE_SIZE;
	last = (cQ->rear + 1)%MAX_QUEUE_SIZE;

	printf("Circular Queue : [");

	i = first;
	while(i != last){
		printf("%c", cQ->queue[i]);
		i = (i+1)%MAX_QUEUE_SIZE;
	}
	printf(" ]\n");
} // 큐를 출력하는 함수

void debugQ(QType *cQ){
	printf("\n---DEBUG\n");
	for(int i = 0; i < MAX_QUEUE_SIZE; i++)
	{
		if(i == cQ->front) {
			printf("  [%d] = front\n", i);
			continue;
		}
		printf("  [%d] = %c\n", i, cQ->queue[i]);

	}
	
	printf("front = %d, rear = %d\n", cQ->front, cQ->rear);
} // 큐를 디버그하는 함수

element getElement(){
	element item;
	printf("input = ");
	scanf(" %c", &item);
	return item;
} // element를 입력하는 함수

int main(void){
	QType *cQ = createQ(); // 큐생성
	element data;

	char command; // 커맨드 입력을 통해 삽입, 삭제, 출력, 디버그, 끝내기를 선택

	printf("----- [오준영] [2017038074] -----\n");

	do{
		printf("\n-----------------------------------------------------\n");
		printf("                     Circular Q                   \n");
		printf("------------------------------------------------------\n");
		printf(" Insert=i,  Delete=d,   PrintQ=p,   Debug=b,   Quit=q \n");
		printf("------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'i': case 'I':
			data = getElement(); // getElement함수를 통해 data를 입력받는다.
			enQ(cQ, data); // enQ함수를 통해 큐 삽입
			break;
		case 'd': case 'D':
			deQ(cQ,&data); // deQ함수를 통해 큐 삭제
			break;
		case 'p': case 'P':
			printQ(cQ); // printQ함수를 통해 현재까지의 큐 출력
			break;
		case 'b': case 'B':
			debugQ(cQ); // debugQ함수를 통해 큐 디버그
			break;
		case 'q': case 'Q':
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}
	while(command != 'q' && command != 'Q');

	return 1;
}

