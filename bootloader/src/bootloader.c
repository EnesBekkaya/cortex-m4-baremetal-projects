#include "common-defines.h"
#include "libopencm3/stm32/memorymap.h"
#include <libopencm3/cm3/scb.h>
#include <libopencm3/cm3/vector.h>

#define BOOTLOADER_SIZE (0x8000U)
#define MAIN_APP_START_ADRESS (FLASH_BASE + BOOTLOADER_SIZE)
static inline void set_msp(uint32_t top_of_main_stack)
{
	__asm volatile("msr msp, %0" : : "r"(top_of_main_stack) :);
}

static void jump_to_main(void)
{
	uint32_t msp_value = *(volatile uint32_t *)MAIN_APP_START_ADRESS;

	vector_table_t *main_vector_table = (vector_table_t *)(MAIN_APP_START_ADRESS);


	SCB_VTOR = MAIN_APP_START_ADRESS;
	set_msp(msp_value);
	main_vector_table->reset();

}
int main(void)
{

	jump_to_main();

	return 0;
}
