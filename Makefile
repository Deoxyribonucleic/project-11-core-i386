TARGET=i686-elf

all: build/boot.o build/core.o build/terminal.o build/lib/string.o
	$(TARGET)-gcc -T linker.ld -o build/p11-core -ffreestanding -O2 -nostdlib build/boot.o build/core.o build/terminal.o build/lib/string.o -lgcc

build/boot.o: src/boot.asm
	$(TARGET)-as src/boot.asm -o build/boot.o

build/core.o: src/core.c
	$(TARGET)-gcc -c src/core.c -o build/core.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra
	
build/terminal.o: src/terminal.c
	$(TARGET)-gcc -c src/terminal.c -o build/terminal.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra
	
build/lib/string.o: src/lib/string.c
	mkdir -p build/lib
	$(TARGET)-gcc -c src/lib/string.c -o build/lib/string.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra

clean:
	rm -r build/*

