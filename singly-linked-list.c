//singly-linked-list.c
#include <stdio.h>
#include <stdlib.h>

typedef struct Node{
    int key;
    struct Node* link;
} listNode; // listNode 구조체 생성, 데이터가 들어갈 key값과 연결을 위한 link

typedef struct Head{
    struct Node* first;
}headNode; // head노드 생성, 첫번째의 노드

int freeList(headNode* h){
    listNode* p = h->first;

    listNode* prev = NULL;
    while(p != NULL){
        prev = p;
        p = p->link;
        free(prev);
    }
    free(h);
    return 0;
} // 동적할당으로 받은 node의 메모리를 free를 이용해 메모리할당 해제하는 함수

headNode* initialize(headNode* h){
    if(h != NULL){
        freeList(h);
    }

    headNode* temp = (headNode*)malloc(sizeof(headNode));
    temp->first = NULL;
    return temp;
} 

int insertNode(headNode* h, int key){
    listNode* node = (listNode*)malloc(sizeof(listNode));
    node->key = key; // 입력한 key값이 node의 key값이 된다.
    node->link = NULL; // 다음 연결 부분이 없어 NULL값

    if(h->first == NULL){
        h->first = node;
        return 0;
    } // 만약 첫노드가 없을 시 현재 입력되는 node가 첫번째가 된다.

    listNode* n = h->first;
    listNode* trail = h->first;

    while(n != NULL){
        if(n->key >= key){
            if(n == h->first){
                h->first = node;
                node->link = n;
            }
            else{
                node->link = n;
                trail->link = node;
            }
            return 0;
        }
        trail = n;
        n = n->link;
    } // 만약 첫 노드가 NULL이 아닐 시 헤드의 link가 삽입된 노드를 가리키며 연결
    trail->link = node;
    return 0;
} // 노드를 삽입할 때 쓰는 함수

int insertLast(headNode* h, int key){
    listNode* node = (listNode*)malloc(sizeof(listNode));
    node->key = key;
    node->link = NULL;

    if(h->first == NULL){
        h->first = node;
        return 0;
    }

    listNode* n = h->first;
    while(n->link != NULL){
        n = n->link;
    }
    n->link = node;
    return 0;
} // 노드의 제일 마지막 부분에 삽입하는 함수

int insertFirst(headNode* h, int key){
    listNode* node = (listNode*)malloc(sizeof(listNode));
    node->key = key;

    node->link = h->first;
    h->first = node;

    return 0;
} // 노드의 첫번째 부분으로 삽입하는 함수

int deleteFirst(headNode* h){
    if(h->first == NULL){
        printf("nothing to delete. \n");
        return 0;
    }
    listNode* n = h->first;

    h->first = n->link;
    free(n);

    return 0;
} // 첫번째 노드를 삭제하는 함수

int deleteNode(headNode* h, int key){
    if(h->first == NULL){
        printf("nothing to delete. \n");
        return 0;
    }

    listNode* n = h->first;
    listNode* trail = NULL;

    while(n != NULL){
        if(n->key == key){
            if(n == h->first){
                h->first = n->link;
            }
            else{
                trail->link = n->link;
            }
            free(n);
            return 0;
        }
        trail = n;
        n = n->link;
    }
    printf("cannot find the node for key = %d\n", key);
    return 0;
} // 노드를 삭제할 때 쓰는 함수

int deleteLast(headNode* h){
    if(h->first == NULL){
        printf("nothing to delete. \n");
        return 0;
    }

    listNode* n = h->first;
    listNode* trail = NULL;

    if(n->link == NULL){
        h->first = NULL;
        free(n);
        return 0;
    }

    while(n->link != NULL){
        trail = n;
        n = n->link;
    }

    trail->link = NULL;
    free(n);

    return 0;
} // 마지막 노드를 삭제할 때 쓰는 함수

int invertList(headNode* h){
    if(h->first == NULL){
        printf("nothing to invert... \n");
        return 0;
    }
    listNode *n = h->first;
    listNode *trail = NULL;
    listNode *middle = NULL;

    while(n != NULL){
        trail = middle;
        middle = n;
        n = n->link;
        middle->link = trail;
    }
    h->first = middle;

    return 0;
} // 노드의 순서를 바꾸는 함수

void printList(headNode* h){
    int i = 0;
    listNode* p;

    printf("\n---PRINT\n");

    if(h==NULL){
        printf("nothing to print... \n");
        return;
    }

    p = h->first;

    while(p != NULL){
        printf("[ [%d]=%d ] ", i, p->key);
        p = p->link;
        i++;
    }

    printf(" items = %d\n", i); // 노드의 개수를 나타내주는 변수
} // 연결리스트의 저장되어 있는 노드들을 print해주는 함수

int main(){
    char command;
    int key;
    headNode* headnode = NULL;

    printf("----- [오준영] [2017038074] ----- \n");

    do{
		printf("----------------------------------------------------------------\n");
		printf("                     Singly Linked List                         \n");
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
			headnode = initialize(headnode);
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
}
/* command입력을 통해 호출되는 함수별로 동작을 실행한다.
삽입과 삭제의 경우 모두 연결리스트들의 link에 유의하면서 실행된다.
*/
