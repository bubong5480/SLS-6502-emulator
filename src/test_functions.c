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

void printAccumulator() { printf("RegA: 0x%x\n", getAccumulator()); };
void printRegisterX() { printf("RegX: 0x%x\n", getRegisterX()); };
void printRegisterY() { printf("RegY: 0x%x\n", getRegisterY()); };
void printHexStatusRegister() { printf("RegSF: 0x%x\n", getStatusRegister()); };
void printBinaryStatusRegister() { printf("RegSR: 0x%s\n", toBinary(getStatusRegister(), 8)); };
void printStackPointer() { printf("RegSP: 0x%x\n", getStackPointer()); };
void printProgramCounter() { printf("RegPC: 0x%x\n", getProgramCounter()); };

void printAllRegs() { 
        printAccumulator();
        printRegisterX();
        printRegisterY();
        printBinaryStatusRegister();
        printStackPointer();
        printProgramCounter();
    };

int dumpRAM(struct Computer *OurComputer, address start, address end) {
        address i;

        for (i = start; i < end; i ++) {
            if ( (i % 16 == 0 && (i != start)) )
                printf("\n");
                printf("%02x ", OurComputer->RAM[i]);
        }
        printf("\n");

        return (i - start);
};