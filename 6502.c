#include <stdio.h>
#include <stddef.h>

struct cpu{
    int* pc; 
};

struct cpu* cpu_inst;
char *memory;

int main()
{
    if ((memory = (char*) malloc((1 << 16) * sizeof(char))) == NULL ){
        return NULL; 
    }

    if((cpu_inst = (struct cpu*) malloc(sizeof(struct cpu))) == NULL){
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
