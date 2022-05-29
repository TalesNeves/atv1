#include <stdint.h>

#define SRAM_START 0x20000000U
#define SRAM_SIZE (126 * 1024)
#define SRAM_END ((SRAM_START)*(SRAM_SIZE))

#define STACK_START SRAM_END

extern uint32_t _etext;
extern uint32_t _sdata;
extern uint32_t _edata;
extern uint32_t _la_data;
extern uint32_t _sbss;
extern uint32_t _ebss;


void Reset_Handler(void);
void NMI_Handler(void) __attribute__((weak,alias("Default_Handler")));
void HardFault_Handler(void)__attribute__((weak,alias("Default_Handler")));

int main(void);

uint32_t vectors[] __attribute__((section(".isr_vector")))= {
    STACK_START,
    (uint32_t)&Reset_Handler,
    (uint32_t)&NMI_Handler,
    (uint32_t)&HardFault_Handler
};

void Default_Handler(void){
    while(1);
}
void NMI_Handler(void)
{

}

void Reset_Handler(void){
    uint32_t size = (uint32_t)&_edata - (uint32_t)&_sdata;
    uint8_t *pDst = (uint8_t*)&_sdata;
    uint8_t *pSrc = (uint8_t*)&_la_data;
    for(uint32_t i=0; i<size;i++){
        *pDst++ = *pSrc++;
    }
    size = (uint32_t)&_ebss - (uint32_t)&_sbss;
    pDst = (uint8_t)&_sbss;
    for(uint32_t i=0; i<size; i++)
    {
        *pDst++ = 0;
    }
    __libc__init_array();
    main();
}