/* linker.ld */
ENTRY(Reset_Handler)

/* Definisi letak dan ukuran memori untuk board LM3S6965EVB (Cortex-M3) */
MEMORY
{
    FLASH (rx) : ORIGIN = 0x00000000, LENGTH = 256K
    RAM (rwx)  : ORIGIN = 0x20000000, LENGTH = 64K
}

/* Menentukan letak ujung Stack (di akhir RAM) */
_estack = ORIGIN(RAM) + LENGTH(RAM);

SECTIONS
{
    /* Kode program diletakkan di FLASH */
    .text : {
        *(.isr_vector)  /* Vector table harus paling awal! */
        *(.text*)       /* Kode program */
        *(.rodata*)     /* Data read-only */
        . = ALIGN(4);
    } > FLASH

    /* Data variabel global disiapkan di RAM */
    .data : {
        *(.data*)
        . = ALIGN(4);
    } > RAM AT > FLASH

    .bss : {
        *(.bss*)
        . = ALIGN(4);
    } > RAM
}