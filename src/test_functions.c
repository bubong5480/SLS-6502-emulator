#include "6502.h"

char* toBinary(int n, int len)
{
    char* binary = (char*)malloc(sizeof(char) * len);
    int k = 0;
    for (unsigned i = (1 << len - 1); i > 0; i = i / 2) {
        binary[k++] = (n & i) ? '1' : '0';
    }
    binary[k] = '\0';
    return binary;
}

void printAccumulator(struct Computer* OurComputer) 
    { printf("RegA: 0x%x\n", OurComputer->cpu_inst->accumulator); };

void printRegisterX(struct Computer* OurComputer) 
    { printf("RegX: 0x%x\n", OurComputer->cpu_inst->register_x); };

void printRegisterY(struct Computer* OurComputer) 
    { printf("RegY: 0x%x\n", OurComputer->cpu_inst->register_y); };

void printHexStatusRegister(struct Computer* OurComputer) 
    { printf("RegSF: 0x%x\n", OurComputer->cpu_inst->status_register); };

void printBinaryStatusRegister(struct Computer* OurComputer) 
    { printf("RegSR: 0x%s\n", toBinary(OurComputer->cpu_inst->status_register, 8)); };

void printStackPointer(struct Computer* OurComputer) 
    { printf("RegSP: 0x%x\n", OurComputer->cpu_inst->stack_pointer); };

void printProgramCounter(struct Computer* OurComputer)
    { printf("RegPC: 0x%p\n", OurComputer->cpu_inst->pc); };

void printAllRegs(struct Computer* OurComputer)
    { 
        printAccumulator(OurComputer);
        printRegisterX(OurComputer);
        printRegisterY(OurComputer);
        printBinaryStatusRegister(OurComputer);
        printStackPointer(OurComputer);
        printProgramCounter(OurComputer);
    };

int dumpRAM(struct Computer *OurComputer, address start, address end) 
{
        address i;

        for (i = start; i < end; i ++) {
            if ( (i % 16 == 0 && (i != start)) )
                printf("\n");
                printf("%02x ", OurComputer->RAM[i]);
        }
        printf("\n");

        return (i - start);
};

int dumpRAMPTR(struct Computer *OurComputer, address start, address end) 
{
        address i;

        for (i = start; i < end; i ++) {
            if ( (i % 16 == 0 && (i != start)) )
                printf("\n");
                printf("%02x ", *(OurComputer->cpu_inst->pc+i));
        }
        printf("\n");

        return (i - start);
};