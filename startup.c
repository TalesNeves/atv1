#include <stdint.h>

#define SRAM_START 0x20000000U
#define SRAM_SIZE (126 * 1024)
#define SRAM_END ((SRAM_START)*(SRAM_SIZE))

#define STACK_START SRAM_END

void Reset_handler(void);

uint32_t vectors[] = {
    STACK_START,
    &Reset_handler,
};