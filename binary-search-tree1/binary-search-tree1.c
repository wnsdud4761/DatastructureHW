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
}//���� Ž��Ʈ���� ����� ���� �Ҵ��ߴ� �޸𸮵��� free�����ִ� �Լ�


void freeNode(Node* ptr)
{
	if(ptr) {
		freeNode(ptr->left);
		freeNode(ptr->right);
		free(ptr);
	}
}//������ ��带 �̿��Ͽ� Ʈ���� ��带 ���� �� ����ߴ� �޸𸮸� free �����ִ� �Լ�

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
    }//�θ� ����� ������ ���� ���Ե� ����� ���� ���� ��� �θ� ����� ��������
    else{
        parentNode->right = newNode;
    }//�ƴҰ�쿡�� ���������� ���Եȴ�.

    return 1;
}// ��带 �����ϴ� �Լ�

int deleteLeafNode(Node* head, int key){
    if(head == NULL){
        printf("\n nothing to delete.\n");
        return -1;
    }//������ ��尡 ���� �� ��µǴ� �Լ�

    if(head->left == NULL){
        printf("\n nothing to delete.\n");
        return -1;
    }//������ ��尡 ���� �� ��µǴ� �Լ�

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
}//��Ͱ˻��� ���� ��� �˻� �Լ�, �Լ� ���� searchRecursive�Լ��� �� �̿��Ͽ� ���ϴ� ��带 ã�´�.

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
}//�ݺ��˻��� ���� ��� �˻� �Լ�, while���� �̿��Ͽ� �ݺ��� ���� ���ϴ� ��带 ã�´�.

int main()
{
	char command;
	int key;
	Node* head = NULL;
	Node* ptr = NULL;	/* temp */

    printf("----- [���ؿ�] [2017038074] ----- \n");

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
