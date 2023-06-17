
#include "APP.h"

led_str_led_config_t LED_red;   // LED configuration for red LED
led_str_led_config_t LED_green; // LED configuration for green LED
led_str_led_config_t LED_blue;  // LED configuration for blue LED

button_str_btn_config_t btn_1; // Button configuration for button 1
/**
 * @brief Initializes the LED and button configurations for the application.
 *
 * This function sets up the initial configurations for the LEDs and buttons used in the application.
 * It assigns the port names, pin numbers, LED statuses, button states, and button active modes to their respective configurations.
 * The function also enables the clock for the specified port and initializes the LEDs and buttons using the appropriate initialization functions.
 *
 * @return void
 */
void app_init(void)
{
    // Initialize LED_red configuration
    LED_red.port_name = DIO_PORTF;
    LED_red.pin = DIO_PIN_1;
    LED_red.led_status = LED_OFF;

    // Initialize LED_blue configuration
    LED_blue.port_name = DIO_PORTF;
    LED_blue.pin = DIO_PIN_2;
    LED_blue.led_status = LED_OFF;

    // Initialize LED_green configuration
    LED_green.port_name = DIO_PORTF;
    LED_green.pin = DIO_PIN_3;
    LED_green.led_status = LED_OFF;

    // Initialize btn_1 configuration
    btn_1.port_name = DIO_PORTF;
    btn_1.pin = DIO_PIN_4;
    btn_1.button_state = BUTTON_RELEASED;
    btn_1.button_active = BUTTON_ACTIVE_LOW;

    dio_enable_clock(DIO_PORTF); // Enable clock for DIO_PORTF

    led_initialization(&LED_red);   // Initialize red LED
    led_initialization(&LED_green); // Initialize green LED
    led_initialization(&LED_blue);  // Initialize blue LED

    button_initialization(&btn_1); // Initialize button 1
}

/**
 * @brief Runs the main application loop for controlling LEDs based on button presses.
 *
 * This function continuously loops and monitors the state of a button (btn_1).
 * When the button is pressed, it changes the state of the LEDs (LED_red, LED_green, LED_blue) according to a predefined sequence.
 * The LEDs are toggled or turned on/off based on the current state of the LEDs and the button press.
 * The function uses a state_changed_flag to track if the LED state needs to be changed.
 * The LED state changes are implemented using the appropriate LED control functions (led_toggle, led_turn_on, led_turn_off).
 * The function also checks for the maximum invalid LED state and resets the LED state back to LEDS_OFF if reached.
 * The function includes a delay loop to introduce a delay between each iteration of the loop.
 *
 * @return void
 */
void app_run(void)
{
    app_enu_led_state_t leds_state = LEDS_OFF; // Initialize the LED state to LEDS_OFF
    btn_enu_btn_state_t btn_1_state;
    uint8_t state_changed_flag = 0;

    while (1)
    {
        if (state_changed_flag == 1)
        {
            state_changed_flag = 0;

            switch (leds_state)
            {
            case LEDS_OFF:
                led_toggle(&LED_red);   // Toggle red LED
                led_toggle(&LED_green); // Toggle green LED
                led_toggle(&LED_blue);  // Toggle blue LED
                break;
            case RED_LED_ON:
                led_toggle(&LED_red);     // Toggle red LED
                led_turn_off(&LED_green); // Turn off green LED
                led_turn_off(&LED_blue);  // Turn off blue LED
                break;
            case GREEN_LED_ON:
                led_turn_off(&LED_red);  // Turn off red LED
                led_toggle(&LED_green);  // Toggle green LED
                led_turn_off(&LED_blue); // Turn off blue LED
                break;
            case BLUE_LED_ON:
                led_turn_off(&LED_red);   // Turn off red LED
                led_turn_off(&LED_green); // Turn off green LED
                led_toggle(&LED_blue);    // Toggle blue LED
                break;
            case ALL_LEDS_ON:
                led_turn_on(&LED_red);   // Turn on red LED
                led_turn_on(&LED_green); // Turn on green LED
                led_turn_on(&LED_blue);  // Turn on blue LED
                break;
            default:
                break;
            }
        }

        button_read_state(&btn_1, &btn_1_state); // Read the state of button 1

        if (btn_1_state == BUTTON_PRESSED)
        {
            while (btn_1_state == BUTTON_PRESSED)
            {
                button_read_state(&btn_1, &btn_1_state); // Wait until the button is released
            }

            state_changed_flag = 1; // Set the flag to indicate LED state change
            leds_state++;           // Increment the LED state

            if (leds_state == MAX_INVALID_LEDS_STATE)
            {
                leds_state = LEDS_OFF; // Reset LED state if the maximum invalid state is reached
            }
        }

        for (uint32_t delay = 0; delay <= 50000; delay++)
            ; // Introduce a delay between iterations
    }
}
