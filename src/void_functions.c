#include "6502.h"

void decode(byte opcode){
  
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

void ADC(byte opcode, byte* pc){
    decode(opcode);
    OurComputer->cpu_inst->accumulator += ret.pc;
};


/*
void AND(byte opcode, byte* pc) {decode(opcode); OurComputer->cpu_inst->accumulator &= ret.pc; };
void ASL(byte opcode, byte* pc) {decode(opcode); ret.arg <<= 1};
void BCC(byte opcode, byte* pc) {
  decode(opcode); *ret.pc += *ret.arg
}

void BCS(byte opcode, byte* pc) {if carry == 1{BCC(opcode, pc)}};
void BEQ(byte opcode, byte* pc) {if zero == 1{BCC(opcode, pc)}};
void BIT(byte opcode, byte* pc) {if zero == 1{BCC(opcode, pc)}};
void BMI(byte opcode, byte* pc) {if N == 1{BCC(opcode, pc)}};
void BNE(byte opcode, byte* pc) {if zero == 0{BCC(opcode, pc)}};
void BPL(byte opcode, byte* pc) {if N==0{BCC(opcode, pc)}};
void BRK(byte opcode, byte* pc) {
  // set flags
}
void BVC(byte opcode, byte* pc) {if V==0{BCC(opcode, pc)}};
void BVS(byte opcode, byte* pc) {if V==1{BCC(opcode, pc)}};
void CLC(byte opcode, byte* pc) {carry = 0};
void CLD(byte opcode, byte* pc) {D = 0};
void CLI(byte opcode, byte* pc) {I = 0};
void CLV(byte opcode, byte* pc) {V = 0};
void CMD(byte opcode, byte* pc) {V = 0};
void CPX(byte opcode, byte* pc) {if zero == 0{BCC(opcode, pc)}};
void CPY(byte opcode, byte* pc) {if zero == 0{BCC(opcode, pc)}};
void DEC(byte opcode, byte* pc) {*OurComputer->cpu_inst->pc -= 1};
void DEX(byte opcode, byte* pc) {*OurComputer->cpu_inst->pc -= OurComputer->cpu_inst->register_x};
void DEY(byte opcode, byte* pc) {*OurComputer->cpu_inst->pc -= OurComputer->cpu_inst->register_y};
void EOR(byte opcode, byte* pc) {decode(opcode); OurComputer->accumulator ^= *ret.arg};
void INC(byte opcode, byte* pc) {decode(opcode); *ret.pc += 1};
void INX(byte opcode, byte* pc) {reg_x += 1};
void INY(byte opcode, byte* pc) {reg_y += 1};
void JMP(byte opcode, byte* pc) {
  decode(opcode); 
  *OurComputer->cpu_inst->pc = *ret.pc;
}
void JSR(byte opcode, byte* pc) {
  // jmp (absolute)
}
void LDA(byte opcode, byte* pc) {OurComputer->accumulator = *OurComputer->cpu_inst->pc};
void LDX(byte opcode, byte* pc) {reg_x = *OurComputer->cpu_inst->pc};
void LDY(byte opcode, byte* pc) {reg_y = *OurComputer->cpu_inst->pc};
void LSR(byte opcode, byte* pc) {decode(opcode); *ret.arg >>= 1};
void LSR(byte opcode, byte* pc) {pc +=1 };
void ORA(byte opcode, byte* pc) {OurComputer->cpu_inst->accumulator ^= *OurComputer->cpu_inst->pc};
void PHA(byte opcode, byte* pc) {OurComputer->cpu_inst->accumulator ^= *OurComputer->cpu_inst->pc};
void PHP(byte opcode, byte* pc) {OurComputer->cpu_inst->accumulator ^= *OurComputer->cpu_inst->pc};
void PLA(byte opcode, byte* pc) {OurComputer->cpu_inst->accumulator ^= *OurComputer->cpu_inst->pc};
void PLP(byte opcode, byte* pc) {OurComputer->cpu_inst->accumulator ^= *OurComputer->cpu_inst->pc};
void ROL(byte opcode, byte* pc) {decode(opcode); rotate *ret.arg by 1 bit left};
void ROR(byte opcode, byte* pc) {decode(opcode); rotate *ret.arg by 1 bit right};
void RTI(byte opcode, byte* pc) {
  // flag shit
  rotate *ret.arg by 1 bit right
}
void RTS(byte opcode, byte* pc) {
  // flag shit
  rotate *ret.arg by 1 bit right
}
void SBC(byte opcode, byte* pc) {decode(opcode); OurComputer->cpu_inst->accumulator -= *(ret.pc + ret.arg)};
void SEC(byte opcode, byte* pc) {carry = 1};
void SED(byte opcode, byte* pc) {D = 1};
void SEI(byte opcode, byte* pc) {I = 1};
void STA(byte opcode, byte* pc) {*OurComputer->cpu_inst->pc = OurComputer->cpu_inst->accumulator};
void STX(byte opcode, byte* pc) {OurComputer->cpu_inst->register_x = *OurComputer->cpu_inst->pc};
void STY(byte opcode, byte* pc) {OurComputer->cpu_inst->register_y = *OurComputer->cpu_inst->pc};
void TAX(byte opcode, byte* pc) {OurComputer->cpu_inst->register_x = OurComputer->cpu_inst->accumulator};
void TAY(byte opcode, byte* pc) {OurComputer->cpu_inst->register_y = OurComputer->cpu_inst->accumulator};
void TSX(byte opcode, byte* pc) {OurComputer->cpu_inst->register_x = stack_pointer};
void TXA(byte opcode, byte* pc) {OurComputer->cpu_inst->accumulator = OurComputer->cpu_inst->register_x};
void TXS(byte opcode, byte* pc) {stack_reg = OurComputer->cpu_inst->register_x};
void TYA(byte opcode, byte* pc) {OurComputer->cpu_inst->accumulator = OurComputer->cpu_inst->register_y};

void NOP(byte opcode, byte* pc) {OurComputer->cpu_inst->pc += 1 };
*/


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