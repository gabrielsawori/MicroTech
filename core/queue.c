// core/queue.c
#include "queue.h"
#include "task.h"

static inline void disable_irq(void) { __asm volatile("cpsid i"); }
static inline void enable_irq(void)  { __asm volatile("cpsie i"); }

void queue_init(Queue_t *q) {
    q->head = 0;
    q->tail = 0;
    q->count = 0;
}

// Fungsi mengirim data ke antrean (Dipanggil oleh Producer)
void queue_send(Queue_t *q, uint32_t item) {
    while (1) {
        disable_irq();
        if (q->count < MAX_QUEUE_ITEMS) {
            // Antrean masih muat, masukkan data!
            q->buffer[q->head] = item;
            q->head = (q->head + 1) % MAX_QUEUE_ITEMS;
            q->count++;
            enable_irq();
            return; // Sukses mengirim
        }
        enable_irq();
        
        // Kotak penuh! Tidur 1 tick lalu coba lagi nanti
        os_delay(1);
    }
}

// Fungsi mengambil data dari antrean (Dipanggil oleh Consumer)
void queue_receive(Queue_t *q, uint32_t *item) {
    while (1) {
        disable_irq();
        if (q->count > 0) {
            // Ada pesan! Ambil datanya
            *item = q->buffer[q->tail];
            q->tail = (q->tail + 1) % MAX_QUEUE_ITEMS;
            q->count--;
            enable_irq();
            return; // Sukses mengambil
        }
        enable_irq();
        
        // Kotak kosong! Tidur 1 tick menunggu kiriman data
        os_delay(1);
    }
}