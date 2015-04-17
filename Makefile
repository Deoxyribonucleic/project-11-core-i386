TARGET=i686-elf

all: build/boot.o build/core.o
	$(TARGET)-gcc -T linker.ld -o build/p11-core -ffreestanding -O2 -nostdlib build/boot.o build/core.o -lgcc

build/boot.o: src/boot.asm
	$(TARGET)-as src/boot.asm -o build/boot.o

build/core.o: src/core.c
	$(TARGET)-gcc -m32 -c src/core.c -o build/core.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra

clean:
	rm -r build/*

