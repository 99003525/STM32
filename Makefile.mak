CC=arm-none-eabi-gcc
MACH=cortex-m4
CFLAGS= -c -mcpu=$(MACH) -mthumb -std=gnu11 -Wall -o0
LDFLAGS= -nostdlib -T stm.ld -Wl,-Map=final.map

all:Application.o startup.o final.elf
Application.o:Application.c
	$(CC) $(CFLAGS) -o $@ $^
startup.o:startup.c
	$(CC) $(CFLAGS) -o $@ $^
final.elf: Application.o startup.o
	$(CC) $(LDFLAGS) -o $@ $^

clean:
	rm -rf *.o *.elf
	
	
