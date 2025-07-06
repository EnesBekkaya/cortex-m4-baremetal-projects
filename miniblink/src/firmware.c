#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>

#define LED_PORT (GPIOG)
#define LED_PIN (GPIO13)
static void rcc_setup(void){
	rcc_clock_setup_pll(&rcc_hsi_configs[RCC_CLOCK_3V3_84MHZ]);
}

static void gpio_setup(void){
	rcc_periph_clock_enable(RCC_GPIOG);
	gpio_mode_setup(LED_PORT,GPIO_MODE_OUTPUT,GPIO_PUPD_NONE,LED_PIN);
}
static void delay(uint32_t cycles){

	for (uint32_t i = 0; i < cycles; i++)
	{
		__asm__("nop");
	}
	
}
int main(void)
{
	rcc_setup();
	gpio_setup();
	while(1){

		gpio_toggle(LED_PORT,LED_PIN);
		delay(84000000/4);
	}
	return 0;
}
