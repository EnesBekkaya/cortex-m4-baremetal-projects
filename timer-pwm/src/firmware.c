#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>
#include <core/system.h>
#include <core/uart.h>
#include <string.h>

#include <../inc/timer.h>
#define LED_PORT 	 (GPIOG)
#define LED_PIN  	 (GPIO13)

#define UART_PORT    (GPIOA)
#define RX_PIN     	 (GPIO10)
#define TX_PIN     	 (GPIO9)

static void gpio_setup(void){
	rcc_periph_clock_enable(RCC_GPIOG);
	rcc_periph_clock_enable(RCC_GPIOA);

	gpio_mode_setup(LED_PORT,GPIO_MODE_AF,GPIO_PUPD_NONE,LED_PIN);
	gpio_set_af(LED_PORT,GPIO_AF1,LED_PIN);

	gpio_mode_setup(UART_PORT,GPIO_MODE_AF,GPIO_PUPD_NONE,RX_PIN | TX_PIN);
	gpio_set_af(UART_PORT,GPIO_AF7,RX_PIN | TX_PIN);
}


int main(void)
{
	system_setup();
	gpio_setup();
	timer_setup();
	uart_setup();

	uint64_t startTime=system_get_ticks();
	float duty_cycle=0.0f;
	timer_pwm_set_duty_cycle(duty_cycle);
	while(1){
		if(system_get_ticks()-startTime >=10){
			duty_cycle+=1.0f;
			if(duty_cycle>100.0f){
				duty_cycle=0.0f;
			}
			timer_pwm_set_duty_cycle(duty_cycle);

			startTime=system_get_ticks();
		}

		 if(uart_data_available()){
			uint8_t data= uart_read_byte();
			uart_write_byte(data + 1 );
		 }
	
	}
	return 0;
}
