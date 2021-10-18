#include <stdio.h>
#include <stdint.h>
#include <stddef.h>

int* fetch();
int* decode();
struct cpu* execute();

struct cpu{
    int8_t* pc; 
    int8_t accumulator; 
};


struct cpu* cpu_inst;
char *memory;

void read_in_memory_contents(char* mem_arr_pointer){

    // for now, just memset every 
}

int main()
{
    if ((memory = (char*) malloc((1 << 16) * sizeof(char))) == NULL){
        return NULL; 
    }

    if((cpu_inst = (struct cpu*) malloc(sizeof(struct cpu))) == NULL){
        return NULL; 
    }    

    while(1){

    }

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
            char byte_1 = *(cpu_inst->pc);
            *(cpu_inst->pc) += 1;
            char byte_2 = *(cpu_inst->pc);
            // two bytes to little endian , store the value of the memory address there into the accumulator 
            int16_t mem_address = (byte_1 << 8) | byte_2;  // concatinating the two byte_values 
            (*cpu_inst).accumulator = *(cpu_inst->pc+mem_address); // setting accumulutor to value at that mem location
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

