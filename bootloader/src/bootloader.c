#include "common-defines.h"
#include "libopencm3/stm32/memorymap.h"
#include <libopencm3/cm3/scb.h>
#include <libopencm3/cm3/vector.h>
#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>

#include "core/uart.h"
#include "core/system.h"
#include "comms.h"

#define UART_PORT    (GPIOA)
#define RX_PIN     	 (GPIO10)
#define TX_PIN     	 (GPIO9)

#define BOOTLOADER_SIZE (0x8000U)
#define MAIN_APP_START_ADRESS (FLASH_BASE + BOOTLOADER_SIZE)

static void gpio_setup(void){
	rcc_periph_clock_enable(RCC_GPIOA);

   	gpio_set_af(UART_PORT,GPIO_AF7,RX_PIN | TX_PIN);


	gpio_mode_setup(UART_PORT,GPIO_MODE_AF,GPIO_PUPD_NONE,RX_PIN | TX_PIN);

}
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
	system_setup();
	gpio_setup();
	uart_setup();
	comms_setup();

	comms_packet_t packet = {
		.length = 9,
		.data = {1, 2, 3, 4, 5, 6, 7, 8, 9, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff},
		.crc = 0
	};
	packet.crc = comms_compute_crc(&packet);
	comms_packet_t rx_packet;
	while (true)
	{
		comms_update();
		if(comms_packet_available()){
			comms_read(&rx_packet);
		}
		comms_write(&packet);
		system_delay(500);
	}
	
	jump_to_main();

	return 0;
}
