// hal/lm3s6965/hal_gpio.c
#include "../../hal/hal_gpio.h"

// Alamat Register memori untuk GPIO Port F pada LM3S6965
#define SYSCTL_RCGC2    (*((volatile uint32_t *)0x400FE108)) // Register Clock
#define GPIO_PORTF_DIR  (*((volatile uint32_t *)0x40025400)) // Register Arah (In/Out)
#define GPIO_PORTF_DEN  (*((volatile uint32_t *)0x4002551C)) // Register Digital Enable
#define GPIO_PORTF_DATA (*((volatile uint32_t *)0x400253FC)) // Register Data (High/Low)

void hal_gpio_init(void) {
    // 1. Nyalakan clock untuk GPIO Port F (Bit 5)
    SYSCTL_RCGC2 |= (1 << 5);

    // 2. Atur Pin 0 sebagai Output (Kirim listrik keluar)
    GPIO_PORTF_DIR |= (1 << 0);

    // 3. Aktifkan fungsi digital di Pin 0
    GPIO_PORTF_DEN |= (1 << 0);
}

void hal_gpio_toggle(uint8_t pin) {
    if (pin == HAL_LED_PIN) {
        // Balikkan state (Toggle) Pin 0 menggunakan operator XOR (^)
        GPIO_PORTF_DATA ^= (1 << 0);
    }
}

uint8_t hal_gpio_read(uint8_t pin) {
    if (pin == HAL_LED_PIN) {
        // Baca apakah bit ke-0 bernilai 1 atau 0
        return (GPIO_PORTF_DATA & (1 << 0)) ? 1 : 0;
    }
    return 0;
}