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
#define RAMSIZE (1<<16)     // Address space = 0x0000 to 0xFFFF
#define opcode_size 147
#define byte uint8_t
#define address uint16_t

// Structure headers and initialization
struct cpu{
    address pc;         // address 
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
byte getAccumulator();
byte getRegisterX();
byte getRegisterY();
byte getStatusRegister();
byte getStackPointer();
address getProgramCounter();
int reset_registers();


/* void_functions headers */

// flag functions
void setNegativeFlag();
void clearNegativeFlag(); 
void setOverflowFlag();
void clearOverflowFlag(); 
void setBreakFlag();
void clearBreakFlag(); 
void setDecimalFlag();
void clearDecimalFlag(); 
void setInterruptFlag();
void clearInterruptFlag(); 
void setZeroFlag();
void clearZeroFlag(); 
void setCarryFlag();
void clearCarryFlag(); 

// opcode functions
void ADC(byte opcode, address pc);


/* test_functions headers */

// print register functions
void printAccumulator();
void printRegisterX();
void printRegisterY();
void printHexStatusRegister();
void printBinaryStatusRegister();
void printStackPointer();
void printAllRegs();
void printProgramCounter();
int dumpRAM(struct Computer *OurComputer, address start, address end);