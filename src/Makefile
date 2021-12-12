run: main.c 6502.o void_functions.o
	gcc main.c 6502.o void_functions.o -o $@

debug: main.c 6502.o void_functions.o test_functions.o
	gcc main.c 6502.o void_functions.o test_functions.o -o $@

%.o: %.c 6502.h
	gcc -g -c $< -o $@

clean:
	rm  *.o 