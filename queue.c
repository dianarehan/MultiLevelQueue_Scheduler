#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "queue.h"


void initializeQueue(Queue* q) {
    q->front = q->rear = NULL;
}


bool isEmpty(Queue* q) {
    return (q->front == NULL);
}


void enqueue(Queue* q, struct data value) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (!newNode) {
        fprintf(stderr, "Memory allocation error\n");
        exit(EXIT_FAILURE);
    }
    newNode->data.name = strdup(value.name);
    newNode->data.value = strdup(value.value);
    newNode->next = NULL;
    if (q->rear) {
        q->rear->next = newNode;
    }
    q->rear = newNode;
    if (!q->front) {
        q->front = newNode;
    }
}


struct data dequeue(Queue* q) {
    if (isEmpty(q)) {
        fprintf(stderr, "Queue underflow\n");
        exit(EXIT_FAILURE);
    }
    Node* temp = q->front;
    struct data data = temp->data;
    q->front = q->front->next;
    if (!q->front) {
        q->rear = NULL;
    }
    free(temp);
    return data;
}


struct data peekFront(Queue* q) {
    if (isEmpty(q)) {
        fprintf(stderr, "Queue is empty\n");
        exit(EXIT_FAILURE);
    }
    return q->front->data;
}


void displayQueue(Queue* q) {
    Node* current = q->front;
    while (current) {
        printf("Name: %s, Value: %s", current->data.name, current->data.value);
        current = current->next;
    }
}

int lengthqueue(Queue* q){
    int count = 0;
    Node* current = q->front;
    while (current != NULL) {
        count++;
        current = current->next;
    }
    return count;
}
void freeQueue(Queue* q) {
    while (!isEmpty(q)) {
        struct data data = dequeue(q);
        free(data.name);
        free(data.value);
    }
}