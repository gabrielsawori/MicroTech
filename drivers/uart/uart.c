// drivers/uart/uart.c
#include <stdint.h>
#include "uart.h"

// Alamat dasar (Base Address) UART0 untuk board LM3S6965
#define UART0_BASE 0x4000C000
// Data Register (Alamat untuk menulis teks)
#define UART0_DR   (*((volatile uint32_t *)(UART0_BASE + 0x00)))
// Flag Register (Alamat untuk mengecek status hardware)
#define UART0_FR   (*((volatile uint32_t *)(UART0_BASE + 0x18)))

// Flag Transmit FIFO Full (Bit ke-5)
#define UART_FR_TXFF (1 << 5)

void uart_init(void) {
    // Pada emulator QEMU board LM3S6965, UART0 sudah diinisialisasi secara otomatis.
    // Jika kita menggunakan board asli nantinya, kita perlu mengatur clock dan baud rate di sini.
}

void uart_putc(char c) {
    // Tunggu jika antrean (FIFO) pengiriman sedang penuh
    while (UART0_FR & UART_FR_TXFF);
    
    // Tulis karakter ke Data Register agar dikirim oleh hardware
    UART0_DR = c;
}

void uart_puts(const char *str) {
    // Looping hingga karakter null-terminator (\0)
    while (*str) {
        uart_putc(*str++);
    }
}

void uart_print_num(uint32_t num) {
    char buf[12];
    int i = 10;
    buf[11] = '\0'; // Null terminator
    
    if (num == 0) {
        uart_putc('0');
        return;
    }
    
    // Ubah angka menjadi karakter ASCII
    while (num > 0) {
        buf[i] = (num % 10) + '0';
        num /= 10;
        i--;
    }
    
    uart_puts(&buf[i + 1]);
}