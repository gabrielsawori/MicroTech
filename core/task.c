// core/task.c
#include "task.h"
#include "systick.h"

#define MAX_TASKS 3  // Diperbesar menjadi 3 karena kita akan punya Idle Task bawaan!
#define STACK_SIZE 256

// TCB Baru: Ditambah delay_ticks (Ukuran struct ini pas 8 byte, penting untuk Assembly)
typedef struct {
    uint32_t *sp;           // Offset 0
    uint32_t delay_ticks;   // Offset 4
} TCB_t;

TCB_t tasks[MAX_TASKS];
uint32_t task_stacks[MAX_TASKS][STACK_SIZE];

volatile uint32_t current_task = 0;
volatile uint32_t next_task = 0;  // Variabel baru untuk Scheduler pintar
volatile uint32_t task_count = 0;

void task_create(void (*task_func)(void)) {
    if (task_count >= MAX_TASKS) return;

    uint32_t *sp = &task_stacks[task_count][STACK_SIZE];
    
    *(--sp) = 0x01000000;          
    *(--sp) = (uint32_t)task_func; 
    *(--sp) = 0xFFFFFFFD;          
    *(--sp) = 0; *(--sp) = 0; *(--sp) = 0; *(--sp) = 0; *(--sp) = 0; 
    for (int i = 0; i < 8; i++) *(--sp) = 0;

    tasks[task_count].sp = sp;
    tasks[task_count].delay_ticks = 0; // Task baru langsung siap (tidak delay)
    task_count++;
}

// Idle Task Bawaan OS: Berjalan kalau semua task lain sedang tidur
void idle_task(void) {
    while(1) {
        // WFI (Wait For Interrupt): Fitur hardware untuk menidurkan CPU dan menghemat daya!
        __asm volatile("wfi"); 
    }
}

void os_start(void) {
    // Otomatis daftarkan Idle Task sebagai task terakhir
    task_create(idle_task);

    __asm volatile("msr psp, %0" : : "r" (tasks[0].sp));
    __asm volatile("mov r0, #2 \n\t msr control, r0 \n\t isb \n\t");
    
    systick_init(120000); 
    
    void (*task_func)(void) = (void (*)(void))task_stacks[0][STACK_SIZE - 2]; 
    task_func();
}

// Scheduler Pintar: Mencari task yang tidak sedang tidur
void os_schedule(void) {
    for (int i = 0; i < task_count; i++) {
        next_task = (current_task + 1 + i) % task_count;
        if (tasks[next_task].delay_ticks == 0) {
            break; // Ketemu task yang siap dieksekusi!
        }
    }
    
    // Jika harus pindah task, picu Context Switch
    if (next_task != current_task) {
        *((volatile uint32_t *)0xE000ED04) |= (1 << 28);
    }
}

// Fungsi Penundaan Non-Blocking
void os_delay(uint32_t ticks) {
    tasks[current_task].delay_ticks = ticks; // Set timer tidur
    os_schedule();                           // Cari task lain dan serahkan CPU
}

// Dipanggil setiap detak jantung OS (oleh SysTick)
void os_tick_handler(void) {
    for (int i = 0; i < task_count; i++) {
        if (tasks[i].delay_ticks > 0) {
            tasks[i].delay_ticks--; // Kurangi waktu tidur
        }
    }
    os_schedule(); // Cek apakah ada task yang baru bangun
}

// Assembly Context Switch yang sudah diperbarui agar membaca next_task dari C
__attribute__((naked)) void PendSV_Handler(void) {
    __asm volatile(
        "mrs r0, psp \n\t"
        "stmdb r0!, {r4-r11} \n\t"

        // Simpan SP ke tasks[current_task].sp
        "ldr r1, =current_task \n\t"
        "ldr r2, [r1] \n\t"
        "ldr r3, =tasks \n\t"
        "lsl r2, r2, #3 \n\t"      // r2 = current_task * 8 bytes (ukuran struct TCB_t)
        "add r2, r3, r2 \n\t"      
        "str r0, [r2] \n\t"        

        // current_task = next_task
        "ldr r4, =next_task \n\t"
        "ldr r5, [r4] \n\t"
        "str r5, [r1] \n\t"

        // Ambil SP dari tasks[next_task].sp
        "lsl r5, r5, #3 \n\t"      
        "add r5, r3, r5 \n\t"      
        "ldr r0, [r5] \n\t"        

        "ldmia r0!, {r4-r11} \n\t"
        "msr psp, r0 \n\t"
        "bx lr \n\t"
    );
}