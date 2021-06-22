//*______ Joshua Snyder ______*//

#include <stdio.h>
#include <stdlib.h>

struct Node {
    struct Node* next;
    int data;
} node_t;

struct LinkedList {
    struct Node* head = malloc(size_of(node_t));
    struct Node* tail = malloc(size_of(node_t));
    int count;

    head->next = tail;
}

void add(struct LinkedList linkedlist, int data) {
    struct Node* newNode = malloc(sizeof(node_t));
    newNode->data = data;

    if (linkedList.head == NULL) {
        linkedList.head = newNode;
        linkedList.tail = newNode;
    }
    else {
        linkedList.tail->next = newNode;
        linkedList.tail = linkedList.tail->next;
    }
}

void displayList(struct LinkedList linkedList) {
    struct Node* currNode = linkedList.head;

    while (currNode != NULL) {
        printf("%i ", currNode->data);
        currNode = currNode->next;
    }
    printf("\n");
}

int main() {
    struct LinkedList linkedList;

    add(linkedList, 1);
    add(linkedList, 2);
    add(linkedList, 3);

    displayList(linkedList);

    return 0;
}