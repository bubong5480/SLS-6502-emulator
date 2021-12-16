#include "6502.h"

typedef void (*opcode_function)(byte, address); 
opcode_function functions[] = {&ADC ,&ADC ,&ADC ,&ADC ,&ADC ,&ADC ,&ADC ,&ADC ,&AND ,&AND ,&AND ,&AND ,&AND ,&AND ,&AND ,&AND ,&ASL ,&ASL ,&ASL ,&ASL ,&BCC ,&BCS ,&BEQ ,&BIT ,&BIT ,&BMI ,&BNE ,&BPL ,&BVC ,&BVS ,&CMP ,&CMP ,&CMP ,&CMP ,&CMP ,&CMP ,&CMP ,&CMP ,&CPX ,&CPX ,&CPX ,&CPY ,&CPY ,&CPY ,&DEC ,&DEC ,&DEC ,&DEC ,&EOR ,&EOR ,&EOR ,&EOR ,&EOR ,&EOR ,&EOR ,&EOR ,&INC ,&INC ,&INC ,&INC ,&JMP ,&JMP ,&JSR ,&LDA ,&LDA ,&LDA ,&LDA ,&LDA ,&LDA ,&LDA ,&LDA ,&LDX ,&LDX ,&LDX ,&LDX ,&LDX ,&LDY ,&LDY ,&LDY ,&LDY ,&LDY ,&LSR ,&LSR ,&LSR ,&LSR ,&ORA ,&ORA ,&ORA ,&ORA ,&ORA ,&ORA ,&ORA ,&ORA ,&ROL ,&ROL ,&ROL ,&ROL ,&ROR ,&ROR ,&ROR ,&ROR ,&SBC ,&SBC ,&SBC ,&SBC ,&SBC ,&SBC ,&SBC ,&SBC ,&STA ,&STA ,&STA ,&STA ,&STA ,&STA ,&STA ,&STX ,&STX ,&STX ,&STY ,&STY ,&STY ,&BRK ,&CLC ,&CLD ,&CLI ,&CLV ,&DEX ,&DEY ,&INX ,&INY ,&NOP ,&PHA ,&PHP ,&PLA ,&PLP ,&RTI ,&RTS ,&SEC ,&SED ,&SEI ,&TAX ,&TAY ,&TSX ,&TXA ,&TXS ,&TYA};

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

  struct opcode_table* s = NULL;
  for (int i = 0; i  < opcode_size; i++){
    s = (struct opcode_table*) malloc(sizeof(*s)); // check if NULL?
    s->opcodes_key = opcodes_keys[i]; // initializing key for s
    s->opcode_function = functions[i]; // initializing the value for s
    HASH_ADD(hh,OurComputer->opcodes, opcodes_key, sizeof(uint8_t),s);
  }
}


void find_user(byte opcode, address pc) {

  struct opcode_table *s;
  HASH_FIND_BYTE(OurComputer->opcodes, &opcode, s);

  if(s == NULL){
    printf("err"); 
    return; 
  }
 
  (*s->opcode_function) (opcode, pc);

  return; 

}

byte fetch(void) {
  return OurComputer->RAM[getProgramCounter()];
}

byte getAccumulator(void) { return OurComputer->cpu_inst->accumulator; };
byte getRegisterX(void) { return OurComputer->cpu_inst->register_x; };
byte getRegisterY(void) { return OurComputer->cpu_inst->register_y; };
byte getStatusRegister(void) { return OurComputer->cpu_inst->status_register; };
byte getStackPointer(void) { return OurComputer->cpu_inst->stack_pointer; };
address getProgramCounter(void) { return OurComputer->cpu_inst->pc; };

int reset_registers(void) {
    OurComputer->cpu_inst->accumulator = 0;
    OurComputer->cpu_inst->register_x = 0;
    OurComputer->cpu_inst->register_y = 0;
    OurComputer->cpu_inst->status_register = 0;
    OurComputer->cpu_inst->stack_pointer = 0;
    return 0;
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
  reset_registers();
  
  dumpRAM(OurComputer, 0, 32);
  for (int i = 0; i < 2; i ++ ) {
  printf("--------\nOpcode: %x\n", fetch());
  OurComputer->cpu_inst->register_x = 0x2;
  find_user(fetch(), getProgramCounter());
  
  }
  printAccumulator();

  return 0;
}