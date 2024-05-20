#ifndef QUEUE_H
#define QUEUE_H

#include <stdbool.h>

struct data
{
    char* name;
    char* value;
};
typedef struct Node {
    struct data data;
    struct Node* next;
} Node;

typedef struct {
    Node* front;
    Node* rear;
} Queue;

void initializeQueue(Queue* q);
bool isEmpty(Queue* q);
void enqueue(Queue* q, struct data value);
struct data dequeue(Queue* q);
struct data peekFront(Queue* q);
void displayQueue(Queue* q);
int lengthqueue(Queue* q);
void freeQueue(Queue* q);

#endif