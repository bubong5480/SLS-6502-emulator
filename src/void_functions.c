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
#include "./src/uthash.h"

#define byte uint8_t
#define RAMSIZE (1<<16)
#define opcode_size 147

int* fetch();
struct cpu* execute();
void build_opcode_table();
void decode(byte);

typedef void (*myFuncDef)(byte, uint8_t*);

struct cpu{
    uint16_t* pc; 
    uint8_t accumulator; 
    byte register_x; 
    byte register_y; 
    byte status_register;
    byte stack_pointer;
};

struct opcode_table{
    uint8_t opcodes_key;
    myFuncDef opcode_function; 
    UT_hash_handle hh;
};

struct Computer{
    byte* RAM;
    struct cpu* cpu_inst;
    struct opcode_table *circuits;
};

struct Computer* OurComputer;
char** opcode_names;

struct return_{
    byte pc;
    byte arg;
};

struct return_ ret; 


void decode(byte opcode){
  int bitmask; 
    switch(opcode){
      // "special" opcodes 
      case 0: 
        break;

      case 1:
        break; 

      case 2:
        break;

      case 3:
        break;

      case 4:
        break;
        
      // "normal" opcodes
      default:
        bitmask = opcode & 0x000FFF00; 
        switch(bitmask){
          // indirect x 
          case 0: // XXX000XX
            ret.pc = *OurComputer->cpu_inst->pc;
            ret.arg = OurComputer->cpu_inst->register_x; 
            break;
          // zero-page
          case 1: // XXX001XX
            ret.pc = *OurComputer->cpu_inst->pc;
            ret.arg = 0; 
            break;
          
          // immediate 
          case 2: //XXX010XX
            ret.pc = *(OurComputer->cpu_inst->pc + 1);
            ret.arg = 0; 
            break;
          
          //  absolute
          case 3: //XXX011XX , same as zero-page? 
            ret.pc = *OurComputer->cpu_inst->pc;
            ret.arg = 0;
            break;

          // indirect y 
          case 4: //XXX100XX
            ret.pc = *OurComputer->cpu_inst->pc;
            ret.arg = OurComputer->cpu_inst->register_y; 
            break;  
          // zeropage x 
          case 5: //XXX101XX
            ret.pc = *OurComputer->cpu_inst->pc;
            ret.arg = OurComputer->cpu_inst->register_x; 
            break;
            
        // absolute y 
          case 6: //XXX110XX
            ret.pc = *OurComputer->cpu_inst->pc;
            ret.arg = OurComputer->cpu_inst->register_y; 
            break;
          
          // absolute x 
          case 7: //XXX111XX
            ret.pc = *OurComputer->cpu_inst->pc;
            ret.arg = OurComputer->cpu_inst->register_x; 
            break;
        }
        break;
    }
} 

void ADC(byte opcode, uint8_t* pc){
    decode(opcode); 
    OurComputer->cpu_inst->accumulator += ret.pc + ret.arg;
};


void AND(byte opcode, uint8_t* pc){decode(opcode); OurComputer->cpu_inst->accumulator &= ret.pc; };
void ASL(byte opcode, uint8_t* pc){decode(opcode); ret.arg <<= 1};
void BCC(byte opcode, uint8_t* pc){decode(opcode); *ret.pc += *ret.arg};
void BCS(byte opcode, uint8_t* pc){if carry == 1{BCC(opcode, pc)}};
void BEQ(byte opcode, uint8_t* pc){if zero == 1{BCC(opcode, pc)}};
void BIT(byte opcode, uint8_t* pc){if zero == 1{BCC(opcode, pc)}};
void BIT(byte opcode, uint8_t* pc){if N == 1{BCC(opcode, pc)}};
void BME(byte opcode, uint8_t* pc){if zero == 0{BCC(opcode, pc)}};
void BPL(byte opcode, uint8_t* pc){if N==0{BCC(opcode, pc)}};
void BRK(byte opcode, uint8_t* pc){break; };
void BVC(byte opcode, uint8_t* pc){if V==0{BCC(opcode, pc)}};
void BVS(byte opcode, uint8_t* pc){if V==1{BCC(opcode, pc)}};
void CLC(byte opcode, uint8_t* pc){carry = 0};
void CLD(byte opcode, uint8_t* pc){D = 0};
void CLI(byte opcode, uint8_t* pc){I = 0};
void CLV(byte opcode, uint8_t* pc){V = 0};
void CMD(byte opcode, uint8_t* pc){V = 0};
void CPX(byte opcode, uint8_t* pc){if zero == 0{BCC(opcode, pc)}};
void CPY(byte opcode, uint8_t* pc){if zero == 0{BCC(opcode, pc)}};
void DEC(byte opcode, uint8_t* pc){*OurComputer->cpu_inst->pc -= 1};
void DEX(byte opcode, uint8_t* pc){*OurComputer->cpu_inst->pc -= OurComputer->cpu_inst->register_x};
void DEY(byte opcode, uint8_t* pc){*OurComputer->cpu_inst->pc -= OurComputer->cpu_inst->register_y};
void EOR(byte opcode, uint8_t* pc){decode(opcode); OurComputer->accumulator ^= *ret.arg};
void INC(byte opcode, uint8_t* pc){decode(opcode); *ret.pc += 1};
void INX(byte opcode, uint8_t* pc){reg_x += 1};
void INY(byte opcode, uint8_t* pc){reg_y += 1};
void JMP(byte opcode, uint8_t* pc){decode(opcode); ret.pc = ret.arg};
void JSR(byte opcode, uint8_t* pc){decode(opcode); ret.pc = ret.arg};
void LDA(byte opcode, uint8_t* pc){OurComputer->accumulator = *OurComputer->cpu_inst->pc};
void LDX(byte opcode, uint8_t* pc){reg_x = *OurComputer->cpu_inst->pc};
void LDY(byte opcode, uint8_t* pc){reg_y = *OurComputer->cpu_inst->pc};
void LSR(byte opcode, uint8_t* pc){decode(opcode); *ret.arg >>= 1};
void LSR(byte opcode, uint8_t* pc){pc +=1 };
void ORA(byte opcode, uint8_t* pc){OurComputer->cpu_inst->accumulator ^= *OurComputer->cpu_inst->pc};
void PHA(byte opcode, uint8_t* pc){OurComputer->cpu_inst->accumulator ^= *OurComputer->cpu_inst->pc};
void PHP(byte opcode, uint8_t* pc){OurComputer->cpu_inst->accumulator ^= *OurComputer->cpu_inst->pc};
void PLA(byte opcode, uint8_t* pc){OurComputer->cpu_inst->accumulator ^= *OurComputer->cpu_inst->pc};
void PLP(byte opcode, uint8_t* pc){OurComputer->cpu_inst->accumulator ^= *OurComputer->cpu_inst->pc};
void ROL(byte opcode, uint8_t* pc){decode(opcode); rotate *ret.arg by 1 bit left};
void ROR(byte opcode, uint8_t* pc){decode(opcode); rotate *ret.arg by 1 bit right};
void RTI(byte opcode, uint8_t* pc){decode(opcode); rotate *ret.arg by 1 bit right};
void RTS(byte opcode, uint8_t* pc){decode(opcode); rotate *ret.arg by 1 bit right};
void SBC(byte opcode, uint8_t* pc){decode(opcode); OurComputer->cpu_inst->accumulator -= *(ret.pc + ret.arg)};
void SEC(byte opcode, uint8_t* pc){carry = 1};
void SED(byte opcode, uint8_t* pc){D = 1};
void SEI(byte opcode, uint8_t* pc){I = 1};
void STA(byte opcode, uint8_t* pc){*OurComputer->cpu_inst->pc = OurComputer->cpu_inst->accumulator};
void STX(byte opcode, uint8_t* pc){OurComputer->cpu_inst->register_x = *OurComputer->cpu_inst->pc};
void STY(byte opcode, uint8_t* pc){OurComputer->cpu_inst->register_y = *OurComputer->cpu_inst->pc};
void TAX(byte opcode, uint8_t* pc){OurComputer->cpu_inst->register_x = OurComputer->cpu_inst->accumulator};
void TAY(byte opcode, uint8_t* pc){OurComputer->cpu_inst->register_y = OurComputer->cpu_inst->accumulator};
void TSX(byte opcode, uint8_t* pc){OurComputer->cpu_inst->register_x = stack_pointer};
void TXA(byte opcode, uint8_t* pc){OurComputer->cpu_inst->accumulator = OurComputer->cpu_inst->register_x};
void TXS(byte opcode, uint8_t* pc){stack_reg = OurComputer->cpu_inst->register_x};
void TYA(byte opcode, uint8_t* pc){OurComputer->cpu_inst->accumulator = OurComputer->cpu_inst->register_y};