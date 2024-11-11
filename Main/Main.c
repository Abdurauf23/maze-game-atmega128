/*
20230204
Hong Jeong
https://ww1.microchip.com/downloads/en/DeviceDoc/doc2467.pdf
*/

#include "config.h"

int main (void)
{
	#ifdef ACCELEROMETER
	main_accelerometer();
	#elif defined(ADC_INTERRUPT)
	main_adc_interrupt();
	#elif defined(ADC_INTERRUPT_UART_INTERRUPT)
	main_adc_interrupt_uart_interrupt();
	#elif defined(ADC_INTERRUPT_UART_POLLING)
	main_adc_interrupt_uart_polling();
	#elif defined(ADC_POLLING)
	main_adc_polling();
	#elif defined(ADC_POLLING_UART_POLLING)
	main_adc_polling_uart_polling();
	#elif defined(BLINK_PORT)
	main_blink_port();
	#elif defined(BLINK_PIN)
	main_blink_pin();
	#elif defined(BLINK_ASM)
	main_blink_asm();
	#elif defined(BLINK_ASM_MACRO)
	main_blink_asm_macro();
	#elif defined(BLINK_ASM_RANDOM)
	main_blink_asm_random();
	#elif defined(BLINK_ASM_RANDOM_DELAY)
	main_blink_asm_random_delay();
	#elif defined(CDS)
	main_cds();
	#elif defined(GAME_OBSTACLE)
	main_game_obstacle();
	#elif defined(GAME_OBSTACLE_LEVEL)
	main_game_obstacle_level();
	#elif defined(GAME_HANGMAN)
	main_game_hangman();
	#elif defined(GAME_PUZZLE)
	main_game_puzzle();
	#elif defined(GAME_WORD_PUZZLE)
	main_game_word_puzzle();
	#elif defined(GRAPHICS_BASICS)
	main_graphics_basics();
	#elif defined(GRAPHICS_MOVEMENT)
	main_graphics_movement();
	#elif defined(GRAPHICS_RANDOM)
	main_graphics_random();
	#elif defined(GRAPHICS_BOUNCING_BALL)
	main_graphics_bouncing_ball();
	#elif defined(GRAPHICS_MOVING_SQUARE)
	main_graphics_moving_square();
	#elif defined(GRAPHICS_SINE_WAVE)
	main_graphics_sine_wave();
	#elif defined(INTERRUPT_EXTERNAL)
	main_interrupt_external();
	#elif defined(INTERRUPT_LAB)
	main_interrupt_lab();
	#elif defined(INTERRUPT_TIMER)
	main_interrupt_timer();
	#elif defined(INTERRUPT_TIMER_CTC)
	main_interrupt_timer_ctc();
	#elif defined(IOT)
	main_iot();
	#elif defined(JOYSTICK)
	main_joystick();
	#elif defined(MEMORY_EEPROM)
	main_memory_eeprom();
	#elif defined(MEMORY_PROGRAM)
	main_memory_program();
	#elif defined(MOTORS_FULLSTEP)
	main_motors_fullstep();
	#elif defined(MOTORS_FULLSTEP_INTERRUPT)
	main_motors_fullstep_interrupt();
	#elif defined(MOTORS_HALFSTEP)
	main_motors_halfstep();
	#elif defined(MOTORS_HALFSTEP_INTERRUPT)
	main_motors_halfstep_interrupt();
	#elif defined(MOTORS_STEPPER_LAB)
	main_motors_stepper_lab();
	#elif defined(MOTORS_PWM_FAST)
	main_motors_pwm_fast();
	#elif defined(MOTORS_PWM_PHASECORRECT)
	main_motors_pwm_phasecorrect();
	#elif defined(MOTORS_PWM_LAB)
	main_motors_pwm_lab();
	#elif defined(MOTORS_SERVO)
	main_motors_servo();
	#elif defined(MOTORS_SERVO_ADC)
	main_motors_servo_adc();
	#elif defined(MOTORS_SERVO_UART)
	main_motors_servo_uart();
	#elif defined(PORT_BLINKING)
	main_port_blinking();
	#elif defined(PORT_ROTATION)
	main_port_rotation();
	#elif defined(SERIAL_BUFFER)
	main_serial_buffer();
	#elif defined(SERIAL_INTERRUPT)
	main_serial_interrupt();
	#elif defined(SERIAL_INTERRUPT_LAB)
	main_serial_interrupt_lab();
	#elif defined(SERIAL_POLLING)
	main_serial_polling();
	#elif defined(SERIAL_POLLING_SIMULIDE)
	main_serial_polling_simulide();
	#elif defined(SERIAL_WORD)
	main_serial_word();
	#elif defined(TIMER_COUNTER)
	main_timer_counter();
	#elif defined(TIMER_CTC)
	main_timer_ctc();
	#elif defined(TIMER_FASTPWM)
	main_timer_fastpwm();
	#elif defined(TIMER_NORMAL)
	main_timer_normal();
	#elif defined(EMBEDDED_PROJECT)
	main_project();
	#else
	// Code to execute when none of the above conditions are met
	#endif
	// The rest of your main function
	return 0;
}
