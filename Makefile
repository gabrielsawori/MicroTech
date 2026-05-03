# Makefile
CC = arm-none-eabi-gcc
MACH = cortex-m3
CFLAGS = -c -mcpu=$(MACH) -mthumb -std=gnu11 -Wall -O0
LDFLAGS = -nostdlib -T linker.ld -Wl,-Map=microtech.map

# File-file yang akan dikompilasi (Task masuk di sini)
# Makefile (Cukup ubah bagian OBJS saja)
OBJS = arch/arm/cortex-m/startup.o \
       drivers/uart/uart.o \
       core/systick.o \
       core/task.o \
       core/mutex.o \
       core/queue.o \
       hal/lm3s6965/hal_gpio.o \
       app/main.o

all: microtech.elf

microtech.elf: $(OBJS)
	$(CC) $(LDFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -o $@ $<

clean:
	rm -rf arch/arm/cortex-m/*.o drivers/uart/*.o core/*.o hal/lm3s6965/*.o app/*.o *.elf *.map