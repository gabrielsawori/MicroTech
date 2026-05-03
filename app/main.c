// app/main.c
#include "../drivers/uart/uart.h"
#include "../core/task.h"
#include "../hal/hal_gpio.h"

// Task khusus untuk berkedip (Blinky)
void task_blinky(void) {
    while(1) {
        // Perintahkan HAL untuk membalikkan arus listrik di pin LED!
        hal_gpio_toggle(HAL_LED_PIN);
        
        // Baca status pin saat ini (apakah sedang ada listrik atau tidak?)
        if (hal_gpio_read(HAL_LED_PIN)) {
            uart_puts("[Blinky Task] LED: NYALA (*)\n");
        } else {
            uart_puts("[Blinky Task] LED: MATI  ( )\n");
        }
        
        // Tidur 100 ticks (sekitar 1 detik)
        os_delay(100);
    }
}

// Task lain untuk membuktikan multitasking tetap jalan
void task_background(void) {
    while(1) {
        uart_puts("[Background] Sistem berjalan stabil...\n");
        os_delay(250); // Muncul lebih jarang (setiap 2.5 detik)
    }
}

int main(void) {
    uart_init();
    
    // Inisialisasi HAL GPIO
    hal_gpio_init();
    
    uart_puts("\n==================================\n");
    uart_puts("   MicroTech OS v0.8: HAL Blinky! \n");
    uart_puts("==================================\n");
    
    task_create(task_blinky);
    task_create(task_background);
    
    uart_puts("Starting OS Scheduler...\n");
    os_start();
    
    while(1);
    return 0;
}