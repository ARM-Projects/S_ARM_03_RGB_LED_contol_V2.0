#include "DELAY.h"

// Global variables
static systick_str_systick_config_t g_str_systick_config;
static systick_enu_reach_zero_flag_t g_ptr_enu_reach_zero_flag;

// Function to introduce a delay in milliseconds
void delay_ms(uint32_t copy_u32_time_out_ms) {
	// Configure SysTick for system clock as the clock source and disable interrupts
	g_str_systick_config.enu_clock_source = SYSTICK_SYSCLK_CLOCK;
	g_str_systick_config.enu_int_state = SYSTICK_DISABLE_INT;
	
	// Initialize and configure SysTick
	systick_init(&g_str_systick_config);
	systick_set_timeout_ms(copy_u32_time_out_ms);
	
	// Enable the SysTick counter
	systick_counter_enable(&g_str_systick_config);
	
	// Check the state of the SysTick counter until it reaches zero
	systick_get_state(&g_ptr_enu_reach_zero_flag);
	while (g_ptr_enu_reach_zero_flag == SYSTICK_NOT_REACH_FLAG) {
		systick_get_state(&g_ptr_enu_reach_zero_flag);
	}
	
	// Disable the SysTick counter
	systick_counter_disable(&g_str_systick_config);
}
