#include "6502.h"

int main(int argc, char* argv[]) {
  // user must pass in binary image to simulate RAM
  if (argc != 2){
    printf("%s outfile", argv[0]);
    return 1;
  }

  char* file_name = argv[1];
  // allocate memory for Computer Structure
  if((OurComputer = (struct Computer*) malloc(sizeof(struct Computer))) == NULL){
    exit(-1);
  }
  // initializing size of the RAM to 2^16
  if ((OurComputer->RAM = (byte*) malloc(RAMSIZE * sizeof(byte))) == NULL){
    exit(-1);
  }
  // initializing cpu structure inside of computer
  if((OurComputer->cpu_inst = (struct cpu*) malloc(sizeof(struct cpu))) == NULL){
    exit(-1);
  }

  // fill struct->RAM with file_name
  read_in_binary_image(file_name);
  build_opcode_table();
  initalize_program_counter();
  // check the first byte (for the time being)

  resetRegisters();
  dumpRAM(OurComputer, 0, 8);

  for (int i = 0; i < RAMSIZE; i++) {
    byte opcode = OurComputer->RAM[getProgramCounter()];
    
    if (opcode == 0x00) {
      printf("%x NOP\n", i);
      (OurComputer->cpu_inst->pc += 1);
    } 
    else {
      if (i == RAMSIZE - 1) {
        printf("%x NOP\n", i);
        (OurComputer->cpu_inst->pc += 1);
      }
      else if (opcode == 0x69) {
        printf("------\n%x opcode: %x\n", i, opcode);
        ADC(opcode, OurComputer->cpu_inst->pc);
        (OurComputer->cpu_inst->pc) += 2;
        printAccumulator(OurComputer);
      }
      else {
        printf("%x NOP\n", i);
        (OurComputer->cpu_inst->pc += 1);
      }
    }
  }

  return 0;
}