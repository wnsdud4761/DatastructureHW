//circular-linked-list.c
#include <stdio.h>
#include <stdlib.h>

typedef struct Node{
    int key;
    struct Node* llink;
    struct Node* rlink;
} listNode;

int freeList(listNode* h){
    if(h->rlink == h){
        free(h);
        return 1;
    } // h의 오른쪽 링크가 h가 된다는 것은 헤드 노드 이외 노드가 없다는 뜻
      // h를 바로 free해주면 list가 free
    listNode* p = h->rlink;

    listNode* prev = NULL;
    while(p != NULL && p != h){
        prev = p;
        p = p->rlink;
        free(prev);
    } // prev라는 노드를 이용하여 오른쪽으로 옮겨가며 노드를 free
    free(h);
    return 0;
}

int initialize(listNode** h){
    if(*h != NULL){
        freeList(*h);
    }
    *h = (listNode*)malloc(sizeof(listNode));
    (*h)->rlink = *h;
    (*h)->llink = *h;
    (*h)->key = -9999;
    return -1;
}

void printList(listNode* h){
    int i= 0;
    listNode* p;

    if(h == NULL){
        printf("Nothing to print....\n");
        return;
    }

    p = h->rlink;

    while(p != NULL && p != h){
        printf("[ [%d]=%d ] ", i, p->key);
		p = p->rlink;
		i++;
    } // circular이기 때문에 p가 다시 헤드노드가 될 때까지 출력을 반복
    printf("items = %d\n", i);

    printf("\n---checking addresses of links\n");
	printf("-------------------------------\n");
	printf("head node: [llink]=%p, [head]=%p, [rlink]=%p\n", h->llink, h, h->rlink);

	i = 0;
	p = h->rlink;
	while(p != NULL && p != h) {
		printf("[ [%d]=%d ] [llink]=%p, [node]=%p, [rlink]=%p\n", i, p->key, p->llink, p, p->rlink);
		p = p->rlink;
		i++;
	}
}

int insertLast(listNode* h, int key){
    if (h == NULL) return -1;

	listNode* node = (listNode*)malloc(sizeof(listNode));
	node->key = key;
	node->rlink = NULL;
	node->llink = NULL;

	if (h->rlink == h) 
	{
		h->rlink = node;
		h->llink = node;
		node->rlink = h;
		node->llink = h;
	} // 만약 노드가 헤드 노드 하나라면 헤드와 노드를 연결시켜 순환
    else {
		h->llink->rlink = node;
		node->llink = h->llink;
		h->llink = node;
		node->rlink = h;
	} // 아닐 경우 마지막 노드가 항상 헤드쪽을 가리켜야 순환  

	return 1;
}

int deleteLast(listNode* h){
    if (h->llink == h || h == NULL)
	{
		printf("nothing to delete.\n");
		return 1;
	}

	listNode* nodetoremove = h->llink;

	nodetoremove->llink->rlink = h;
	h->llink = nodetoremove->llink;

	free(nodetoremove);

	return 1;
} // nodetoremove를 이용하여 다음이 헤드인 노드를 찾아 free를 해줌으로 마지막 노드를 삭제

int insertFirst(listNode* h, int key){
    listNode* node = (listNode*)malloc(sizeof(listNode));
	node->key = key;
	node->rlink = NULL;
	node->llink = NULL;


	node->rlink = h->rlink;
	h->rlink->llink = node;
	node->llink = h;
	h->rlink = node;


	return 1;
} // 가장 첫번째로 삽입하기 위해 헤드가 다음으로 가리키던 노드와 삽입된 노드를 연결 후 삽입된 노드의 왼쪽 링크를 헤드로 연결하여 순환 유지

int deleteFirst(listNode* h){
    if (h == NULL || h->rlink == h)
	{
		printf("nothing to delete.\n");
		return 0;
	}

	listNode* nodetoremove = h->rlink;

	nodetoremove->rlink->llink = h;
	h->rlink = nodetoremove->rlink;

	free(nodetoremove);

	return 1;
} // nodetoremove를 이용하여 헤드가 삭제할 노드가 가리키고 있던 노드를 가리키게 함으로써 연결

int invertList(listNode* h){
    if(h->rlink == h || h == NULL) {
		printf("nothing to invert...\n");
		return 0;
	}
	listNode *n = h->rlink;
	listNode *trail = h;
	listNode *middle = h;

	h->llink = h->rlink;

	while(n != NULL && n != h){
		trail = middle;
		middle = n;
		n = n->rlink;
		middle->rlink = trail;
		middle->llink = n;
	}

	h->rlink = middle;

	return 0;
} // 노드의 순서를 바꾸어 주는 함수

int insertNode(listNode* h, int key){
    if(h == NULL) return -1;

	listNode* node = (listNode*)malloc(sizeof(listNode));
	node->key = key;
	node->llink = node->rlink = NULL;

	if (h->rlink == h)
	{
		insertFirst(h, key);
		return 1;
	}

	listNode* n = h->rlink;

	while(n != NULL && n != h) {
		if(n->key >= key) {
			if(n == h->rlink) {
				insertFirst(h, key);
			} 
            else { 
				node->rlink = n;
				node->llink = n->llink;
				n->llink->rlink = node;
				n->llink = node;
			} // 첫번째도 아니고 마지막도 아닌 중간에 노드를 삽입하는 경우
			return 0;
		}

		n = n->rlink;
	}

	insertLast(h, key);

	return 0;
} // 노드를 사빕하는 함수

int deleteNode(listNode* h, int key){
    if (h->rlink == h || h == NULL)
	{
		printf("nothing to delete.\n");
		return 0;
	}

	listNode* n = h->rlink;

	while(n != NULL && n != h) {
		if(n->key == key) {
			if(n == h->rlink) { 
				deleteFirst(h);
			} 
            else if (n->rlink == h){
				deleteLast(h);
			} 
            else { 
				n->llink->rlink = n->rlink;
				n->rlink->llink = n->llink;

				free(n);
			} // 중간에 있는 노드를 삭제하는 함수
			return 0;
		}

		n = n->rlink;
	}

	printf("cannot find the node for key = %d\n", key);
	return 0;
}

int main(){
    char command;
	int key;
	listNode* headnode = NULL;
    
    printf("[----- [오준영] [2017038074] -----\n");

	do{
		printf("----------------------------------------------------------------\n");
		printf("                  Doubly Circular Linked List                   \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize    = z           Print         = p \n");
		printf(" Insert Node   = i           Delete Node   = d \n");
		printf(" Insert Last   = n           Delete Last   = e\n");
		printf(" Insert First  = f           Delete First  = t\n");
		printf(" Invert List   = r           Quit          = q\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'z': case 'Z':
			initialize(&headnode);
			break;
		case 'p': case 'P':
			printList(headnode);
			break;
		case 'i': case 'I':
			printf("Your Key = ");
			scanf("%d", &key);
			insertNode(headnode, key);
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteNode(headnode, key);
			break;
		case 'n': case 'N':
			printf("Your Key = ");
			scanf("%d", &key);
			insertLast(headnode, key);
			break;
		case 'e': case 'E':
			deleteLast(headnode);
			break;
		case 'f': case 'F':
			printf("Your Key = ");
			scanf("%d", &key);
			insertFirst(headnode, key);
			break;
		case 't': case 'T':
			deleteFirst(headnode);
			break;
		case 'r': case 'R':
			invertList(headnode);
			break;
		case 'q': case 'Q':
			freeList(headnode);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
} // 명령어 입력을 통해 q를 입력하기 전까지 계속해서 프로그램을 실행
