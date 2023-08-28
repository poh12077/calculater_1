#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

// Create a node
typedef struct Node {
	char operation;
	float num;
	struct Node* next;
	struct Node* prev;
}Node;

#define BUFFER_SIZE 100

Node** phead;

void printList(struct Node* node);
void insertNumAtEnd(struct Node** head_ref, float new_data);
Node* makeLinkedList(char* buffer);
void insertOperationAtEnd(struct Node** head_ref, char new_data);
void calculate(struct Node* node);
void deleteNode( struct Node* del_node);
int multiply(struct Node* node);
int add(struct Node* node);
int searchParentheses(struct Node* node);
void insertAfter(struct Node* prev_node, float data);