#include <stdio.h>

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
