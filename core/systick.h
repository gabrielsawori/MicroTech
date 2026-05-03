// core/systick.h
#ifndef SYSTICK_H
#define SYSTICK_H

#include <stdint.h>

void systick_init(uint32_t load_value);

// Variabel global untuk menghitung detak OS
extern volatile uint32_t os_tick_count;

#endif