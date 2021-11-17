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
int* decode();
struct cpu* execute();
void build_opcode_table();

struct cpu{
  uint8_t* pc;
  uint16_t accumulator;
};

struct opcode_table{
  uint8_t opcodes_key;
  char* opcode_name;
  UT_hash_handle hh;
};

struct Computer{
  byte* RAM;
  struct cpu* cpu_inst;
  struct opcode_table *opcodes;
};

struct Computer* OurComputer;
char** opcode_names;

void read_in_binary_image(char* image_name){
  int n, fd;
  if((fd=open(image_name, O_RDONLY)) < 0){
    exit(-1);
  }
  if((n = read(fd, OurComputer->RAM, RAMSIZE)) != RAMSIZE){
    exit(-1);
  }
  close(fd);
}


// Make program counter point to first byte of RAM
void initalize_program_counter(){
  OurComputer->cpu_inst->pc = OurComputer->RAM;
}

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
  for(int i = 0; i < opcode_size; i++){
    printf("%3s, %x\n", opcode_names[i], opcodes_keys[i]);
  }

  struct opcode_table* s = NULL;
  for (int i = 0; i  < opcode_size; i++){
    s = (struct opcode_table*) malloc(sizeof(*s)); // check if NULL?
    s->opcodes_key = opcodes_keys[i]; // initializing key for s
    s->opcode_name = opcode_names[i]; // initializing the value for s
    HASH_ADD(hh,OurComputer->opcodes, opcodes_key, sizeof(uint8_t),s);
    // Adds s = {opcodes_keys[i] : 1} to the hash table
    // s ~ (key, value), added to opcodes, the hash table.
  }

}

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

  return 0;
}
