#include "6502.h"

void setNegativeFlag() { OurComputer->cpu_inst->status_register = getStackPointer() | 0b1 << 7; }
void clearNegativeFlag() { OurComputer->cpu_inst->status_register = getStackPointer()  & 0b0 << 7; }

void setOverflowFlag() { OurComputer->cpu_inst->status_register = getStackPointer() | 0b1 << 6; }
void clearOverflowFlag() { OurComputer->cpu_inst->status_register = getStackPointer()  & 0b0 << 6; }

void setBreakFlag() { OurComputer->cpu_inst->status_register = getStackPointer() | 0b1 << 4; }
void clearBreakFlag() { OurComputer->cpu_inst->status_register = getStackPointer()  & 0b0 << 4; }

void setDecimalFlag() { OurComputer->cpu_inst->status_register = getStackPointer() | 0b1 << 3; }
void clearDecimalFlag() { OurComputer->cpu_inst->status_register = getStackPointer()  & 0b0 << 3; }

void setInterruptFlag() { OurComputer->cpu_inst->status_register = getStackPointer() | 0b1 << 2; }
void clearInterruptFlag() { OurComputer->cpu_inst->status_register = getStackPointer()  & 0b0 << 2; }

void setZeroFlag() { OurComputer->cpu_inst->status_register = getStackPointer() | 0b1 << 1; }
void clearZeroFlag() { OurComputer->cpu_inst->status_register = getStackPointer()  & 0b0 << 1; }

void setCarryFlag() { OurComputer->cpu_inst->status_register = getStackPointer() | 0b1; }
void clearCarryFlag() { OurComputer->cpu_inst->status_register = getStackPointer()  & 0b0; }

/*
void decode(byte opcode) {
  
  int a_mask, b_mask, c_mask; 
  
  a_mask = opcode & 0xFFF00000;
  b_mask = opcode & 0x000FFF00; 
  c_mask = opcode & 0x000000FF;

  if(c_mask == 0){
    switch(b_mask){
      // immediate 
      case 0: //XXX010XX
        ret.pc = *(OurComputer->cpu_inst->pc + 1);
        ret.arg = 0;
        break;
      // zero-page
      case 1: // XXX001XX
        ret.pc = *OurComputer->cpu_inst->pc;
        ret.arg = 0; 
        break;
      //  absolute
      case 3: //XXX011XX 
        // do jump checks with a_mask (indirect jump)
        if (a_mask == 3){
          // abs indexed indirect
          // add X to lower bits of address we pass 
        }
        ret.pc = *OurComputer->cpu_inst->pc;
        ret.arg = 0;
        break; 
      // zeropage x 
      case 5: //XXX101XX
        ret.pc= *(address*)((uintptr_t) (OurComputer->cpu_inst->pc + OurComputer->cpu_inst->register_x) % (uintptr_t)(OurComputer->cpu_inst->pc[256]));
        ret.arg = 0;
        break;
      // absolute x 
      case 7: //XXX111XX
        ret.pc = *(OurComputer->cpu_inst->pc + OurComputer->cpu_inst->register_x);
        ret.arg = 0; 
        break;
    }
  }
  else if (c_mask == 1){
    switch(b_mask){
      // indirect X
      case 0: // XXX000XX
        ret.pc = *(address*)(OurComputer->cpu_inst->pc + OurComputer->cpu_inst->register_x);
        ret.arg = 0; 
        break;
      // zero-page
      case 1: // XXX001XX
        ret.pc = *OurComputer->cpu_inst->pc;
        ret.arg = 0; 
        break;
      // immediate
      case 2: 
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
        ret.pc = * (address*)(uintptr_t)(*(OurComputer->cpu_inst->pc) + OurComputer->cpu_inst->register_y);
        ret.arg = 0; 
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
  }
  else if (c_mask == 2){
    switch(b_mask){
      case 0: //XXX010XX
        ret.pc = *(OurComputer->cpu_inst->pc + 1);
        ret.arg = 0; 
        break;
      // zero page
      case 1: // XXX001XX
        ret.pc = *OurComputer->cpu_inst->pc;
        ret.arg = 0; 
        break;
      // case 2: accumulator 
      //  absolute
      case 3: //XXX011XX , same as zero-page? 
        ret.pc = *OurComputer->cpu_inst->pc;
        ret.arg = 0;
        break;
      // absolute x 
      case 5: //XXX111XX
        ret.pc = *OurComputer->cpu_inst->pc;
        ret.arg = OurComputer->cpu_inst->register_x; 
        break;
      // absolute y 
      case 7: //XXX110XX
        ret.pc = *OurComputer->cpu_inst->pc;
        ret.arg = OurComputer->cpu_inst->register_y; 
        break;
    }
  }
  // special cases
  else{
  //  implied
  //  indirect 
  //  indirect x 
  //  indirect y 
  //  relative 
  }

    // switch(opcode){
    //   // "special" opcodes 
    //   case 0: 
    //   //accumulator
    //   //OPC A 
    //   //implied single byte instruction
    //     break;

    //   case 1:
    //   //zeropage y 
    //   //OPC $LL,Y
    //   //operand is zeropage address, EA is incremented by Y w/o carry
    //     break; 

    //   case 2:
    //   //relative
    //   //OPC $BB
    //   //branch target is PC + offset BB 
    //   //branch offsets (like BB) are signed 8-bit ints 
    //     break;

    //   case 3:
    //   //implied 
    //   //OPC 
    //   //operand implied, prob included inside command itself
    //     break;

    //   case 4:
    //   //indirect 
    //   //OPC $LLHH
    //   //operand is address, EA is contents of word at address: C.w ($HHLL)
    //   // idk what C.w means 
    //     break;
        
    //   // "normal" opcodes
    //   default:
        
    //     switch(bitmask){
    //       // indirect x 
    //       case 0: // XXX000XX
    //         ret.pc = *OurComputer->cpu_inst->pc;
    //         ret.arg = OurComputer->cpu_inst->register_x; 
    //         break;
    //       // zero-page
    //       case 1: // XXX001XX
    //         ret.pc = *OurComputer->cpu_inst->pc;
    //         ret.arg = 0; 
    //         break;
          
    //       // immediate 
    //       case 2: //XXX010XX
    //         ret.pc = *(OurComputer->cpu_inst->pc + 1);
    //         ret.arg = 0; 
    //         break;
          
    //       //  absolute
    //       case 3: //XXX011XX , same as zero-page? 
    //         ret.pc = *OurComputer->cpu_inst->pc;
    //         ret.arg = 0;
    //         break;

    //       // indirect y 
    //       case 4: //XXX100XX
    //         ret.pc = *OurComputer->cpu_inst->pc;
    //         ret.arg = OurComputer->cpu_inst->register_y; 
    //         break;  
    //       // zeropage x 
    //       case 5: //XXX101XX
    //         ret.pc = *OurComputer->cpu_inst->pc;
    //         ret.arg = OurComputer->cpu_inst->register_x; 
    //         break;
            
    //     // absolute y 
    //       case 6: //XXX110XX
    //         ret.pc = *OurComputer->cpu_inst->pc;
    //         ret.arg = OurComputer->cpu_inst->register_y; 
    //         break;
          
    //       // absolute x 
    //       case 7: //XXX111XX
    //         ret.pc = *OurComputer->cpu_inst->pc;
    //         ret.arg = OurComputer->cpu_inst->register_x; 
    //         break;
    //     }
    //     break;
    //}
} 
*/
void ADC(byte opcode, address pc) {
  // decode(opcode);
  OurComputer->cpu_inst->accumulator += ret.arg;

    // update PC 
};

void AND(byte opcode, address pc) {
  // decode(opcode); 
  OurComputer->cpu_inst->accumulator &= ret.arg; 

  // update PC 
};

/*
// ASL uses either an address or Accumulator
// needs decode done

void ASL(byte opcode, address pc) {
  // decode(opcode); 
  ret.arg <<= 1;
};

// BCC - branch on Carry Flag = 0
void BCC(byte opcode, address pc) {
  // decode(opcode); 
  *ret.pc += *ret.arg
};

// BSC - branch on Carry Flag = 1
void BCS(byte opcode, byte* pc) {if carry == 1{BCC(opcode, pc)}};

// BEQ - branch on Zero Flag = 1
void BEQ(byte opcode, byte* pc) {if zero == 1{BCC(opcode, pc)}};

// BIT - bits 7 and 6 of operand are transfered to bit 7 and 6 of SR (N,V);
// the zero-flag is set to the result of operand AND accumulator.

void BIT(byte opcode, byte* pc) {if zero == 1{BCC(opcode, pc)}};

// BMI - branch on Negative Flag = 1
void BMI(byte opcode, byte* pc) {if N == 1{BCC(opcode, pc)}};

// BNE - branch on Zero Flag = 1
void BNE(byte opcode, byte* pc) {if zero == 0{BCC(opcode, pc)}};

// BPL - branch on Negative Flag = 0
void BPL(byte opcode, byte* pc) {if N==0{BCC(opcode, pc)}};

// BRK - break
void BRK(byte opcode, byte* pc) {
  // set flags
}

// BVC - branch on Overflow = 0
void BVC(byte opcode, byte* pc) {if V==0{BCC(opcode, pc)}};

// BVS - branch on Overlflow = 1
void BVS(byte opcode, byte* pc) {if V==1{BCC(opcode, pc)}};
*/

void CLC() {
  clearCarryFlag();
  OurComputer->cpu_inst->pc++;    // update PC
};

void CLD() {
  clearDecimalFlag();
  OurComputer->cpu_inst->pc++;    // update PC
};

void CLI() {
  clearInterruptFlag();
  OurComputer->cpu_inst->pc++;    // update PC
};

void CLV() {
  clearOverflowFlag();
  OurComputer->cpu_inst->pc++;    // update PC
};

void CMP(byte opcode, address pc) {
  // decode(opcode);
  byte a = getAccumulator() - OurComputer->RAM[pc];

  if (a == 0) {
    setZeroFlag();
  } else {
    clearZeroFlag();
  }

  if (a < 0) {
    setNegativeFlag();
  } else {
    clearNegativeFlag();
  }

  // Carry flag set/clear

  // update PC 
};

void CPX(byte opcode, address pc) {
  // decode(opcode);
  byte x = getRegisterX() - OurComputer->RAM[pc];

  if (x == 0) {
    setZeroFlag();
  } else {
    clearZeroFlag();
  }

  if (x < 0) {
    setNegativeFlag();
  } else {
    clearNegativeFlag();
  }

  // Carry flag set/clear

  // update PC 
};
void CPY(byte opcode, address pc) {
  // decode(opcode);
  byte y = getRegisterY() - OurComputer->RAM[pc];

  if (y == 0) {
    setZeroFlag();
  } else {
    clearZeroFlag();
  }

  if (y < 0) {
    setNegativeFlag();
  } else {
    clearNegativeFlag();
  }

  // Carry flag set/clear

  // update PC 
};

void DEC(byte opcode, address pc) {
  OurComputer->RAM[pc] -= 1;

  // update PC 
};

void DEX() {
  OurComputer->cpu_inst->register_x -= 1;
  OurComputer->cpu_inst->pc++;    // update PC
};

void DEY() {
  OurComputer->cpu_inst->register_y -= 1;
  OurComputer->cpu_inst->pc++;    // update PC
};

void EOR(byte opcode, address pc) {
  // decode(opcode);
  OurComputer->cpu_inst->accumulator ^= ret.arg; 

  // update PC 

};

void INC(byte opcode, address pc) {
  OurComputer->RAM[pc] += 1;

  // update PC 
};

void INX() {
  OurComputer->cpu_inst->register_x += 1;
  OurComputer->cpu_inst->pc++;    // update PC
};

void INY() {
  OurComputer->cpu_inst->register_y += 1;
  OurComputer->cpu_inst->pc++;    // update PC
};

/*
void JMP(byte opcode, byte* pc) {
  decode(opcode); 
  *OurComputer->cpu_inst->pc = *ret.pc;
}
void JSR(byte opcode, byte* pc) {
  // jmp (absolute)
}
*/

void LDA(byte opcode, address pc) {
  // decode(opcode);
  OurComputer->cpu_inst->accumulator = OurComputer->RAM[pc];

  // update PC
  };

void LDX(byte opcode, address pc) {
  // decode(opcode);
  OurComputer->cpu_inst->register_x  = OurComputer->RAM[pc];

  // update PC
};

void LDY(byte opcode, address pc) {
  // decode(opcode);
  OurComputer->cpu_inst->register_y  = OurComputer->RAM[pc];

  // update PC
};

/* 
// LSR uses either an address or Accumulator
// needs decode done
// Left Shift
void LSR(byte opcode, byte* pc) {
  // decode(opcode); 
  ret.arg >>= 1};

};
*/

void NOP(byte opcode, address pc) { 
  OurComputer->cpu_inst->pc += 1;   // update PC
};

void ORA(byte opcode, address pc) {
  OurComputer->cpu_inst->accumulator |= OurComputer->RAM[pc];

  // update PC
};

/*
// Stack functions: PH - Push and PL - Pull opcodes 

void PHA(byte opcode, address pc) {
  OurComputer->cpu_inst->accumulator ^= *OurComputer->cpu_inst->pc;
};

void PHP(byte opcode, address pc) {
  OurComputer->cpu_inst->accumulator ^= *OurComputer->cpu_inst->pc;
};

void PLA(byte opcode, address pc) {
  OurComputer->cpu_inst->accumulator ^= *OurComputer->cpu_inst->pc;
};

void PLP(byte opcode, address pc) {
  OurComputer->cpu_inst->accumulator ^= *OurComputer->cpu_inst->pc
};
*/

/*
void ROL(byte opcode, byte* pc) {decode(opcode); rotate *ret.arg by 1 bit left};
void ROR(byte opcode, byte* pc) {decode(opcode); rotate *ret.arg by 1 bit right};

// Return from Interrupt
void RTI(byte opcode, byte* pc) {
  // flag shit
  rotate *ret.arg by 1 bit right
}

// Return from Subroutine
void RTS(byte opcode, byte* pc) {
  // flag shit
  rotate *ret.arg by 1 bit right
}
*/

// Subtract Memory from Accumulator with Borrow
void SBC(byte opcode, address pc) {
  // decode(opcode); 
  OurComputer->cpu_inst->accumulator -= ret.arg;

  // update PC 
};

void SEC() {
  setCarryFlag();

  OurComputer->cpu_inst->pc++;    // update PC
};

void SED() {
  clearDecimalFlag();
  
  
  OurComputer->cpu_inst->pc++;    // update PC
};

void SEI() {
  clearInterruptFlag();

  // update PC
  OurComputer->cpu_inst->pc++;
};

void STA(byte opcode, address pc) {
  // decode(opcode);
  OurComputer->RAM[pc] = getAccumulator();

  // update PC
};

void STX(byte opcode, address pc) {
  // decode(opcode);
  OurComputer->RAM[pc] = getRegisterX();

  // update PC
};

void STY(byte opcode, address pc) {
  // decode(opcode);
  OurComputer->RAM[pc] = getRegisterY();

  // update PC
};

void TAX() {
  OurComputer->cpu_inst->register_x = getAccumulator();

  OurComputer->cpu_inst->pc++;    // update PC
};

void TAY() {
  OurComputer->cpu_inst->register_y = getAccumulator();

  OurComputer->cpu_inst->pc++;    // update PC
};

void TSX() {
  OurComputer->cpu_inst->register_x = getStackPointer();

  OurComputer->cpu_inst->pc++;    // update PC
};

void TXA() {
  OurComputer->cpu_inst->accumulator = getRegisterX();

  OurComputer->cpu_inst->pc++;    // update PC
};

void TXS() {
  OurComputer->cpu_inst->stack_pointer = getRegisterX();

  OurComputer->cpu_inst->pc++;    // update PC
};

void TYA() {
  OurComputer->cpu_inst->accumulator = getRegisterY();

  OurComputer->cpu_inst->pc++;    // update PC
}














/*
aaa bbb cc

  cc = 01 
  bbb
    000   indirect x  
    001   zero page 
    010   immediate     
    011   absolute 
    100   indirect y 
    101   zeropage X 
    110   absolute Y    
    111   absolute X

  cc = 10 
  bbb 
    000   immediate 
    001   zero page 
    010   accumulator    
    011   absolute 
    101   zeropage X
    111   absolute X  

  cc = 00 
  bbb
    000   immediate 
    001   zero page 
    011   absolute       
    101   zeropage X
    111   absolute X     
 
 implied     funcs with implied dont need to call decode 
 relative    BRANCH funcs, will be hard coded 

010 011 00  doesnt add X  (absolute indirect) 
011 011 00  adds X   (absolute indexed indirect)

001 100 00
 cc = 11 
 ^ doesnt exist

*/