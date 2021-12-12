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


/* Function headers */

// 6502 - initialization and cycle functions
int* fetch();
struct cpu* execute();
void decode(byte opcode);
void read_in_binary_image(char* image_name);
void initalize_program_counter();

// opcode table
void build_opcode_table();

// get register functions
byte getRegA(struct Computer* OurComputer);
byte getRegX(struct Computer* OurComputer);
byte getRegY(struct Computer* OurComputer);
byte getRegSF(struct Computer* OurComputer);
byte getRegSP(struct Computer* OurComputer);
address* getRegPC(struct Computer* OurComputer);

/* void_functions headers */

// flag functions
void setNegativeFlag(struct Computer* OurComputer);
void clearNegativeFlag(struct Computer* OurComputer); 
void setOverflowFlag(struct Computer* OurComputer);
void clearOverflowFlag(struct Computer* OurComputer); 
void setBreakFlag(struct Computer* OurComputer);
void clearBreakFlag(struct Computer* OurComputer); 
void setDecimalFlag(struct Computer* OurComputer);
void clearDecimalFlag(struct Computer* OurComputer); 
void setInterruptFlag(struct Computer* OurComputer);
void clearInterruptFlag(struct Computer* OurComputer); 
void setZeroFlag(struct Computer* OurComputer);
void clearZeroFlag(struct Computer* OurComputer); 
void setCarryFlag(struct Computer* OurComputer);
void clearCarryFlag(struct Computer* OurComputer); 


// opcode functions
void ADC(byte opcode, byte* pc);


/* test_functions headers */

// print register functions
void printAccumulator(struct Computer* OurComputer);
void printRegisterX(struct Computer* OurComputer);
void printRegisterY(struct Computer* OurComputer);
void printHexStatusRegister(struct Computer* OurComputer);
void printBinaryStatusRegister(struct Computer* OurComputer);
void printStackPointer(struct Computer* OurComputer);
void printAllRegs(struct Computer* OurComputer);
void printProgramCounter(struct Computer* OurComputer);
int dumpBinaryImage(struct Computer *OurComputer, address start, address end);
