//binary-search-tree1.c
#include <stdio.h>
#include <stdlib.h>

typedef struct node{
    int key;
    struct node *left;
    struct node *right;
}Node;

int freeBST(Node* head)
{
	if(head->left == head){
		free(head);
		return 1;
	}

	Node* p = head->left;

	freeNode(p);

	free(head);
	return 1;
}//이진 탐색트리를 만들기 위해 할당했던 메모리들을 free시켜주는 함수


void freeNode(Node* ptr)
{
	if(ptr) {
		freeNode(ptr->left);
		freeNode(ptr->right);
		free(ptr);
	}
}//포인터 노드를 이용하여 트리의 노드를 만들 떄 사용했던 메모리를 free 시켜주는 함수

int initializeBST(Node ** h){
    if(*h != NULL){
        freeBST(*h);
    }

    *h = (Node*)malloc(sizeof(Node));
    (*h)->left = NULL;
    (*h)->right = *h;
    (*h)->key = -9999;
    return 1;
}

void inorderTraversal(Node* ptr){
    if(ptr){
        inorderTraversal(ptr->left);
        printf(" [%d] ", ptr->key);
        inorderTraversal(ptr->right);
    }
}

void preorderTraversal(Node* ptr){
    if(ptr){
        printf(" [%d] ", ptr->key);
        preorderTraversal(ptr->left);
        preorderTraversal(ptr->right);
    }
}

void postorderTraversal(Node* ptr){
    if(ptr){
        postorderTraversal(ptr->left);
        postorderTraversal(ptr->right);
        printf(" [%d] ", ptr->key);
    }
}

int insert(Node* head, int key){
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->key = key;
    newNode->left = NULL;
    newNode->right = NULL;

    if(head->left == NULL){
        head->left = newNode;
        return 1;
    }

    Node* ptr = head->left;

    Node* parentNode = NULL;
    while(ptr != NULL){
        if(ptr->key == key){
            return 1;
        }

        parentNode = ptr;

        if(ptr->key < key){
            ptr = ptr->right;
        }
        else{
            ptr = ptr->left;
        }
    }

    if(parentNode->key > key){
        parentNode->left = newNode;
    }//부모 노드의 값보다 새로 삽입된 노드의 값이 작을 경우 부모 노드의 왼쪽으로
    else{
        parentNode->right = newNode;
    }//아닐경우에는 오른쪽으로 삽입된다.

    return 1;
}// 노드를 삽입하는 함수

int deleteLeafNode(Node* head, int key){
    if(head == NULL){
        printf("\n nothing to delete.\n");
        return -1;
    }//삭제할 노드가 없을 시 출력되는 함수

    if(head->left == NULL){
        printf("\n nothing to delete.\n");
        return -1;
    }//삭제할 노드가 없을 시 출력되는 함수

    Node* ptr = head->left;

    Node* parentNode = head;

    while(ptr != NULL){
        if(ptr->left == NULL && ptr->right ==NULL){
            if(parentNode == head){
                head->left = NULL;
            }
            if(parentNode->left == ptr){
                parentNode->left = NULL;
            }
            else{
                parentNode->right = NULL;
            }
            free(ptr);
        }
        else{
            printf("the node [%d] is not a leaf \n", ptr->key);
        }

        return 1;
    }

    parentNode = ptr;

    if(ptr->key < key){
        ptr = ptr->right;
    }
    else{
        ptr = ptr->left;
    }
    printf("cannot find the node for key [%d]\n", key);
    return 1;
}

Node* searchRecursive(Node* ptr, int key)
{
	if(ptr == NULL){
        return NULL;
    }
	
    if(ptr->key < key){
        ptr = searchRecursive(ptr->right, key);
    }
		
	else if(ptr->key > key){
        ptr = searchRecursive(ptr->left, key);
    }
		
	return ptr;
}//재귀검색을 통한 노드 검색 함수, 함수 안의 searchRecursive함수를 또 이용하여 원하는 노드를 찾는다.

Node* searchIterative(Node* head, int key)
{
	Node* ptr = head->left;

	while(ptr != NULL)
	{
		if(ptr->key == key){
            return ptr;
        }
			
		if(ptr->key < key){
            ptr = ptr->right;
        } 
		else{
            ptr = ptr->left;
        }
	}

	return NULL;
}//반복검색을 통한 노드 검색 함수, while문을 이용하여 반복을 통해 원하는 노드를 찾는다.

int main()
{
	char command;
	int key;
	Node* head = NULL;
	Node* ptr = NULL;	/* temp */

    printf("----- [오준영] [2017038074] ----- \n");

	do{
		printf("\n\n");
		printf("----------------------------------------------------------------\n");
		printf("                   Binary Search Tree #1                        \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize BST       = z                                       \n");
		printf(" Insert Node          = n      Delete Leaf Node             = d \n");
		printf(" Inorder Traversal    = i      Search Node Recursively      = s \n");
		printf(" Preorder Traversal   = p      Search Node Iteratively      = f\n");
		printf(" Postorder Traversal  = t      Quit                         = q\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'z': case 'Z':
			initializeBST(&head);
			break;
		case 'q': case 'Q':
			freeBST(head);
			break;
		case 'n': case 'N':
			printf("Your Key = ");
			scanf("%d", &key);
			insert(head, key);
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteLeafNode(head, key);
			break;
		case 'f': case 'F':
			printf("Your Key = ");
			scanf("%d", &key);
			ptr = searchIterative(head, key);
			if(ptr != NULL)
				printf("\n node [%d] found at %p\n", ptr->key, ptr);
			else
				printf("\n Cannot find the node [%d]\n", key);
			break;
		case 's': case 'S':
			printf("Your Key = ");
			scanf("%d", &key);
			ptr = searchRecursive(head->left, key);
			if(ptr != NULL)
				printf("\n node [%d] found at %p\n", ptr->key, ptr);
			else
				printf("\n Cannot find the node [%d]\n", key);
			break;

		case 'i': case 'I':
			inorderTraversal(head->left);
			break;
		case 'p': case 'P':
			preorderTraversal(head->left);
			break;
		case 't': case 'T':
			postorderTraversal(head->left);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}
