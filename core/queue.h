// core/queue.h
#ifndef QUEUE_H
#define QUEUE_H

#include <stdint.h>

#define MAX_QUEUE_ITEMS 10 // Kapasitas maksimal antrean

// Struktur data Circular Queue
typedef struct {
    uint32_t buffer[MAX_QUEUE_ITEMS];
    uint32_t head;
    uint32_t tail;
    volatile uint32_t count;
} Queue_t;

void queue_init(Queue_t *q);
void queue_send(Queue_t *q, uint32_t item);
void queue_receive(Queue_t *q, uint32_t *item);

#endif