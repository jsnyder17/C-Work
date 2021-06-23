//*______ Joshua Snyder ______*//

#include <stdio.h>
#include <stdlib.h>

struct Node {
    struct Node* next;
    int data;
} node_t;

struct Stack {
    struct Node* head;
    int count;
} stack_t;

void push(struct Stack* stack, const int DATA) {
    struct Node* newNode = malloc(sizeof(node_t));
    newNode->data = DATA;

    if (stack->head == NULL) {
        stack->head = newNode;
    }
    else {
        newNode->next = stack->head;
        stack->head = newNode;
    }

    stack->count += 1;

    printf("Added %i \n", newNode->data);
}
void pop(struct Stack* stack) {
    struct Node* currNode = stack->head;
    int data;

    data = stack->head->data;

    stack->head = stack->head->next;

    stack->count -= 1;

    printf("Popped %i\n", data);
}
void display(struct Stack* stack) {
    struct Node* currNode = stack->head;

    printf("------ STACK ------\n");
    while (currNode != NULL) {
        printf("%i ", currNode->data);
        currNode = currNode->next;
    }
    printf("\n-------------------\n");
    printf("(%i) items. \n", stack->count);
}

int main(void) {
    struct Stack stack;
    int i;

    stack.count = 0;

    for (i = 0; i < 10; ++i) {
        push((struct Stack*)&stack, i);
    }

    display((struct Stack*)&stack);

    for (i = 0; i < 10; ++i) {
        pop((struct Stack*)&stack);
        display((struct Stack*)&stack);
    }
}