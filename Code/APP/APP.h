#ifndef APP_H
#define APP_H

#include "../HAL/LED/LED.h"
#include "../HAL/BUTTON/Button.h"
#include "../STD_LIBRARIES/bit_math.h"
#include "../STD_LIBRARIES/STD_TYPES.h"
#include "../MCAL/DIO/DIO_interface.h"

typedef enum{
	LEDS_OFF,
	RED_LED_ON,
	GREEN_LED_ON,
	BLUE_LED_ON,
	ALL_LEDS_ON,
	MAX_INVALID_LEDS_STATE
}app_enu_led_state_t;

void app_init(void);
void app_run(void);

#endif