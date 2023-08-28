#include "header.h"

Node* makeLinkedList(char* buffer) {
	Node* head = NULL;
	int flag = 0;
	float num = 0;
	insertOperationAtEnd(&head, '(');
	for (int i = 0; i < BUFFER_SIZE; i++) {
		char data = *(buffer + i);
		if (data == '\0') {
			if (flag == 1) {
				insertNumAtEnd(&head, num);
			}
			break;
		}

		if (data == '(' || data == ')' || data == '+' || data == '-' || data == '*' || data == '/') {
			if (flag == 1) {
				insertNumAtEnd(&head, num);
				num = 0;
				flag = 0;
			}
			insertOperationAtEnd(&head, data);
		}
		else {
			if (flag == 1) {
				num *= 10;
			}
			num += data - '0';
			flag = 1;
		}
	}
	insertOperationAtEnd(&head, ')');
	return head;
}

void insertOperationAtEnd(struct Node** head, char data) {
	struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
	newNode->operation = data;
	// assign null to next of newNode
	newNode->next = NULL;

	// store the head node temporarily (for later use)
	struct Node* temp = *head;

	// if the linked list is empty, make the newNode as head node
	if (*head == NULL) {
		newNode->prev = NULL;
		*head = newNode;
		return;
	}

	// if the linked list is not empty, traverse to the end of the linked list
	while (temp->next != NULL)
		temp = temp->next;

	// now, the last node of the linked list is temp

	// assign next of the last node (temp) to newNode
	temp->next = newNode;

	// assign prev of newNode to temp
	newNode->prev = temp;
}


void insertNumAtEnd(struct Node** head, float data) {
	struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
	newNode->num = data;
	newNode->next = NULL;
	newNode->operation = '\0';

	// store the head node temporarily (for later use)
	struct Node* temp = *head;

	// if the linked list is empty, make the newNode as head node
	if (*head == NULL) {
		newNode->prev = NULL;
		*head = newNode;
		return;
	}

	// if the linked list is not empty, traverse to the end of the linked list
	while (temp->next != NULL)
		temp = temp->next;

	// now, the last node of the linked list is temp

	// assign next of the last node (temp) to newNode
	temp->next = newNode;

	// assign prev of newNode to temp
	newNode->prev = temp;
}


// insert a node after a specific node
void insertAfter(struct Node* prev_node, float data) {
	// check if previous node is null
	if (prev_node == NULL) {
		printf("previous node cannot be null");
		return;
	}

	// allocate memory for newNode
	struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));

	// assign data to newNode
	newNode->num = data;
	newNode->operation = '\0';

	// set next of newNode to next of prev node
	newNode->next = prev_node->next;

	// set next of prev node to newNode
	prev_node->next = newNode;

	// set prev of newNode to the previous node
	newNode->prev = prev_node;

	// set prev of newNode's next to newNode
	if (newNode->next != NULL)
		newNode->next->prev = newNode;
}

// delete a node from the doubly linked list
void deleteNode( struct Node* del_node) {
	if (*phead == NULL || del_node == NULL)
		return;

	// if del_node is the head node, point the head pointer to the next of del_node
	if (*phead == del_node)
		*phead = del_node->next;

	// if del_node is not at the last node, point the prev of node next to del_node to the previous of del_node
	if (del_node->next != NULL)
		del_node->next->prev = del_node->prev;

	// if del_node is not the first node, point the next of the previous node to the next node of del_node
	if (del_node->prev != NULL)
		del_node->prev->next = del_node->next;

	// free the memory of del_node
	free(del_node);
}

// Print the linked list
void printList(struct Node* node) {
	while (node != NULL) {
		if (node->operation == '\0') {
			printf("%f ", node->num);
		}
		else {
			printf("%c ", node->operation);
		}
		node = node->next;
	}
	printf("\n");
}

int preprocess(struct Node* node) {
	while (node != NULL) {
		if (node->operation == '-') {
			if(node->next->operation=='\0') {
				if (node->prev != NULL) {
					if (node->prev->operation == '(') {
						node->next->num *= -1;
						deleteNode(node);
						return 1;
					}
				}
				node->operation = '+';
				node->next->num *= -1;
			}
		}
		node = node->next;
		if (node == NULL) {
			return 0;
		}
	}
}


// Print the linked list
int searchParentheses(struct Node* node) {
	Node* head = node;
	while (node->next!=NULL)
	{
		node = node->next;
	}

	while (node != NULL) {
		if (node->operation == '(') {
			while (multiply(node)){
				printList(head);
			}
			while (add(node)) {
				printList(head);
			}
			
			if (node->next->next->next == NULL && node->prev==NULL) {
				deleteNode(node->next->next);
				printList(node->next);
				return 0;
			}
			else {
				deleteNode(node->next->next);
				deleteNode(node);
			}
			return 1;
		}
		node = node->prev;
		if (node == NULL) {
			return 0;
		}
	}
}

void calculate(Node* head) {
	while (searchParentheses(head))
	{
		printList(head);
	}
}

int add(struct Node* node) {
	float output = 0;
	Node* p;
	while (node != NULL) {
		switch (node->operation)
		{
		case '+':
			output = (node->prev->num) + (node->next->num);
			p = node->prev->prev;
			for (int i = 0; i < 3; i++) {
				deleteNode(p->next);
			}
			insertAfter(p, output);
			return 1;
		case '-':
			output = (node->prev->num) - (node->next->num);
			p = node->prev->prev;
			for (int i = 0; i < 3; i++) {
				deleteNode(p->next);
			}
			insertAfter(p, output);
			return 1;
		case ')':
			return 0;
		}
		node = node->next;
	}
}


int multiply(struct Node* node) {
	float output = 0;
	Node* p;
	while (node != NULL) {
		switch (node->operation)
		{
		case '*':
			output = (node->prev->num) * (node->next->num);
			p = node->prev->prev;
			for (int i = 0; i < 3; i++) {
				deleteNode( p->next);
			}
			insertAfter(p, output);
			return 1;
		case '/':
			output = (node->prev->num) / (node->next->num);
			p = node->prev->prev;
			for (int i = 0; i < 3; i++) {
				deleteNode( p->next);
			}
			insertAfter(p, output);
			return 1;
		case ')':
			return 0;
		}
		node = node->next;
	}
}
