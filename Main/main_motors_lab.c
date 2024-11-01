
#include "config.h"

#ifdef MOTORS_STEPPER_LAB
/* Given MOTORS_STEPPER_FULLSTEP
Stop at a specific angle
*/
// Rotate motor one step per button press
void main_motors_stepper_lab(void)
{
	DDRD &= ~((1 << DDD0) | (1 << DDD1)); // Set PD0 and PD1 as inputs for the buttons
	DDRB = 0xFF;                          // Set PORTB as output
	int DELAY = 100;                      // Delay between steps

	// Half-step sequence
	uint8_t steps[] = {0x01, 0x03, 0x02, 0x06, 0x04, 0x0C, 0x08, 0x09};
	int num_steps = sizeof(steps) / sizeof(steps[0]);

	int step_index = 0;

	while (1)
	{
		// Check if PD0 is pressed
		if ((PIND & (1 << PIND0)) == 0)
		{
			// Advance one step in one direction
			step_index++;
			if (step_index >= num_steps)
			{
				step_index = 0;
			}

			PORTB = steps[step_index];  // Update motor position
			_delay_ms(DELAY);

			// Simple delay to prevent multiple steps per press
			while((PIND & (1 << PIND0)) == 0);
		}

		// Check if PD1 is pressed
		if ((PIND & (1 << PIND1)) == 0)
		{
			// Advance one step in the other direction
			step_index--;
			if (step_index < 0)
			{
				step_index = num_steps - 1;
			}

			PORTB = steps[step_index];  // Update motor position
			_delay_ms(DELAY);

			// Simple delay to prevent multiple steps per press
			while((PIND & (1 << PIND1)) == 0);
		}
	}
}
#endif


#ifdef MOTORS_PWM_LAB
/*mission: 
Given MOTORS_PWM_FAST
Increase/Decrease the speed by button 0/1
*/
/* PWM Motors */
/* Timer Registers
	OCR0
	TCCR0: WGM00 WGM01 CS02 CS01 CS00
*/
#include <avr/io.h>
#include <util/delay.h>

void main_motors_pwm_lab(void) {
	DDRB |= (1<<4); // OC0 as output
	TCCR0 = (1<<COM01)|(1<<WGM01)|(1<<WGM00)|(1<<CS2); // Fast PWM, non-inverted, prescale=64

	DDRD &= ~((1<<PD0) | (1<<PD1)); // Set PD0 and PD1 as input
	PORTD |= (1<<PD0) | (1<<PD1); // Enable pull-up resistors

	unsigned char speed = 0;

	while(1) {
		if (!(PIND & (1<<PD0))) { // Check if button on PD0 is pressed
			if (speed < 245) {
				speed = speed + 10;
			}
			_delay_ms(100); // Debounce delay
			} else if (!(PIND & (1<<PD1))) { // Check if button on PD1 is pressed
			if (speed > 10) {
				speed = speed - 10;
			}
			_delay_ms(100); // Debounce delay
		}

		OCR0 = speed;
		_delay_ms(10); // Update delay
	}
}
#endif
