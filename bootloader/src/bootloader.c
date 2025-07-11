#include "common-defines.h"
#include "libopencm3/stm32/memorymap.h"
#include <libopencm3/cm3/scb.h>

#define BOOTLOADER_SIZE (0x8000U)
#define MAIN_APP_START_ADRESS (FLASH_BASE + BOOTLOADER_SIZE)
static inline void set_msp(uint32_t top_of_main_stack)
{
	__asm volatile("msr msp, %0" : : "r"(top_of_main_stack) :);
}

static void jump_to_main(void)
{
	typedef void (*void_fn)(void);
	
	uint32_t msp_value = *(volatile uint32_t *)MAIN_APP_START_ADRESS;

	uint32_t *reset_vector_entry = (uint32_t *)(MAIN_APP_START_ADRESS + 4U);
	uint32_t *reset_vector = (uint32_t *)(*reset_vector_entry);

	void_fn jump_fn = (void_fn)reset_vector;

	SCB_VTOR = MAIN_APP_START_ADRESS;
	set_msp(msp_value);

	jump_fn();
}

int main(void)
{

	jump_to_main();

	return 0;
}
