//doubly-linked-list.c
#include <stdio.h>
#include <stdlib.h>

typedef struct Node{
    int key; // 노드의 입력한 데이터 값
    struct Node* llink; // 다음 노드와 연결할 링크
    struct Node* rlink; // 전 노드와 연결할 링크
}listNode;

typedef struct Head{
    struct Node* first;
}headNode; // 맨처음 노드의 표시를 위한 헤드노드

int freeList(headNode* h){
    listNode *p = h->first; // p를 헤드 다음 노드로 선언

    listNode* prev = NULL; // prev라는 노드 선언
    while(p != NULL){
        prev = p;
        p = p->rlink;
        free(prev);
    } /* 만약 헤드 다음 노드인 p가 NULL이 아니면 prev는 p가 되고
      헤드의 다음 노드는 p의 다음 노드로 지정
      이후 prev를 메모리 할당 해제 = p 노드가 해제
      이 과정을 계속 반복하여 모든 list를 free
      */
    free(h); // 마지막으로 남은 헤드노드를 free
    return 0;
} // 할당된 메모리를 free할 함수

int initialize(headNode** h){
    if(*h != NULL){
        freeList(*h);
    }

    *h = (headNode*)malloc(sizeof(headNode));
    (*h)->first = NULL;
    return 1;
} 

int insertFirst(headNode* h, int key){
    listNode* node = (listNode*)malloc(sizeof(listNode)); // node의 메모리 할당
    node->key = key;  
    node->rlink = node->llink = NULL; // node의 연결부분을 NULL로 설정

    if(h->first == NULL){
        h->first = node;
        return 1;
    } // 만약 헤드 다음 노드가 NULL일 경우 선언된 노드가 헤드 다음으로 설정

    node->rlink = h->first; // node의 다음 연결이 헤드 노드 다음 노드로 설정
    node->llink = NULL;

    listNode *p = h->first; 
    p->llink = node; // p의 전링크를 node로 설정
    h->first = node; // 헤드 다음 노드를 node로 설정

    return 0;
} // 리스트의 맨처음 노드를 삽입하는 함수

int insertLast(headNode* h, int key){
    listNode* node = (listNode*)malloc(sizeof(listNode));
    node->key = key;
    node->rlink = NULL;
    node->llink = NULL;

    if(h->first == NULL){
        h->first = node;
        return 0;
    }

    listNode* n = h->first;
    while(n->rlink != NULL){
        n = n->rlink;
    }
    n->rlink = node; // n의 다음 링크를 node로 설정
    node->llink = n; // node의 전 링크를 n이라고 설정
    return 0;
}
 // 리스트의 마지막의 노드를 삽입하는 함수
int insertNode(headNode* h, int key){
    listNode* node = (listNode*)malloc(sizeof(listNode));
    node->key = key;
    node->llink = node->rlink = NULL;

    if(h->first == NULL){
        h->first = node;
        return 0;
    }
    
    listNode* n = h->first;

    while(n != NULL){
        if(n->key >= key){
            if(n== h->first){
                insertFirst(h, key);
            } 
            else{
                node->rlink = n;
                node->llink = n->llink;
                n->llink->rlink = node;
            } // 삽입될 노드의 전노드의 다음링크와 다음 노드의 전링크를 연결
            return 0;
        }
        n= n->rlink;
    }
    insertLast(h, key);
    return 0;
} // 리스트의 노드를 삽입하는 함수

int deleteFirst(headNode* h){
    if(h->first == NULL){
        printf("nothing to delete.\n");
        return 0;
    } // 헤드 다음노드가 NULL일 시 출력
    listNode *n = h->first; // 삭제할 노드를 헤드의 다음 노드로 설정
    h->first = n->rlink; // 헤드의 다음노드는 삭제할 노드 n이 다음으로 가리키던 노드로 설정

    free(n); // n의 메모리할당을 통해 노드 삭제

    return 0;
} // 맨처음 노드를 삭제하는 함수

int deleteLast(headNode* h){
    if(h->first == NULL){
        printf("nothing to delete.\n");
        return 0;
    }

    listNode* n = h->first;
    listNode* trail = NULL;

    if(n->rlink == NULL){
        h->first = NULL;
        free(n);
        return 0;
    }

    while(n->rlink != NULL){
        trail = n;
        n = n->rlink;
    }

    trail->rlink = NULL;
    free(n);

    return 0;
} // 맨마지막 노드를 삭제하는 함수

int deleteNode(headNode* h, int key){
    if(h->first == NULL){
        printf("nothing t delete.\n");
        return 1;
    }

    listNode* n = h->first;

    while(n != NULL){
        if(n->key == key){
            if(n == h->first){
                deleteFirst(h);
            }
            else if(n->rlink == NULL){
                deleteLast(h);
            }
            else{
                n->llink->rlink = n->rlink;
                n->rlink->llink = n->llink;
                free(n);
            } 
            return 1;
        }
        n = n->rlink;
    }
    printf("cannot find the node for ky = %d\n", key);
    return 1;
} /* 노드안의 데이터값과 일치하는 노드를 삭제하는 함수
    삭제후 연결되어 있던 노드들의 연결관계를 다시 설정해주는게 중요
  */
int invertList(headNode* h){
    if(h->first == NULL){
        printf("nothing to invert....\n");
        return 0;
    }
    listNode *n = h->first;
    listNode *trail = NULL;
    listNode *middle = NULL;

    while(n != NULL){
        trail = middle;
        middle = n;
        n = n->rlink;
        middle->rlink = trail;
        middle->llink = n;
    }

    h->first = middle;
    
    return 0;
} // 리스트의 순서를 뒤집어주는 함수

void printList(headNode* h){
    int i = 0;
    listNode* p;
    printf("\n---PRINT\n");

    if(h == NULL){
        printf("Nothing to print....\n");
        return;
    }

    p = h->first;

    while(p != NULL){
        printf("[ [%d]=%d ] ", i, p->key);
        p = p->rlink;
        i++;
    }
    printf("items = %d\n", i);
} // 리스트들을 나열해주는 함수 노드들의 갯수는 item을 이용하여 출력

int main(){
    char command;
	int key;
	headNode* headnode=NULL;

    printf("[----- [오준영] [2017038074] -----\n");
	do{
		printf("----------------------------------------------------------------\n");
		printf("                     Doubly Linked  List                        \n");
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
} // 명령어 입력을 통하여 리스트를 추가, 삭제, 순서바꾸기를 할 수 있음.
  // q를 누를 시 종료
