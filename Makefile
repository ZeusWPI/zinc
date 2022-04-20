main.out: main.c platform.h socket.h
	cris-linux-gnu-gcc -g -mcpu=v10 -mno-side-effects -mcc-init -static -nostdlib main.c -Wl,--entry=main -o main.out
