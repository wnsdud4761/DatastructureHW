//graph-search.c
#include <stdio.h>
#include <stdlib.h>
#define TRUE 1
#define FALSE 0
#define MAX_VERTEX 10 
#define MAX_QUEUE_SIZE 20

int visited[MAX_VERTEX];

typedef struct graphNode{
    int vertex; // ������ ����
    struct graphNode* link;
}graphNode;

typedef struct graphType{
    int n;
    graphNode* adjacentListHeadPointer[MAX_VERTEX];
}graphType;

typedef int element;

typedef struct {
	element queue[MAX_QUEUE_SIZE];
	int front, rear;
}QueueType;

void initGraph(graphType* g){
    int v;
    g->n = 0;
    for(v=0; v<MAX_VERTEX; v++){
        g->adjacentListHeadPointer[v] = NULL;
    }
} // �׷��� �ʱ�ȭ �Լ�

void insertVertex(graphType* g, int v){
    if(g->n+1 > MAX_VERTEX){
        printf("���� ���� �ʰ�!\n");
        return;
    }

    g->n++;
} // ���� ���� �Լ�

void insertEdge(graphType* g, int tail, int head){
    graphNode* node;

    if((tail >= g->n) || (head >= g->n)){
        printf("���� ���� ����!\n");
        return;
    }

    node = (graphNode*)malloc(sizeof(graphNode));
    node->vertex = head;
    node->link = g->adjacentListHeadPointer[tail];

    g->adjacentListHeadPointer[tail] = node;
} // ���� ���� �Լ�, head�� tail�� ���� ����Ʈ�� ����

void printgraph(graphType* g){
    for(int i=0; i<g->n; i++){
        graphNode* p=g->adjacentListHeadPointer[i];
        printf("���� %d�� ��������Ʈ : ", i);
        while(p != NULL){
            printf("%d ", p->vertex);
            p = p->link;
        }
        printf("\n");
    }
} // �׷����� ������ִ� �Լ�

void init(QueueType *q)
{
	q->front = q->rear = 0;
} // ť ����ȭ �Լ�

int is_empty(QueueType *q)
{
	return (q->front == q->rear);
} // ���� ���� ���� �Լ�

int is_full(QueueType *q)
{
	return ((q->rear + 1) % MAX_QUEUE_SIZE == q->front);
} // ��ȭ ���� ���� �Լ�

void enqueue(QueueType *q, element item)
{
	if (is_full(q))
		printf("ť�� ��ȭ�����Դϴ�");
	q->rear = (q->rear + 1) % MAX_QUEUE_SIZE;
	q->queue[q->rear] = item;
} // ť�� �����ϴ� �Լ�

element dequeue(QueueType *q)
{
	if (is_empty(q))
		printf("ť�� ��������Դϴ�");
	q->front = (q->front + 1) % MAX_QUEUE_SIZE;
	return q->queue[q->front];
} // ���� �Լ�

element peek(QueueType *q)
{
	if (is_empty(q))
		printf("ť�� ��������Դϴ�");
	return q->queue[(q->front + 1) % MAX_QUEUE_SIZE];
} // ���� �Լ�

void bfsGraph(graphType* g, int v){
    graphNode *w;
    QueueType q;
    init(&q); // ť �ʱ�ȭ
    visited[v] = TRUE; // ���� v �湮 ǥ��
    printf("%d ", v); // �湮 ���� ���
    enqueue(&q, v); // ���� ������ ť�� ����
    while(!is_empty(&q)){
        v = dequeue(&q); // ť�� ����� ���� ����
        for(w=g->adjacentListHeadPointer[v]; w++; w=w->link){
            if(!visited[w->vertex]){
                visited[w->vertex] = TRUE; // �湮 ǥ��
                printf("%d ", w->vertex);
                enqueue(&q, w->vertex); // ������ ť�� ����
            } // �̹湮 ���� Ź���� ���� if��
        } // ���� ���� Ž���� ���� for��
    }
} // bfsŽ�� �Լ�

void dfsGraph(graphType* g, int v){
    graphNode *w;
    visited[v] = TRUE;
    printf("%d ", v);
    for(w = g->adjacentListHeadPointer[v]; w; w=w->link){
        if(!visited[w->vertex]){
            dfsGraph(g, w->vertex); // ���� w���� dfs���� ����
        }
    } // ���� ���� Ž���� ���� for��
} // dfsŽ�� �Լ�(��� ���)

int main()
{
	char command;
	int vertex;
    int head;
    int tail;
    graphType *g;
    g = (graphType*)malloc(sizeof(graphType));

    printf("----- [���ؿ�] [2017038074] ----- \n");

	do{
		printf("\n\n");
		printf("----------------------------------------------------------------\n");
		printf("                   Graph Searches                         \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize Graph     = z                                       \n");
		printf(" Insert Vertex        = v      Insert Edge             = e \n");
		printf(" Depth First Search   = d      Breath First Search     = b \n");
		printf(" Print Graph          = p      Quit                    = q \n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'z': case 'Z':
			initGraph(g);
			break;
		case 'v': case 'V':
            printf("Your vertex = ");
            scanf("%d", &vertex);
            insertVertex(g, vertex);
			break;
		case 'e': case 'E':
			printf("Your head & tail = ");
			scanf("%d %d", &head, &tail);
			insertEdge(g, head, tail);
			break;
		case 'd': case 'D':
            bfsGraph(g, 0);
			break;
		case 'b': case 'B':
            bfsGraph(g, 0);
			break;
		case 'p': case 'P':
			printgraph(g);
			break;
        case 'q': case 'Q':
			free(g);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}
