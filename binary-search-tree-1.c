#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int key;
    struct node *left;
    struct node *right;
} Node;

int initializeBST(Node** h);

/* functions that you have to implement */
void inorderTraversal(Node* ptr);	  /* recursive inorder traversal */
void preorderTraversal(Node* ptr);    /* recursive preorder traversal */
void postorderTraversal(Node* ptr);	  /* recursive postorder traversal */
int insert(Node* head, int key);      /* insert a node to the tree */
int deleteLeafNode(Node* head, int key);  /* delete the leaf node for the key */
Node* searchRecursive(Node* ptr, int key);  /* search the node for the key */
Node* searchIterative(Node* head, int key);  /* search the node for the key */
int freeBST(Node* head); /* free all memories allocated to the tree */

/* you may add your own defined functions if necessary */

int main()
{
    char command;
    int key;
    Node* head = NULL;
    Node* ptr = NULL;	/* temp */

    do {
        printf("\n\n");
        printf("----------------------------------------------------------------\n");
        printf("                   Binary Search Tree #1                        \n");
        printf("----------------------------------------------------------------\n");
        printf(" Initialize BST       = z                                       \n");
        printf(" Insert Node          = n      Delete Node                  = d \n");
        printf(" Inorder Traversal    = i      Search Node Recursively      = s \n");
        printf(" Preorder Traversal   = p      Search Node Iteratively      = f \n");
        printf(" Postorder Traversal  = t      Quit                         = q \n");
        printf("----------------------------------------------------------------\n");

        printf("Command = ");
        scanf(" %c", &command);

        switch (command) {
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
                if (ptr != NULL)
                    printf("\n node [%d] found at %p\n", ptr->key, ptr);
                else
                    printf("\n Cannot find the node [%d]\n", key);
                break;
            case 's': case 'S':
                printf("Your Key = ");
                scanf("%d", &key);
                ptr = searchRecursive(head->left, key);
                if (ptr != NULL)
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

    } while (command != 'q' && command != 'Q');

    return 1;
}

int initializeBST(Node** h) {

    /* if the tree is not empty, then remove all allocated nodes from the tree */
    if (*h != NULL)
        freeBST(*h);

    /* create a head node */
    *h = (Node*)malloc(sizeof(Node));
    (*h)->left = NULL;	/* root */
    (*h)->right = *h;
    (*h)->key = -9999;
    return 1;
}

void inorderTraversal(Node* ptr) // recutsive 방식으로 inorder traversal 구현
{
    if (ptr) {
        inorderTraversal(ptr->left);
        printf("[%d] ", ptr->key);
        inorderTraversal(ptr->right);
    }
}

void preorderTraversal(Node* ptr) // recursive 방식으로 preorder traversal 구현
{
    if (ptr) {
        printf("[%d] ", ptr->key);
        preorderTraversal(ptr->left);
        preorderTraversal(ptr->right);
    }
}

void postorderTraversal(Node* ptr) // recursive 방식으로 postorder traversal 구현
{
    if (ptr) {
        postorderTraversal(ptr->left);
        postorderTraversal(ptr->right);
        printf("[%d] ", ptr->key);
    }
}

int insert(Node* head, int key) // insert a node to the tree
{
    Node* newNode = (Node*)malloc(sizeof(Node));  //새로운 노드를 동적할당
    newNode->key = key;
    newNode->left = newNode->right = NULL;

    if (head->left == NULL) {		//트리가 비어있을 경우 새로운 노드를 루트로 설정하고 종료
        head->left = newNode;
        return 1;
    }

    Node* parent = head;	//부모노드를 가리키는 포인터 생성
    Node* ptr = head->left;	//새로운 노드의 위치를 찾기 위한 포인터 생성

    while (ptr != NULL) {	//비어있는 노드를 찾을 때까지 반복
        if (key < ptr->key) {	//새로운 노드의 키값이 현재 노드의 키값보다 작을 경우 왼쪽 자식노드로 이동
            parent = ptr;
            ptr = ptr->left;	
        }
        else if (key > ptr->key) {	//새로운 노드의 키값이 현재 노드의 키값보다 클 경우 오른쪽 자식노드로 이동
            parent = ptr;
            ptr = ptr->right;
        }
        else {
            free(newNode);	
            return 0;	//중복된 키값이 존재할 경우 새로운 노드를 해제하고 종료
        }
    }

    if (key < parent->key)	//새로운 노드의 키값이 부모노드의 키값보다 작을 경우 왼쪽 자식노드로 삽입
        parent->left = newNode;
    else				//새로운 노드의 키값이 부모노드의 키값보다 클 경우 오른쪽 자식노드로 삽입
        parent->right = newNode;

    return 1;
}

int deleteLeafNode(Node* head, int key) // delete the leaf node for the key
{
    if (head == NULL || head->left == NULL) {	//트리가 비어있거나 루트노드가 없을 경우 메시지 출력
        printf("Nothing to delete.\n");	
        return 0;
    }

    Node* parent = head;	//부모노드를 가리키는 포인터 생성
    Node* ptr = head->left;	//삭제할 노드를 가리키는 포인터 생성

    while (ptr != NULL && ptr->key != key) {	//삭제할 노드를 찾을 때까지 반복
        parent = ptr;	
        if (key < ptr->key)	//삭제할 노드의 키값이 현재 노드의 키값보다 작을 경우 왼쪽 자식노드로 이동
            ptr = ptr->left;
        else
            ptr = ptr->right;	//삭제할 노드의 키값이 현재 노드의 키값보다 클 경우 오른쪽 자식노드로 이동
    }

    if (ptr == NULL) {	//삭제할 노드가 존재하지 않을 경우 메시지 출력
        printf("Cannot find the node [%d]\n", key);
        return 0;
    }

    if (ptr->left == NULL && ptr->right == NULL) { //삭제할 노드가 리프노드일 경우
        if (parent->left == ptr)	//부모노드의 왼쪽 자식노드일 경우 부모노드의 왼쪽 자식노드를 NULL로 설정
            parent->left = NULL;
        else						//부모노드의 오른쪽 자식노드일 경우 부모노드의 오른쪽 자식노드를 NULL로 설정
            parent->right = NULL;
        free(ptr);
        return 1;
    }

    printf("The node [%d] is not a leaf node.\n", key); //삭제할 노드가 리프노드가 아닐 경우 메시지 출력
    return 0;
}

Node* searchRecursive(Node* ptr, int key) // search the node for the key
{
    if (ptr == NULL || ptr->key == key)	//노드가 비어있거나 노드의 키값이 찾는 키값과 같을 경우 해당 노드를 반환
        return ptr;

    if (key < ptr->key)	//찾는 키값이 현재 노드의 키값보다 작을 경우 왼쪽 자식노드로 이동
        return searchRecursive(ptr->left, key);
    else			//찾는 키값이 현재 노드의 키값보다 클 경우 오른쪽 자식노드로 이동
        return searchRecursive(ptr->right, key);
}

Node* searchIterative(Node* head, int key) // search the node for the key
{
    Node* ptr = head->left;
    while (ptr != NULL && ptr->key != key) {	//찾는 키값을 가진 노드를 찾을 때까지 반복
        if (key < ptr->key)	//찾는 키값이 현재 노드의 키값보다 작을 경우 왼쪽 자식노드로 이동
            ptr = ptr->left;
        else		//찾는 키값이 현재 노드의 키값보다 클 경우 오른쪽 자식노드로 이동
            ptr = ptr->right;
    }
    return ptr;
}

int freeBST(Node* head) // free all memories allocated to the tree (freeBst 함수를 recursive 방식으로 구현)
{
    if (head == NULL)
        return 0;

    if (head->left != NULL)	//루트노드가 존재할 경우 루트노드를 기준으로 freeBST 함수 호출
        freeBST(head->left);
    if (head->right != head)	//루트노드가 아닐 경우 freeBST 함수 호출
        freeBST(head->right);

    free(head);	//해당 노드를 해제
    return 1;

	//결과적으로 freeBST 함수를 호출하면 루트노드를 기준으로 모든 노드를 해제하게 된다.
}
