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

void printAccumulator(void) { printf("RegA: 0x%x\n", getAccumulator()); };
void printRegisterX(void) { printf("RegX: 0x%x\n", getRegisterX()); };
void printRegisterY(void) { printf("RegY: 0x%x\n", getRegisterY()); };
void printHexStatusRegister(void) { printf("RegSF: 0x%x\n", getStatusRegister()); };
void printBinaryStatusRegister(void) { printf("RegSR: 0b%s\n", toBinary(getStatusRegister(), 8)); };
void printStackPointer(void) { printf("RegSP: 0x%x\n", getStackPointer()); };
void printProgramCounter(void) { printf("RegPC: 0x%x\n", getProgramCounter()); };

void printAllRegs(void) { 
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