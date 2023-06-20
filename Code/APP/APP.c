
#include "APP.h"


led_str_led_config_t LED_red;
led_str_led_config_t LED_green;
led_str_led_config_t LED_blue;

button_str_btn_config_t btn_1;



void app_init(void){
	LED_red.port_name= DIO_PORTF;
	LED_red.pin = DIO_PIN_1;
	LED_red.led_status = LED_OFF;
	
	LED_blue.port_name= DIO_PORTF;
	LED_blue.pin = DIO_PIN_2;
	LED_blue.led_status = LED_OFF;
	
	
	LED_green.port_name= DIO_PORTF;
	LED_green.pin = DIO_PIN_3;
	LED_green.led_status = LED_OFF;

	
	btn_1.port_name= DIO_PORTF;
	btn_1.pin = DIO_PIN_4;
	btn_1.button_state = BUTTON_RELEASED;
	btn_1.button_active = BUTTON_ACTIVE_LOW;
	
	
	dio_enable_clock(DIO_PORTF);

	led_intialize(&LED_red);
	led_intialize(&LED_green);
	led_intialize(&LED_blue);
	button_initializa(&btn_1);
}
void app_run(void){
	app_enu_led_state_t leds_state = LEDS_OFF;
	btn_enu_btn_state_t btn_1_state;
	uint8_t state_changed_flag = 0;
	while(1){
		
		if(state_changed_flag == 1){
			state_changed_flag = 0;
			switch(leds_state){
				case LEDS_OFF:
					led_turn_off(&LED_red);
					led_turn_off(&LED_green);
					led_turn_off(&LED_blue);
					
					break;
				case RED_LED_ON:
					led_toggle(&LED_red);
					led_turn_off(&LED_green);
					led_turn_off(&LED_blue);
					delay_ms(1000);
					led_toggle(&LED_red);
					break;
				case GREEN_LED_ON:
					led_turn_off(&LED_red);
					led_toggle(&LED_green);
					led_turn_off(&LED_blue);
					delay_ms(1000);
					led_toggle(&LED_green);
					break;
				case BLUE_LED_ON:
					led_turn_off(&LED_red);
					led_turn_off(&LED_green);
					led_toggle(&LED_blue);
					delay_ms(1000);
					led_toggle(&LED_blue);
					break;
				case ALL_LEDS_ON:
					led_turn_on(&LED_red);
					led_turn_on(&LED_green);
					led_turn_on(&LED_blue);
					delay_ms(1000);
					led_turn_off(&LED_red);
					led_turn_off(&LED_green);
					led_turn_off(&LED_blue);
					
					break;
				default:
					break;
			}
			
		}
		button_read_state(&btn_1, &btn_1_state);
		if(btn_1_state == BUTTON_PRESSED){
			while(btn_1_state == BUTTON_PRESSED){
				button_read_state(&btn_1, &btn_1_state);
			}
			state_changed_flag = 1;
			leds_state++;
			if(leds_state == MAX_INVALID_LEDS_STATE){
			
				leds_state = LEDS_OFF;
			}
		
		}
		for(uint32_t delay=0; delay <=50000; delay++);
	}
	
}