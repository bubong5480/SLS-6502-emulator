#include <stdio.h>

int* fetch();
int* decode();
struct cpu* execute();

struct cpu{
    int* pc; 
};

struct cpu* cpu_inst; 

int main()
{
    while (1);
        switch(*(cpu_inst->pc)){
            case 'EA':
                *(cpu_inst->pc) += 1; 
            default: 
                printf('\n');
                break;
        }
    return 0; 
}

int* fetch(struct cpu* cpu_inst) {
    return(cpu_inst->pc); 
} 

int* decode(struct cpu* cpu_inst) {
    return(cpu_inst->pc);
} 
