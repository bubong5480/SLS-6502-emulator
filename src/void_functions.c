#include "6502.h"

void setNegativeFlag(void) { OurComputer->cpu_inst->status_register = getStackPointer() | 0b1 << 7; }
void clearNegativeFlag(void) { OurComputer->cpu_inst->status_register = getStackPointer()  & 0b0 << 7; }

void setOverflowFlag(void) { OurComputer->cpu_inst->status_register = getStackPointer() | 0b1 << 6; }
void clearOverflowFlag(void) { OurComputer->cpu_inst->status_register = getStackPointer()  & 0b0 << 6; }

void setBreakFlag(void) { OurComputer->cpu_inst->status_register = getStackPointer() | 0b1 << 4; }
void clearBreakFlag(void) { OurComputer->cpu_inst->status_register = getStackPointer()  & 0b0 << 4; }

void setDecimalFlag(void) { OurComputer->cpu_inst->status_register = getStackPointer() | 0b1 << 3; }
void clearDecimalFlag(void) { OurComputer->cpu_inst->status_register = getStackPointer()  & 0b0 << 3; }

void setInterruptFlag(void) { OurComputer->cpu_inst->status_register = getStackPointer() | 0b1 << 2; }
void clearInterruptFlag(void) { OurComputer->cpu_inst->status_register = getStackPointer()  & 0b0 << 2; }

void setZeroFlag(void) { OurComputer->cpu_inst->status_register = getStackPointer() | 0b1 << 1; }
void clearZeroFlag(void) { OurComputer->cpu_inst->status_register = getStackPointer()  & 0b0 << 1; }

void setCarryFlag(void) { OurComputer->cpu_inst->status_register = getStackPointer() | 0b1; }
void clearCarryFlag(void) { OurComputer->cpu_inst->status_register = getStackPointer()  & 0b0; }

void decode(byte opcode) {
  int a_mask, b_mask, c_mask; 
  
  a_mask = (opcode & 0b11100000) >> 5;
  b_mask = (opcode & 0b00011100) >> 2; 
  c_mask = opcode & 0b00000011;

  if (c_mask == 0b00) {
    switch(b_mask) {
      // immedate 
      case 0:
        ret.arg = OurComputer->RAM[getProgramCounter() + 1];
        ret.pc = getProgramCounter() + 2;
        break;
      // zeropage 
      case 1: 
        ret.pc = OurComputer->RAM[getProgramCounter() + 1];
        ret.arg = OurComputer->RAM[ret.pc];
        ret.pc = getProgramCounter() + 2;
        break;
      // absolute
      case 3: 
        ret.pc = OurComputer->RAM[getProgramCounter() + 1] << 8 
          | OurComputer->RAM[getProgramCounter() + 2];
        ret.arg = OurComputer->RAM[ret.pc];
        ret.pc = getProgramCounter() + 3;
        break;
      // zeropage, x
      case 5:
        ret.pc = OurComputer->RAM[getProgramCounter() + 1];
        ret.pc += getRegisterX();
        ret.arg = OurComputer->RAM[ret.pc];
        ret.pc = getProgramCounter() + 2;
        break;
      // absolute, x
      case 7:
        ret.pc = OurComputer->RAM[getProgramCounter() + 1] << 8 
          | OurComputer->RAM[getProgramCounter() + 2];
        ret.pc += getRegisterX();
        ret.arg = OurComputer->RAM[ret.pc];
        ret.pc = getProgramCounter() + 3;
        break;

      default:
        break;
    }
  }
  else if (c_mask == 0b01) {
    switch(b_mask) {
      // (zeropage, x)
      case 0:
        ret.pc = OurComputer->RAM[getProgramCounter() + 1];
        ret.pc += getRegisterX();
        ret.pc = OurComputer->RAM[ret.pc];
        ret.arg = OurComputer->RAM[ret.pc];
        ret.pc = getProgramCounter() + 2;
        break;
      // zeropage
      case 1:
        ret.pc = OurComputer->RAM[getProgramCounter() + 1];
        ret.arg = OurComputer->RAM[ret.pc];
        ret.pc = getProgramCounter() + 2;
        break;
      // immediate
      case 2: 
        ret.arg = OurComputer->RAM[getProgramCounter() + 1];
        ret.pc = getProgramCounter() + 2;
        break;
      // absolute
      case 3: 
        ret.pc = OurComputer->RAM[getProgramCounter() + 1] << 8 
          | OurComputer->RAM[getProgramCounter() + 2];
        ret.arg = OurComputer->RAM[ret.pc];
        ret.pc = getProgramCounter() + 3;
        break;
      // (zeropage), y
      case 4:
        ret.pc = OurComputer->RAM[getProgramCounter() + 1];
        ret.pc = OurComputer->RAM[ret.pc] + getRegisterY();
        ret.arg = OurComputer->RAM[ret.pc];
        ret.pc = getProgramCounter() + 2;
        break;
      // zeropage, x
      case 5:
        ret.pc = OurComputer->RAM[getProgramCounter() + 1];
        ret.pc += getRegisterX();
        ret.arg = OurComputer->RAM[ret.pc];
        ret.pc = getProgramCounter() + 2;
        break;
      // absolute, y
      case 6:
        ret.pc = OurComputer->RAM[getProgramCounter() + 1] << 8 
          | OurComputer->RAM[getProgramCounter() + 2];
        ret.pc += getRegisterY();
        ret.arg = OurComputer->RAM[ret.pc];
        ret.pc = getProgramCounter() + 3;
        break;
      // absolute, x
      case 7:
        ret.pc = OurComputer->RAM[getProgramCounter() + 1] << 8 
          | OurComputer->RAM[getProgramCounter() + 2];
        ret.pc += getRegisterX();
        ret.arg = OurComputer->RAM[ret.pc];
        ret.pc = getProgramCounter() + 3;
        break;

      default:
        break;
    }
  }
  else if (c_mask == 0b10) {
    switch(b_mask) {
      // immedate 
      case 0:
        ret.arg = OurComputer->RAM[getProgramCounter() + 1];
        ret.pc = getProgramCounter() + 2;
        break;
      // zeropage 
      case 1: 
        ret.pc = OurComputer->RAM[getProgramCounter() + 1];
        ret.arg = OurComputer->RAM[ret.pc];
        ret.pc = getProgramCounter() + 2;
        break;
      // accumulator
      case 3: 
        ret.arg = getAccumulator();
        ret.pc = getProgramCounter() + 1;
        break;
      // zeropage, x
      case 5:
        ret.pc = OurComputer->RAM[getProgramCounter() + 1];
        ret.pc += getRegisterX();      // add a conditional for STX/LDX
        ret.arg = OurComputer->RAM[ret.pc];
        ret.pc = getProgramCounter() + 2;
        break;
      // absolute, x
      case 7:
        ret.pc = OurComputer->RAM[getProgramCounter() + 1] << 8 
          | OurComputer->RAM[getProgramCounter() + 2];
        ret.pc += getRegisterX();     // add a conditional for STX/LDX
        ret.arg = OurComputer->RAM[ret.pc];
        ret.pc = getProgramCounter() + 3;
        break;

      default:
        break;
    }
  }
  return;
}

  /*
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
  decode(opcode);
  printf("A + M =  %x + %x\n", getAccumulator(), ret.arg);
  OurComputer->cpu_inst->accumulator += ret.arg;
  OurComputer->cpu_inst->pc = ret.pc;  // update PC 
}

void AND(byte opcode, address pc) {
  // decode(opcode); 
  OurComputer->cpu_inst->accumulator &= ret.arg; 
  // update PC 
}

/*******************************************************/
/*    BCC, BCS, BEQ, BMI, BNE, BPL , BVC, BPS   */
/*******************************************************/

// BCC - branch on Carry Flag = 0
void BCC(byte opcode, address pc){
  //decode(opcode); 
  byte a = (0b1) & getStatusRegister(); //on carry flag = 0
  if (a == 0) {
    OurComputer->cpu_inst->pc += ret.pc+1;
  }
  else {
    OurComputer->cpu_inst->pc+=1;
  }
  return;
}

// BSC - branch on Carry Flag = 1
void BCS(byte opcode, address pc){
  //decode(opcode);
  byte carry = (0b1) & getStatusRegister(); //on carry flag = 1
  if (carry == 1) {
    OurComputer->cpu_inst->pc += OurComputer->RAM[pc + 1];
  }
  return; 
}

// BEQ - branch on Zero Flag = 1
void BEQ(byte opcode, address pc) {
  //decode(opcode);
  byte zero = (0b1 << 1) & getStatusRegister();
  if (zero == 1) {
    OurComputer->cpu_inst->pc += ret.arg; 
  }
  return; 
}

void BIT(byte opcode, address pc) {
  int BIT6_mask = 1 << 0b1 << 6;
  int BIT7_mask = 1 << 0b1 << 7;

  if (BIT6_mask & pc) {
    setOverflowFlag(); 
  } else {clearOverflowFlag();}

  if (BIT7_mask & pc) {
    setNegativeFlag();
  } else {clearNegativeFlag();}

  if (OurComputer->cpu_inst->accumulator & pc) {
  clearZeroFlag();
  }
  return; 
}

void CLC(byte opcode, address pc) {
  clearCarryFlag();
  OurComputer->cpu_inst->pc++;    // update PC
  return; 
}

// BMI - branch on Negative Flag = 1
void BMI (byte opcode, address pc) {
  //decode(opcode);
  byte negative = (0b1 << 7) & getStatusRegister();
  if (negative == 1) {
    OurComputer->cpu_inst->pc += ret.arg;
  }
  return; 
}

// BNE - branch on Zero Flag = 0
void BNE (byte opcode, address pc) {
  //decode(opcode);
  byte zero = (0b1 << 1) & getStatusRegister();
  if (zero == 0) {
    OurComputer->cpu_inst->pc += ret.arg;
  }
  return; 
}

// BPL - branch on Negative Flag = 0
void BPL (byte opcode, address pc) {
  //decode(opcode);
  byte negative = (0b1 << 7) & getStatusRegister();
  if (negative == 0) {
    OurComputer->cpu_inst->pc += OurComputer->RAM[pc + 1]; 
  }
  return; 
}

//BVC - branch on Overflow = 0
void BVC (byte opcode, address pc) {
  //decode(opcode);
  byte overflow = (0b1 << 6) & getStatusRegister();
  if (overflow == 0) {
    OurComputer->cpu_inst->pc += ret.arg;
  }
}

// BVS - branch on Overflow = 1
void BVS (byte opcode, address pc) {
  //decode(opcode);
  byte overflow = (0b1 << 6) & getStatusRegister();
  if (overflow == 0) {
    OurComputer->cpu_inst->pc += ret.arg;
  }
}

void CLD(byte opcode, address pc) {
  clearDecimalFlag();
  OurComputer->cpu_inst->pc++;    // update PC
}

void CLI(byte opcode, address pc) {
  clearInterruptFlag();
  OurComputer->cpu_inst->pc++;    // update PC
}

void CLV(byte opcode, address pc) {
  clearOverflowFlag();
  OurComputer->cpu_inst->pc++;    // update PC
}

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
}

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
}

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
}

void DEC(byte opcode, address pc) {
  OurComputer->RAM[pc] -= 1;
  // update PC 
}

void DEX(byte opcode, address pc) {
  OurComputer->cpu_inst->register_x -= 1;
  OurComputer->cpu_inst->pc++;    // update PC
}

void DEY(byte opcode, address pc) {
  OurComputer->cpu_inst->register_y -= 1;
  OurComputer->cpu_inst->pc++;    // update PC
}

void EOR(byte opcode, address pc) {
  // decode(opcode);
  OurComputer->cpu_inst->accumulator ^= ret.arg; 
  // update PC 

}

void INC(byte opcode, address pc) {
  OurComputer->RAM[pc] += 1;
  // update PC 
}

void INX(byte opcode, address pc) {
  OurComputer->cpu_inst->register_x += 1;
  OurComputer->cpu_inst->pc++;    // update PC
}

void INY(byte opcode, address pc) {
  OurComputer->cpu_inst->register_y += 1;
  OurComputer->cpu_inst->pc++;    // update PC
}

void LDA(byte opcode, address pc) {
  // decode(opcode);
  OurComputer->cpu_inst->accumulator = OurComputer->RAM[pc];
  // update PC
  }

void LDX(byte opcode, address pc) {
  // decode(opcode);
  OurComputer->cpu_inst->register_x  = OurComputer->RAM[pc];
  // update PC
}

void LDY(byte opcode, address pc) {
  // decode(opcode);
  OurComputer->cpu_inst->register_y  = OurComputer->RAM[pc];
  // update PC
}

void NOP(byte opcode, address pc) { 
  OurComputer->cpu_inst->pc += 1;   // update PC
}

void ORA(byte opcode, address pc) {
  OurComputer->cpu_inst->accumulator |= OurComputer->RAM[pc];
  // update PC
}

void ROL(byte opcode, address pc) {
  //decode(opcode);
  byte carry = (0b1) & getStatusRegister(); //get the carry flag
  byte bitZero = (0b1 << 7) & ret.arg;  // bit 0 is shifted into carry
  if (bitZero == 1) {
    setCarryFlag();
  } else {(clearCarryFlag());}
  ret.arg = ret.arg << 1; //shift ret.arg over one bit
  ret.arg = carry | ret.arg; //move carry into the 7th bit
};

//void ROR(byte opcode, byte* pc) {decode(opcode); rotate *ret.arg by 1 bit right};
void ROR(byte opcode, address pc) {
  //decode(opcode);
  byte carry = (((0b1) & getStatusRegister()) << 7); //get the carry flag
  byte bitZero = (0b1) & ret.arg;  // bit 0 is shifted into carry
  if (bitZero == 1) {
    setCarryFlag();
  } else {clearCarryFlag();}
  ret.arg = ret.arg >> 1; //shift ret.arg over one bit
  ret.arg = carry | ret.arg; //move carry into the 7th bit
};

// Subtract Memory from Accumulator with Borrow
void SBC(byte opcode, address pc) {
  // decode(opcode); 
  OurComputer->cpu_inst->accumulator -= ret.arg;
  // update PC 
}

void SEC(byte opcode, address pc) {
  setCarryFlag();
  OurComputer->cpu_inst->pc++;    // update PC
}

void SED(byte opcode, address pc) {
  clearDecimalFlag();
  OurComputer->cpu_inst->pc++;    // update PC
}

void SEI(byte opcode, address pc) {
  clearInterruptFlag();
  // update PC
  OurComputer->cpu_inst->pc++;
}

void STA(byte opcode, address pc) {
  // decode(opcode);
  OurComputer->RAM[pc] = getAccumulator();
  // update PC
}

void STX(byte opcode, address pc) {
  // decode(opcode);
  OurComputer->RAM[pc] = getRegisterX();
  // update PC
}

void STY(byte opcode, address pc) {
  // decode(opcode);
  OurComputer->RAM[pc] = getRegisterY();
  // update PC
}

void TAX(byte opcode, address pc) {
  OurComputer->cpu_inst->register_x = getAccumulator();
  OurComputer->cpu_inst->pc++;    // update PC
}

void TAY(byte opcode, address pc) {
  OurComputer->cpu_inst->register_y = getAccumulator();
  OurComputer->cpu_inst->pc++;    // update PC
}

void TSX(byte opcode, address pc) {
  OurComputer->cpu_inst->register_x = getStackPointer();
  OurComputer->cpu_inst->pc++;    // update PC
}

void TXA(byte opcode, address pc) {
  OurComputer->cpu_inst->accumulator = getRegisterX();
  OurComputer->cpu_inst->pc++;    // update PC
}

void TXS(byte opcode, address pc) {
  OurComputer->cpu_inst->stack_pointer = getRegisterX();
  OurComputer->cpu_inst->pc++;    // update PC
}

void TYA(byte opcode, address pc) {
  OurComputer->cpu_inst->accumulator = getRegisterY();
  OurComputer->cpu_inst->pc++;    // update PC
}

// ASL uses either an address or Accumulator
// needs decode done
/*void ASL(byte opcode, address pc) {
  // decode(opcode); 
  ret.arg <<= 1;
};*/
void ASL(byte opcode, address pc) {
  return; 
}

/*
// BRK - break
void BRK(byte opcode, byte* pc) {
  // set flags
}
*/
void BRK(byte opcode, address pc) {
  return; 
}

/*
void JMP(byte opcode, byte* pc) {
  decode(opcode); 
  *OurComputer->cpu_inst->pc = *ret.pc;
}*/
void JMP(byte opcode, address pc) {
  return; 
}

/*
void JSR(byte opcode, byte* pc) {
  // jmp (absolute)
}
*/
void JSR(byte opcode, address pc) {
  return; 
}

/* 
// LSR uses either an address or Accumulator
// needs decode done
// Left Shift
void LSR(byte opcode, byte* pc) {
  // decode(opcode); 
  ret.arg >>= 1};

};
*/
void LSR(byte opcode, address pc) {
  return; 
}

/*
// Stack functions: PH - Push and PL - Pull opcodes 

void PHA(byte opcode, address pc) {
  OurComputer->cpu_inst->accumulator ^= *OurComputer->cpu_inst->pc;
}
*/
void PHA(byte opcode, address pc) {
  return; 
}

/*
void PHP(byte opcode, address pc) {
  OurComputer->cpu_inst->accumulator ^= *OurComputer->cpu_inst->pc;
}
*/
void PHP(byte opcode, address pc) {
  return; 
}

/*
void PLA(byte opcode, address pc) {
  OurComputer->cpu_inst->accumulator ^= *OurComputer->cpu_inst->pc;
}
*/
void PLA(byte opcode, address pc) {
  return; 
}

/*
void PLP(byte opcode, address pc) {
  OurComputer->cpu_inst->accumulator ^= *OurComputer->cpu_inst->pc
}
*/
void PLP(byte opcode, address pc) {
  return; 
}

/*
// Return from Interrupt
void RTI(byte opcode, byte* pc) {
  // flag shit
  rotate *ret.arg by 1 bit right
}
*/
void RTI(byte opcode, address pc) {
  return; 
}

/*
// Return from Subroutine
void RTS(byte opcode, byte* pc) {
  // flag shit
  rotate *ret.arg by 1 bit right
}
*/
void RTS(byte opcode, address pc) {
  return; 
}
