
#include "config.h"

#ifdef MOTORS_FULLSTEP
void main_motors_fullstep(void)
{
	DDRD = 0x00; // Set PORTD as input
	DDRB = 0xFF; // Set PORTB as output
	int DELAY = 100; // Delay between steps

	// Array to store the full-step sequence
	uint8_t steps[] = {0x66, 0xCC, 0x99, 0x33};
	int num_steps = sizeof(steps) / sizeof(steps[0]); // Number of steps in the sequence

	int step_index = 0; // Current step index

	while (1)
	{
		if ((PIND & 0x80) == 0)
		{
			// Move forward through the sequence
			PORTB = steps[step_index];
			_delay_ms(DELAY);
			step_index++;
			if (step_index >= num_steps)
			{
				step_index = 0; // Reset the index to loop through the sequence again
			}
		}
		else
		{
			// Move backward through the sequence
			step_index--;
			if (step_index < 0)
			{
				step_index = num_steps - 1; // Wrap around to the end of the sequence
			}
			PORTB = steps[step_index];
			_delay_ms(DELAY);
		}
	}
}

#endif

#ifdef MOTORS_HALFSTEP
void main_motors_halfstep(void)
{
	DDRD = 0x00; // Set PORTD as input
	DDRB = 0xFF; // Set PORTB as output
	int DELAY = 100; // Delay between steps

	// Array to store the half-step sequence
	uint8_t steps[] = {0x01, 0x03, 0x02, 0x06, 0x04, 0x0C, 0x08, 0x09};
	int num_steps = sizeof(steps) / sizeof(steps[0]); // Number of steps in the sequence

	int step_index = 0; // Current step index

	while (1)
	{
		if ((PIND & 0x80) == 0)
		{
			// Move forward through the sequence
			PORTB = steps[step_index];
			_delay_ms(DELAY);
			step_index++;
			if (step_index >= num_steps)
			{
				step_index = 0; // Reset the index to loop through the sequence again
			}
		}
		else
		{
			// Move backward through the sequence
			step_index--;
			if (step_index < 0)
			{
				step_index = num_steps - 1; // Wrap around to the end of the sequence
			}
			PORTB = steps[step_index];
			_delay_ms(DELAY);
		}
	}
}															
#endif

#ifdef MOTORS_FULLSTEP_INTERRUPT
volatile uint8_t direction = 0; // Direction flag, 0 for one way, 1 for the other
void main_motors_fullstep_interrupt(void)
{
	DDRD &= ~(1 << DDD2); // Set PD2 (INT0 pin) as input
	DDRB = 0xFF;          // Set PORTB as output
	int DELAY = 100;      // Delay between steps

	// Full-step sequence
	uint8_t steps[] = {0x66, 0xCC, 0x99, 0x33};
	int num_steps = sizeof(steps) / sizeof(steps[0]);

	int step_index = 0;

	// Set up INT0 interrupt
	EICRA = 1 << ISC01;   // Trigger on falling edge of INT0
	EIMSK = 1 << INT0;    // Enable INT0
	sei();                // Enable global interrupts

	while (1)
	{
		PORTB = steps[step_index];  // Set the motor position
		_delay_ms(DELAY);

		// Change the step index based on direction
		if (direction == 0)
		{
			step_index++;
			if (step_index >= num_steps)
			{
				step_index = 0;
			}
		}
		else
		{
			step_index--;
			if (step_index < 0)
			{
				step_index = num_steps - 1;
			}
		}
	}
}

// Interrupt Service Routine for INT0
ISR(INT0_vect)
{
	direction = !direction; // Toggle the direction flag
}
#endif

#ifdef MOTORS_HALFSTEP_INTERRUPT
volatile uint8_t direction = 0; // Direction flag, 0 for one way, 1 for the other

void main_motors_halfstep_interrupt(void)
{
	DDRD &= ~(1 << DDD2); // Set PD2 (INT0 pin) as input
	DDRB = 0xFF;          // Set PORTB as output
	int DELAY = 100;      // Delay between steps
	int ANGLE = 19;		  //Angle
	int i = 0;
	// Half-step sequence
	uint8_t steps[] = {0x01, 0x03, 0x02, 0x06, 0x04, 0x0C, 0x08, 0x09};
	int num_steps = sizeof(steps) / sizeof(steps[0]);

	int step_index = 0;

	// Set up INT0 interrupt
	EICRA = 1 << ISC01;   // Trigger on falling edge of INT0
	EIMSK = 1 << INT0;    // Enable INT0
	sei();                // Enable global interrupts

	while (1)
	{
		PORTB = steps[step_index];  // Set the motor position
		_delay_ms(DELAY);

		// Change the step index based on direction
		if (direction == 0)
		{
			step_index++;
			i++;
			if (i == ANGLE){
				while(1);
			}
			if (step_index >= num_steps)
			{
				step_index = 0;
			}
		}
		else
		{
			step_index--;
			i++;
			if (i == ANGLE){
				while(1);
			}
			if (step_index < 0)
			{
				step_index = num_steps - 1;
			}
		}
	}
}

// Interrupt Service Routine for INT0
ISR(INT0_vect)
{
	direction = !direction; // Toggle the direction flag
}
#endif

#ifdef MOTORS_PWM_FAST
/* PWM Motors */
/* Timer Registers
	OCR0
	TCCR0: WGM00 WGM01 CS02 CS01 CS00
*/

void  main_motors_pwm_fast(void)
{
	DDRB |= (1<<4);	//OC0 as output
	TCCR0 = (1<<COM01)|(1<<WGM01)|(1<<WGM00)|(1<<CS2); // Fast PWM, non-inverted, prescale=64
	
	while(1)
	{
		for(unsigned char k = 0; k < 255; k++)
		{
			OCR0 = k;
			_delay_ms(10);
		}
	}
}
#endif

#ifdef MOTORS_PWM_PHASECORRECT
/* Phase Correct PWM Motors */
/* Timer Registers
    OCR0
    TCCR0: WGM00 WGM01 CS02 CS01 CS00
*/

void main_motors_pwm_phasecorrect(void)
{
    DDRB |= (1<<4); // OC0 as output

    // Phase Correct PWM, non-inverted, prescale=64
    TCCR0 = (1<<COM01) | (1<<WGM00) | (1<<CS01) | (1<<CS00);

    while(1)
    {
        for(unsigned char k = 0; k < 255; k++)
        {
            OCR0 = k;
            _delay_ms(10);
        }
        for(unsigned char k = 255; k > 0; k--)
        {
            OCR0 = k;
            _delay_ms(10);
        }
    }
}
#endif

#ifdef MOTORS_SERVO
#define PWM_FREQUENCY 50 // 50 Hz or 20ms period
#define PRESCALER 8      // Prescaler for the timer

// Initialize Timer1 for PWM
void pwm_init() {
	// Set PB5 as output for OC1A
	DDRB |= (1 << 5);

	// Configure Timer1 for Fast PWM mode, ICR1 as TOP
	ICR1 = F_CPU / (PRESCALER * PWM_FREQUENCY) - 1; // Setting TOP for a 20ms period
	TCCR1A = (1 << COM1A1) | (1 << WGM11); // Non-inverting mode, Mode 14 (Fast PWM)
	TCCR1B = (1 << WGM12) | (1 << WGM13) | (1 << CS11); // Prescaler set to 8
}

void servo_write(uint8_t angle) {
	// Calculate the pulse width corresponding to the angle
	// Map angle to pulse width range (1ms - 2ms)
	uint16_t min_pulse_ticks = ICR1 / 20; // Minimum pulse width (1ms)
	uint16_t max_pulse_ticks = ICR1 / 10; // Maximum pulse width (2ms)
	uint16_t pulse_width_ticks = ((angle / 180.0) * (max_pulse_ticks - min_pulse_ticks)) + min_pulse_ticks;

	OCR1A = pulse_width_ticks; // Set pulse width for OC1A
}

void main_motors_servo(void) {
	pwm_init(); // Initialize PWM

	while (1) {
		for (uint8_t angle = 0; angle <= 180; angle += 10) {
			servo_write(angle);
			_delay_ms(1000); // Delay to allow servo to reach position
		}

		for (int angle = 180; angle >= 0; angle -= 10) {
			servo_write(angle);
			_delay_ms(1000); // Delay to allow servo to reach position
		}
	}
}
#endif

#ifdef MOTORS_SERVO_ADC
#define PWM_FREQUENCY 50 // 50 Hz for servo
#define PRESCALER 8      // Prescaler for Timer1
#define ADC_MAX 1023     // Maximum ADC value for 10-bit resolution

// Initialize ADC
void adc_init() {
	// Reference voltage = AVCC, left adjust result, input channel = ADC0
	ADMUX = (1 << REFS0) | (1 << ADLAR);
	// Enable ADC, set prescaler, start conversion
	ADCSRA = (1 << ADEN) | (1 << ADSC) | (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);
}

// Read ADC value from channel 0
uint16_t adc_read() {
	// Start single conversion
	ADCSRA |= (1 << ADSC);
	// Wait for conversion to complete
	while (ADCSRA & (1 << ADSC));
	// Return the ADC value
	return ADC;
}

// Initialize Timer1 for PWM
void pwm_init() {
	// Set PB5 as output for OC1A
	DDRB |= (1 << 5);

	// Configure Timer1 for Fast PWM mode, ICR1 as TOP
	ICR1 = F_CPU / (PRESCALER * PWM_FREQUENCY) - 1; // Setting TOP for a 20ms period
	TCCR1A = (1 << COM1A1) | (1 << WGM11); // Non-inverting mode, Mode 14 (Fast PWM)
	TCCR1B = (1 << WGM12) | (1 << WGM13) | (1 << CS11); // Prescaler set to 8
}

void servo_write(uint8_t angle) {
	// Calculate the pulse width corresponding to the angle
	// Map angle to pulse width range (1ms - 2ms)
	uint16_t min_pulse_ticks = ICR1 / 20; // Minimum pulse width (1ms)
	uint16_t max_pulse_ticks = ICR1 / 10; // Maximum pulse width (2ms)
	uint16_t pulse_width_ticks = ((angle / 180.0) * (max_pulse_ticks - min_pulse_ticks)) + min_pulse_ticks;

	OCR1A = pulse_width_ticks; // Set pulse width for OC1A
}

void main_motors_servo_adc(void) {
	adc_init(); // Initialize ADC
	pwm_init(); // Initialize PWM

	while (1) {
		uint16_t adc_value = adc_read(); // Read potentiometer value
		uint8_t angle = (uint8_t)((adc_value / (float)ADC_MAX) * 180); // Map ADC value to angle
		servo_write(angle); // Set servo position
		_delay_ms(20); // Short delay for stability
	}
}
#endif

#ifdef MOTORS_SERVO_UART
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include <stdlib.h>

#define F_CPU 16000000UL // 16 MHz CPU frequency
#define BAUD 9600
#define MYUBRR F_CPU/16/BAUD-1
#define PWM_FREQUENCY 50 // 50 Hz or 20ms period
#define PRESCALER 8      // Prescaler for the timer

volatile uint8_t new_angle_received = 0;
char received_str[4]; // Buffer to store received characters
uint8_t i = 0; // Index for buffer

// Initialize Timer1 for PWM
void pwm_init() {
	// Set PB5 as output for OC1A
	DDRB |= (1 << 5);

	// Configure Timer1 for Fast PWM mode, ICR1 as TOP
	ICR1 = F_CPU / (PRESCALER * PWM_FREQUENCY) - 1; // Setting TOP for a 20ms period
	TCCR1A = (1 << COM1A1) | (1 << WGM11); // Non-inverting mode, Mode 14 (Fast PWM)
	TCCR1B = (1 << WGM12) | (1 << WGM13) | (1 << CS11); // Prescaler set to 8
}
// UART1 initialization
void uart1_init(unsigned int ubrr) {
	// Set baud rate
	UBRR1H = (unsigned char)(ubrr>>8);
	UBRR1L = (unsigned char)ubrr;
	// Enable receiver and transmitter
	UCSR1B = (1<<RXEN1)|(1<<TXEN1)|(1<<RXCIE1);
	// Set frame format: 8 data, 1 stop bit
	UCSR1C = (3<<UCSZ10);
	// Enable global interrupts
	sei();
}

// UART1 transmit data
void uart1_transmit(unsigned char data) {
	// Wait for empty transmit buffer
	while (!(UCSR1A & (1<<UDRE1)));
	// Put data into buffer, sends the data
	UDR1 = data;
}

// UART1 receive interrupt
ISR(USART1_RX_vect) {
	char received_char = UDR1; // Read received data
	if (received_char == '\r' || received_char == '\n') {
		received_str[i] = '\0'; // Null-terminate the string
		new_angle_received = 1; // Set flag
		i = 0; // Reset index for next input
		} 
	else if (i < sizeof(received_str) - 1) { // secure the last \0 space
		received_str[i++] = received_char; // Store character and increment index
	}
}

// UART1 transmit string
void uart1_transmit_string(const char *str) {
	while (*str != '\0') {
		uart1_transmit(*str++);
	}
}

void servo_write(uint8_t angle) {
	// Calculate the pulse width corresponding to the angle
	// Map angle to pulse width range (1ms - 2ms) that's standard
	uint16_t min_pulse_ticks = ICR1 / 20; // Minimum pulse width (1ms)
	uint16_t max_pulse_ticks = ICR1 / 10; // Maximum pulse width (2ms)
	uint16_t pulse_width_ticks = ((angle / 180.0) * (max_pulse_ticks - min_pulse_ticks)) + min_pulse_ticks;

	OCR1A = pulse_width_ticks; // Set pulse width for OC1A
}


void main_motors_servo_uart(void) {
	pwm_init(); // Initialize PWM
	uart1_init(MYUBRR); // Initialize UART1

	while (1) {
		if (new_angle_received) {
			new_angle_received = 0; // Clear flag
			uint8_t angle = atoi(received_str); // Convert string to integer

			if (angle >= 0 && angle <= 180) {
				servo_write(angle);
				char buffer[10];
				sprintf(buffer, "%d\r\n", angle);
				uart1_transmit_string(buffer); // Send back the angle
			}
		}
	}
}
#endif


