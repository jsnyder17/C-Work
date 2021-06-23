//*______ Joshua Snyder ______*//

#include <stdio.h>
#include <stdlib.h>

struct Node {
    struct Node* next;
    int data;
} node_t;

struct Queue {
    struct Node* head;
    int count;
} queue_t;


void push(struct Queue* queue, const int DATA) {
    struct Node* newNode = malloc(sizeof(node_t));
    newNode->data = DATA;
    
    if (queue->head == NULL) {
        queue->head = newNode;
    }
    else {
        struct Node* currNode = queue->head;

        while (currNode->next != NULL) {
            currNode = currNode->next;
        }

        currNode->next = newNode;
    }

    ++queue->count;
}
int pop(struct Queue* queue) {
    int data = queue->head->data;

    queue->head = queue->head->next;

    --queue->count;

    return data;
}
void display(struct Queue* queue) {
    struct Node* currNode = queue->head;

    printf("------ QUEUE ------\n");
    while (currNode != NULL) {
        printf("%i ", currNode->data);
        currNode = currNode->next;
    }
    printf("\n-------------------\n");
    printf("(%i) items. \n", queue->count);
}

int main(void) {
    struct Queue queue;
    int i;

    queue.count = 0;

    for (i = 0; i < 10; ++i) {
        push(&queue, i);
    }

    display(&queue);

    printf("All items added to queue. \n");

    for (i = 0; i < 10; ++i) {
        printf("Popped %i\n", pop(&queue));
        display(&queue);
    }

    printf("Finished popping queue. \n");

    return 0;
}