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
  if ((OurComputer->RAM = (byte*) malloc((1 << 16) * sizeof(byte))) == NULL){
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
  if (*(OurComputer->cpu_inst->pc) != 0xEA){
    printf("Success\n");
  }
  
  OurComputer->cpu_inst->accumulator=0x00;
  OurComputer->cpu_inst->register_x=0x00;
  OurComputer->cpu_inst->register_y=0x00;
  OurComputer->cpu_inst->status_register=0x00;
  OurComputer->cpu_inst->stack_pointer=0x00;
  getAllRegs(OurComputer);


  return 0;
}