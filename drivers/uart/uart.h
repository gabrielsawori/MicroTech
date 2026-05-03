// drivers/uart/uart.h
#ifndef UART_H
#define UART_H

#include <stdint.h>  // <-- Tambahkan baris ini!

void uart_init(void);
void uart_putc(char c);
void uart_puts(const char *str);
void uart_print_num(uint32_t num);

#endif