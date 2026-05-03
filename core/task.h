// core/task.h
#ifndef TASK_H
#define TASK_H

#include <stdint.h>

void task_create(void (*task_func)(void));
void os_start(void);

void os_delay(uint32_t ticks);
void os_tick_handler(void);

#endif