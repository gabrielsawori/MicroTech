// core/mutex.h
#ifndef MUTEX_H
#define MUTEX_H

#include <stdint.h>

// Struktur data Mutex
typedef struct {
    volatile uint8_t locked;      // Status: 0 = Bebas, 1 = Terkunci
    volatile uint32_t owner_task; // ID Task yang memegang kunci
} Mutex_t;

void mutex_init(Mutex_t *mutex);
void mutex_lock(Mutex_t *mutex);
void mutex_unlock(Mutex_t *mutex);

#endif