// hal/hal_gpio.h
#ifndef HAL_GPIO_H
#define HAL_GPIO_H

#include <stdint.h>

// Definisi abstrak untuk pin LED utama di board
#define HAL_LED_PIN 0 

void hal_gpio_init(void);
void hal_gpio_toggle(uint8_t pin);
uint8_t hal_gpio_read(uint8_t pin);

#endif