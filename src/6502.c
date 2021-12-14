#include "6502.h"

void read_in_binary_image(char* image_name){
  int n, fd;
  if((fd=open(image_name, O_RDONLY)) < 0){
    exit(-1);
  }
  if((n = read(fd, OurComputer->RAM, RAMSIZE)) != RAMSIZE){
    exit(-1);
  }
  close(fd);
};

// Make program counter point to first byte of RAM
void initalize_program_counter() { OurComputer->cpu_inst->pc = 0; };

// Builds opcode table
void build_opcode_table(){
  int n, fd;
  byte* opcodes_keys;
  OurComputer->opcodes = NULL;

  // need to read in the opcodes
  if((opcodes_keys = (byte*) malloc((opcode_size) * sizeof(byte))) == NULL){
    exit(-1);
  }
  if((fd=open("opcode_values", O_RDONLY)) < 0){
    exit(-1);
  }
  if((n = read(fd, opcodes_keys, opcode_size)) != opcode_size){
    exit(-1);
  }
  close(fd);
  if ((opcode_names = (char**)malloc(sizeof(char*)*opcode_size)) == NULL){
    exit(-1);
  }
  for(int i = 0; i < opcode_size; ++i){
    opcode_names[i] = (char*)malloc(sizeof(char)*4);
  }
  if((fd=open("opcode_names.txt", O_RDONLY)) < 0){
    exit(-1);
  }
  for(int i = 0; i < opcode_size; ++i){
    if(read(fd,opcode_names[i],3) != 3){
      exit(-1);
    }
  }
  close(fd);
  
  /* for(int i = 0; i < opcode_size; i++){
    printf("%3s, %x\n", opcode_names[i], opcodes_keys[i]);
   }
  */

  struct opcode_table* s = NULL;
  for (int i = 0; i  < opcode_size; i++){
    s = (struct opcode_table*) malloc(sizeof(*s)); // check if NULL?
    s->opcodes_key = opcodes_keys[i]; // initializing key for s
    s->opcode_function = opcode_names[i]; // initializing the value for s
    HASH_ADD(hh,OurComputer->opcodes, opcodes_key, sizeof(uint8_t),s);
    // Adds s = {opcodes_keys[i] : 1} to the hash table
    // s ~ (key, value), added to opcodes, the hash table.
  }
};

byte getAccumulator() { return OurComputer->cpu_inst->accumulator; };
byte getRegisterX() { return OurComputer->cpu_inst->register_x; };
byte getRegisterY() { return OurComputer->cpu_inst->register_y; };
byte getStatusRegister() { return OurComputer->cpu_inst->status_register; };
byte getStackPointer() { return OurComputer->cpu_inst->stack_pointer; };
address getProgramCounter() { return OurComputer->cpu_inst->pc; };

int reset_registers() {
    OurComputer->cpu_inst->accumulator = 0;
    OurComputer->cpu_inst->register_x = 0;
    OurComputer->cpu_inst->register_y = 0;
    OurComputer->cpu_inst->status_register = 0;
    OurComputer->cpu_inst->stack_pointer = 0;
    
    return 0;
};