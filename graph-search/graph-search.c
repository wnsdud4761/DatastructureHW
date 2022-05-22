//graph-search.c
#include <stdio.h>
#include <stdlib.h>
#define TRUE 1
#define FALSE 0
#define MAX_VERTEX 10 
#define MAX_QUEUE_SIZE 20

int visited[MAX_VERTEX];

typedef struct graphNode{
    int vertex; // 정점의 개수
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
} // 그래프 초기화 함수

void insertVertex(graphType* g, int v){
    if(g->n+1 > MAX_VERTEX){
        printf("정점 개수 초과!\n");
        return;
    }

    g->n++;
} // 정점 삽입 함수

void insertEdge(graphType* g, int tail, int head){
    graphNode* node;

    if((tail >= g->n) || (head >= g->n)){
        printf("정점 개수 오류!\n");
        return;
    }

    node = (graphNode*)malloc(sizeof(graphNode));
    node->vertex = head;
    node->link = g->adjacentListHeadPointer[tail];

    g->adjacentListHeadPointer[tail] = node;
} // 간선 삽입 함수, head를 tail의 인접 리스트에 삽입

void printgraph(graphType* g){
    for(int i=0; i<g->n; i++){
        graphNode* p=g->adjacentListHeadPointer[i];
        printf("정점 %d의 인접리스트 : ", i);
        while(p != NULL){
            printf("%d ", p->vertex);
            p = p->link;
        }
        printf("\n");
    }
} // 그래프를 출력해주는 함수

void init(QueueType *q)
{
	q->front = q->rear = 0;
} // 큐 조기화 함수

int is_empty(QueueType *q)
{
	return (q->front == q->rear);
} // 공백 상태 검출 함수

int is_full(QueueType *q)
{
	return ((q->rear + 1) % MAX_QUEUE_SIZE == q->front);
} // 포화 상태 검출 함수

void enqueue(QueueType *q, element item)
{
	if (is_full(q))
		printf("큐가 포화상태입니다");
	q->rear = (q->rear + 1) % MAX_QUEUE_SIZE;
	q->queue[q->rear] = item;
} // 큐에 삽입하는 함수

element dequeue(QueueType *q)
{
	if (is_empty(q))
		printf("큐가 공백상태입니다");
	q->front = (q->front + 1) % MAX_QUEUE_SIZE;
	return q->queue[q->front];
} // 삭제 함수

element peek(QueueType *q)
{
	if (is_empty(q))
		printf("큐가 공백상태입니다");
	return q->queue[(q->front + 1) % MAX_QUEUE_SIZE];
} // 삭제 함수

void bfsGraph(graphType* g, int v){
    graphNode *w;
    QueueType q;
    init(&q); // 큐 초기화
    visited[v] = TRUE; // 정점 v 방문 표시
    printf("%d ", v); // 방문 정점 출력
    enqueue(&q, v); // 시작 정점을 큐에 저장
    while(!is_empty(&q)){
        v = dequeue(&q); // 큐에 저장된 정점 선택
        for(w=g->adjacentListHeadPointer[v]; w++; w=w->link){
            if(!visited[w->vertex]){
                visited[w->vertex] = TRUE; // 방문 표시
                printf("%d ", w->vertex);
                enqueue(&q, w->vertex); // 정점을 큐에 삽입
            } // 미방문 정점 탁색을 위한 if문
        } // 인접 정점 탐색을 위한 for문
    }
} // bfs탐색 함수

void dfsGraph(graphType* g, int v){
    graphNode *w;
    visited[v] = TRUE;
    printf("%d ", v);
    for(w = g->adjacentListHeadPointer[v]; w; w=w->link){
        if(!visited[w->vertex]){
            dfsGraph(g, w->vertex); // 정점 w에서 dfs새로 시작
        }
    } // 인접 정점 탐색을 위한 for문
} // dfs탐색 함수(재귀 사용)

int main()
{
	char command;
	int vertex;
    int head;
    int tail;
    graphType *g;
    g = (graphType*)malloc(sizeof(graphType));

    printf("----- [오준영] [2017038074] ----- \n");

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
