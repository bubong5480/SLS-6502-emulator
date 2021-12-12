run: main.c 6502.o void_functions.o test_functions.o
	gcc main.c 6502.o void_functions.o test_functions.o -o $@

6502.o: 6502.c 6502.h
	gcc -g -c 6502.c -o $@

void_functions.o: void_functions.c 6502.h
	gcc -g -c void_functions.c -o $@

test_functions.o: test_functions.c 6502.h
	gcc -g -c test_functions.c -o $@

clean:
	rm  *.o 