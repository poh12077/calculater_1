#include "header.h"


int main() {

	char buffer[BUFFER_SIZE];
	memset(buffer, '\0', BUFFER_SIZE);

	while (1)
	{
		printf("input :");
		scanf("%s", buffer);

		Node* head = NULL;
		head = makeLinkedList(buffer);
		phead = head;

		printList(head);
		while (preprocess(head))
		printList(head);

		calculate(head);
	}
	
	return 0;
}