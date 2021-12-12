#include "6502.h"

void getAccumulator(struct Computer* OurComputer) 
    { printf("RegA: 0x%x\n", OurComputer->cpu_inst->accumulator); };

void getRegisterX(struct Computer* OurComputer) 
    { printf("RegX: 0x%x\n", OurComputer->cpu_inst->register_x); };

void getRegisterY(struct Computer* OurComputer) 
    { printf("RegY: 0x%x\n", OurComputer->cpu_inst->register_y); };

void getStatusRegister(struct Computer* OurComputer) 
    { printf("RegSF: 0x%x\n", OurComputer->cpu_inst->status_register); };

void getStackPointer(struct Computer* OurComputer) 
    { printf("RegSP: 0x%x\n", OurComputer->cpu_inst->stack_pointer); };

void getProgramCounter(struct Computer* OurComputer)
    { printf("RegPC: 0x%p\n", OurComputer->cpu_inst->pc); };

void getAllRegs(struct Computer* OurComputer)
    { 
        getAccumulator(OurComputer);
        getRegisterX(OurComputer);
        getRegisterY(OurComputer);
        getStatusRegister(OurComputer);
        getStackPointer(OurComputer);
        getProgramCounter(OurComputer);
    };