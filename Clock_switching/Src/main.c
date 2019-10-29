#include <stdint.h>

#define SRAM_ADDRESS1 0x2000012CU

int main() {
    uint32_t value = 0;
    uint32_t *ptr = (uint32_t*) SRAM_ADDRESS1;
    
    while(1) { //  
        value = *ptr;
        if(value) break;
    }
    
    while(1);
    
    return 0;
}

