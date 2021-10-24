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

#define byte uint8_t
#define RAMSIZE (1<<16)


int* fetch();
int* decode();
struct cpu* execute();

struct cpu{
    uint8_t* pc; 
    uint16_t accumulator; 
};

struct Computer{
    byte* RAM;
    struct cpu* cpu_inst;
}

struct Computer* OurComputer;

void read_in_binary_image(char* image_name){

    int fd=open(image_name, O_RDONLY);
    if (fd < 0) {
      fprintf(stderr, "ERROR: Open failed!\n");
      exit(-1);
    }

    int n = read(fd, OurComputer->RAM, RAMSIZE);
    if (n != RAMSIZE) {
      fprintf(stderr, "ERROR: Bad ramfile: %s n=%d\n", ramfile, n);
      exit(-1);
    }
    close(fd);
}

// Make program counter point to first byte of RAM 
void initalize_program_counter(){
    OurComputer->cpu_inst->pc = OurComputer->RAM;
}

int main(int argc, char* argv[]) {

    // user must pass in binary image to simulate RAM 
    if (argc != 2){
        printf("%s outfile", argv[0]);
        return 1;
    }

    char* file_name = argv[1];

    if (argc == 2){
    // allocate memory for Computer Structure
    if ((OurComputer = (struct Computer*) malloc(sizeof((struct Computer)))) == NULL){
        return NULL; 
    }
    // initializing size of the RAM to 2^16
    if ((OurComputer->RAM = (byte*) malloc((1 << 16) * sizeof(byte))) == NULL){
        return NULL; 
    }
    // initializing cpu structure inside of computer
    if((OurComputer->cpu_inst = (struct cpu*) malloc(sizeof(struct cpu))) == NULL){
        return NULL; 
    }    

    // fill struct->RAM with file_name 
    read_in_binary_image(file_name);

    initalize_program_counter();

    if (*(OurComputer->cpu_inst->pc) == 0x00 ){
        print('Sucess');
    }

    return 0; 
}


/*

compartmentalizing fetch and decode

int* fetch(struct cpu* cpu_inst) {

    return *(cpu_inst->pc);
}

void* decode(){
    case 0xA9:
        char input = *(cpu_inst->pc) + 1; 
        void* output = (*cpu_inst).accumulator

        execute(input, output, 0xA9)
}


*/

/*
int* fetch(struct cpu* cpu_inst) {
    switch(*(cpu_inst->pc)){

        // LDA opcodes
        case 0xA9: // immediate
            *(cpu_inst->pc) += 1; // pass in incremented value or actually increment pc? 
            (*cpu_inst).accumulator = *(cpu_inst->pc); // 
            break;
        case 0xA5:

            break;
        case 0xB5:
            break;
        case 0xAD: // absolute 
            *(cpu_inst->pc) += 1;
            char byte_1 = *(cpu_inst->pc + 1);
            char byte_2 = *(cpu_inst->pc + 2);
            // two bytes to little endian , store the value of the memory address there into the accumulator 
            int16_t mem_address = (byte_1 << 8) | byte_2;  // concatinating the two byte_values 
            
            *(cpu_inst->pc) += mem_address;
            (*cpu_inst).accumulator = *(cpu_inst->pc); // setting accumulutor to value at that mem location
            *(cpu_inst->pc) += 1;
            break;
        case 0xBD:
            break;
        case 0xB9:
            break;
        case 0xA1:
            break;
        case 0xB1:
            break;

        case 0xEA:
            *(cpu_inst->pc) += 1;
            break; 
        default: 
            printf('\n');
            break;
            
    }
    
    *(cpu_inst->pc) += 1
    return 0; 
} 

*/