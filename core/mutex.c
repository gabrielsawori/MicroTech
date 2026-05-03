// core/mutex.c
#include "mutex.h"
#include "task.h"

// Ambil variabel current_task dari task.c
extern volatile uint32_t current_task;

// Fungsi inline Assembly untuk mematikan dan menyalakan interupsi (agar prosesnya atomic)
static inline void disable_irq(void) { __asm volatile("cpsid i"); }
static inline void enable_irq(void)  { __asm volatile("cpsie i"); }

void mutex_init(Mutex_t *mutex) {
    mutex->locked = 0;
    mutex->owner_task = 0xFFFFFFFF; // Default: Tidak ada pemilik
}

void mutex_lock(Mutex_t *mutex) {
    while (1) {
        disable_irq(); // Matikan interupsi (Scheduler tidak bisa memotong di sini)
        
        if (mutex->locked == 0) {
            // Kunci bebas! Kita ambil kuncinya.
            mutex->locked = 1;
            mutex->owner_task = current_task;
            enable_irq(); // Nyalakan interupsi kembali
            return;       // Sukses mengunci, keluar dari fungsi
        }
        
        enable_irq(); // Kunci sedang dipakai, nyalakan interupsi lagi
        
        // Karena fasilitas sedang dikunci task lain, kita tidur 1 tick 
        // lalu cek lagi nanti (mencegah CPU hang).
        os_delay(1); 
    }
}

void mutex_unlock(Mutex_t *mutex) {
    disable_irq();
    
    // Pastikan yang membuka gembok adalah task yang memegang kunci
    if (mutex->locked == 1 && mutex->owner_task == current_task) {
        mutex->locked = 0;
        mutex->owner_task = 0xFFFFFFFF;
    }
    
    enable_irq();
}