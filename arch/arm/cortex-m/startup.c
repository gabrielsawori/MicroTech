// arch/arm/cortex-m/startup.c
#include <stdint.h>

extern int main(void);
extern uint32_t _estack;
extern void SysTick_Handler(void);
extern void PendSV_Handler(void); // Deklarasi PendSV

void Default_Handler(void) {
    while(1);
}

void Reset_Handler(void) {
    main();
    while(1);
}

// Interrupt Vector Table
__attribute__((section(".isr_vector")))
void (*const g_pfnVectors[])(void) = {
    (void (*)(void))&_estack,  // 0: Initial Stack Pointer
    Reset_Handler,             // 1: Reset
    Default_Handler,           // 2: NMI
    Default_Handler,           // 3: HardFault
    Default_Handler,           // 4: MemManage
    Default_Handler,           // 5: BusFault
    Default_Handler,           // 6: UsageFault
    0, 0, 0, 0,                // 7-10: Reserved
    Default_Handler,           // 11: SVCall
    Default_Handler,           // 12: Debug Monitor
    0,                         // 13: Reserved
    PendSV_Handler,            // 14: PendSV (Context Switcher)
    SysTick_Handler,           // 15: SysTick Timer
};