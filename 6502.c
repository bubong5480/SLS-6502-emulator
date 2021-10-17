#include <stdio.h>
#include <stddef.h>

int* fetch();
int* decode();
struct cpu* execute();

struct cpu{
    int* pc; 
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

    while (1){
        switch(*(cpu_inst->pc)){
            case 0xEA:
                *(cpu_inst->pc) += 1; 
            default: 
                printf('\n');
                break;
        }
    }
    return 0; 
}

int* fetch(struct cpu* cpu_inst) {
    return(cpu_inst->pc); 
} 

int* decode(struct cpu* cpu_inst) {
    return(cpu_inst->pc);
} 
