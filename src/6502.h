#ifndef SIX_FIVE_2_H
#define SIX_FIVE_2_H

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
#define HASH_FIND_BYTE(head,findbyte,out)                                          \
    HASH_FIND(hh,head,findbyte,sizeof(byte),out)

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
    void (*opcode_function)(byte, address); 
    UT_hash_handle hh;
};

struct Computer{
    byte* RAM;
    struct cpu* cpu_inst;
    struct opcode_table *opcodes;
};

struct Computer* OurComputer;

struct return_{
    address pc;
    byte arg;
};

struct return_ ret; 

/* Function headers */

// 6502 - initialization and cycle functions
byte fetch(void);
struct cpu* execute();
void decode(byte opcode);
void read_in_binary_image(char* image_name);
void initalize_program_counter();

// opcode table
void build_opcode_table(void);

// get register functions
byte getAccumulator(void);
byte getRegisterX(void);
byte getRegisterY(void);
byte getStatusRegister(void);
byte getStackPointer(void);
address getProgramCounter(void);
int reset_registers(void);


/* void_functions headers */

// flag functions
void setNegativeFlag(void);
void clearNegativeFlag(void); 
void setOverflowFlag(void);
void clearOverflowFlag(void); 
void setBreakFlag(void);
void clearBreakFlag(void); 
void setDecimalFlag(void);
void clearDecimalFlag(void); 
void setInterruptFlag(void);
void clearInterruptFlag(void); 
void setZeroFlag(void);
void clearZeroFlag(void); 
void setCarryFlag(void);
void clearCarryFlag(void); 

// opcode functions
void ADC(byte, address);
void AND(byte, address);
void ASL(byte, address);
void BCC(byte, address);
void BIT(byte, address);
void BMI(byte, address);
void BNE(byte, address);
void BPL(byte, address);
void BRK(byte, address);
void BVC(byte, address);
void BVS(byte, address);
void CLC(byte, address);
void CLD(byte, address);
void CLI(byte, address);
void CLV(byte, address);
void CMP(byte, address);
void CPX(byte, address);
void CPY(byte, address);
void DEC(byte, address);
void DEX(byte, address);
void DEY(byte, address);
void EOR(byte, address);
void INC(byte, address);
void INX(byte, address);
void INY(byte, address);
void JMP(byte, address);
void JSR(byte, address);
void LDA(byte, address);
void LDX(byte, address);
void LDY(byte, address);
void LSR(byte, address);
void NOP(byte, address);
void ORA(byte, address);
void PHA(byte, address);
void PHP(byte, address);
void PLA(byte, address);
void PLP(byte, address);
void ROL(byte, address);
void ROR(byte, address);
void RTI(byte, address);
void RTS(byte, address);
void SBC(byte, address);
void SEC(byte, address);
void SED(byte, address);
void SEI(byte, address);
void STA(byte, address);
void STX(byte, address);
void STY(byte, address);
void TAX(byte, address);
void TAY(byte, address);
void TSX(byte, address);
void TXA(byte, address);
void TXS(byte, address);
void TYA(byte, address);
void BCS(byte, address);
void BEQ(byte, address);
void BMI(byte, address);
void BNE(byte, address);



/* test_functions headers */

// print register functions
void printAccumulator(void);
void printRegisterX(void);
void printRegisterY(void);
void printHexStatusRegister(void);
void printBinaryStatusRegister(void);
void printStackPointer(void);
void printAllRegs(void);
void printProgramCounter(void);
int dumpRAM(struct Computer *OurComputer, address start, address end);


#endif // SIX_FIVE_2_H