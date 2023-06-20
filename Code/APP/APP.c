
#include "APP.h"
// LED configurations
led_str_led_config_t LED_red;
led_str_led_config_t LED_green;
led_str_led_config_t LED_blue;

// Button configuration
button_str_btn_config_t btn_1;

// Application initialization
void app_init(void) {
	// Configure LED_red
	LED_red.port_name = DIO_PORTF;
	LED_red.pin = DIO_PIN_1;
	LED_red.led_status = LED_OFF;
	
	// Configure LED_blue
	LED_blue.port_name = DIO_PORTF;
	LED_blue.pin = DIO_PIN_2;
	LED_blue.led_status = LED_OFF;
	
	// Configure LED_green
	LED_green.port_name = DIO_PORTF;
	LED_green.pin = DIO_PIN_3;
	LED_green.led_status = LED_OFF;

	// Configure btn_1
	btn_1.port_name = DIO_PORTF;
	btn_1.pin = DIO_PIN_4;
	btn_1.button_state = BUTTON_RELEASED;
	btn_1.button_active = BUTTON_ACTIVE_LOW;

	// Enable clock for port DIO_PORTF
	dio_enable_clock(DIO_PORTF);

	// Initialize LED configurations
	led_initialization(&LED_red);
	led_initialization(&LED_green);
	led_initialization(&LED_blue);

	// Initialize button configuration
	button_initialization(&btn_1);
}

// Application main logic
void app_run(void) {
	// Initialize variables
	app_enu_led_state_t leds_state = LEDS_OFF;
	btn_enu_btn_state_t btn_1_state;
	uint8_t state_changed_flag = 0;

	while (1) {
		// Check if the state of the LEDs has changed
		if (state_changed_flag == 1) {
			state_changed_flag = 0;
			
			// Update LEDs based on the current state
			switch (leds_state) {
				case LEDS_OFF:
					// Turn off all LEDs
					led_turn_off(&LED_red);
					led_turn_off(&LED_green);
					led_turn_off(&LED_blue);
					break;
				case RED_LED_ON:
					// Toggle the red LED
					led_toggle(&LED_red);
					led_turn_off(&LED_green);
					led_turn_off(&LED_blue);
					delay_ms(1000);
					led_toggle(&LED_red);
					break;
				case GREEN_LED_ON:
					// Toggle the green LED
					led_turn_off(&LED_red);
					led_toggle(&LED_green);
					led_turn_off(&LED_blue);
					delay_ms(1000);
					led_toggle(&LED_green);
					break;
				case BLUE_LED_ON:
					// Toggle the blue LED
					led_turn_off(&LED_red);
					led_turn_off(&LED_green);
					led_toggle(&LED_blue);
					delay_ms(1000);
					led_toggle(&LED_blue);
					break;
				case ALL_LEDS_ON:
					// Turn on all LEDs for 1 second and then turn them off
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

		// Read the state of btn_1
		button_read_state(&btn_1, &btn_1_state);

		// Check if btn_1 is pressed
		if (btn_1_state == BUTTON_PRESSED) {
			// Wait until btn_1 is released
			while (btn_1_state == BUTTON_PRESSED) {
				button_read_state(&btn_1, &btn_1_state);
			}

			// Set the state_changed_flag to 1 and increment the leds_state
			state_changed_flag = 1;
			leds_state++;

			// Reset leds_state if it reaches the maximum invalid state
			if (leds_state == MAX_INVALID_LEDS_STATE) {
				leds_state = LEDS_OFF;
			}
		}

		// Introduce a short delay
		for (uint32_t delay = 0; delay <= 50000; delay++);
	}
}
