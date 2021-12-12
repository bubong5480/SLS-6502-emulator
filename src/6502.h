#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
// For open
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
// For read
#include <unistd.h>
// For opcode table
#include "uthash.h"

// Type definitions
#define RAMSIZE (1<<16)
#define opcode_size 147
#define byte uint8_t
#define address uint16_t

// Structure headers and initialization
struct cpu{
    address* pc; 
    byte accumulator; 
    byte register_x; 
    byte register_y; 
    byte status_register;
    byte stack_pointer;
};

struct opcode_table{
    byte opcodes_key;
    byte* opcode_function; 
    UT_hash_handle hh;
};

struct Computer{
    byte* RAM;
    struct cpu* cpu_inst;
    struct opcode_table *opcodes;
};

struct Computer* OurComputer;
char** opcode_names;

struct return_{
    address pc;
    byte arg;
};

struct return_ ret; 


// Function headers
// CPU - initialization and cycle functions
int* fetch();
struct cpu* execute();
void decode(byte opcode);
void read_in_binary_image(char* image_name);
void initalize_program_counter();

// opcode table
void build_opcode_table();

/* void_functions headers */

// opcode functions
void ADC(byte opcode, byte* pc);


/* test_functions headers */

// print register functions
void getAccumulator(struct Computer* OurComputer);
void getRegisterX(struct Computer* OurComputer);
void getRegisterY(struct Computer* OurComputer);
void getStatusRegister(struct Computer* OurComputer);
void getStackPointer(struct Computer* OurComputer);
void getAllRegs(struct Computer* OurComputer);
void getProgramCounter(struct Computer* OurComputer);


