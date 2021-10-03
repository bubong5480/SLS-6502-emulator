#include <stdio.h>
#include <stddef.h>

struct cpu{
    int* pc; 
};

struct cpu* cpu_inst;

int main()
{
    if((cpu_inst = malloc(sizeof(struct cpu))) == NULL){
        return NULL; 
    }    

    while (1){
        switch(*(cpu_inst->pc)){
            case 'EA':
                *(cpu_inst->pc) += 1; 
            default: 
                printf('\n');
                break;
        }
    }
    return 0; 
}
