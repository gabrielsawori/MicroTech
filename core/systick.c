// core/systick.c
#include "systick.h"
#include "../drivers/uart/uart.h"
#include "task.h"

// Alamat Register
#define SYSTICK_CTRL (*((volatile uint32_t *)0xE000E010))
#define SYSTICK_LOAD (*((volatile uint32_t *)0xE000E014))
#define SYSTICK_VAL  (*((volatile uint32_t *)0xE000E018))
#define ICSR         (*((volatile uint32_t *)0xE000ED04)) // Register untuk picu PendSV

volatile uint32_t os_tick_count = 0;

void systick_init(uint32_t load_value) {
    SYSTICK_CTRL = 0;          
    SYSTICK_LOAD = load_value; 
    SYSTICK_VAL = 0;           
    SYSTICK_CTRL = 0x07;       
}

void SysTick_Handler(void) {
    os_tick_count++;
    os_tick_handler(); // Beritahu Scheduler bahwa waktu telah berdetak
}