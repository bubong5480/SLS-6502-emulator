all: 6502 debug test

6502: 6502.c 6502.o void_functions.o
	gcc 6502.c 6502.o void_functions.o -o $@

debug: 6502.c 6502.o void_functions.o test_functions.o
	gcc 6502.c 6502.o void_functions.o test_functions.o -o $@

%.o: %.c 6502.h
	gcc -g -c $< -o $@

test: 
	gcc -Wall -c void_functions.c -Wno-nullability-completeness
	gcc -Wall -c test_functions.c -Wno-nullability-completeness
	gcc -Wall -c 6502.c -Wno-nullability-completeness
	gcc -o testprogram void_functions.o test_functions.o 6502.o 6502.h

clean:
	rm  *.o 
	rm -rf testprogram


