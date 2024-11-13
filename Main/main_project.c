#include "config.h"

#ifdef EMBEDDED_PROJECT

#define JOYSTICK_DEAD_ZONE 10
#define PLAYER_RADIUS 2

unsigned int x_position = 60;
unsigned int y_position = 6;
unsigned int mData_ADC3 = 0;
unsigned int mData_ADC4 = 0;
unsigned int level = 1;
uint64_t maze_representation[128];

void init_touch_sensor(void) {
	DDRC &= ~(1 << PC3); // Set PC3 as input
	PORTC |= (1 << PC3); // Enable pull-up resistor on PC3
}

void init_clear(void)
{
	cli();
	Interrupt_init();
	Uart1_init();
	init_touch_sensor();
	sei();
	init_devices();
	lcd_clear();
	ScreenBuffer_clear();
}

void show_banner(void)
{
	lcd_clear();
	lcd_string(1, 5, "Maze  Game");
	lcd_string(3, 6, "U2110077");
	lcd_string(4, 6, "U2110222");
	lcd_string(5, 6, "U2110283");
	lcd_string(6, 6, "U2110285");
}

void draw_levels(void)
{
	lcd_clear();
	char score_text[8];
	sprintf(score_text, "Level = %d", level);
	lcd_string(1, 6, score_text);

	lcd_string(3, 4, "1. Easy");
	lcd_string(4, 4, "2. Mid");
	lcd_string(5, 4, "3. Difficult");
	lcd_string(6, 4, "4. Random");
}

void check_level(unsigned int data)
{
	if (data < 10 && level != 1)
		level--;
	else if (data > 50 && level != 4)
		level++;
}

void easy(uint64_t num[128])
{

	for (int i = 0; i < 128; i++)
	{
		num[i] = 0;
		if (i == 0 || i == 1 || i == 126 || i == 127)
		num[i] = 0xFFFFFFFFFFFFFFFF;
		else if (i <= 10 && i >= 2)
		num[i] = 0xC000000000000000;
		else if (i <= 12 && i > 10)
		num[i] = 0xF00FFFFFFFFFFFFF;
		else if (i <= 30 && i > 12)
		num[i] = 0xC000000000000003;
		else if (i <= 32 && i > 30)
		num[i] = 0xFFFFFFFFFFFFF00F;
		else if (i <= 50 && i > 32)
		num[i] = 0xC000000000000003;
		else if (i <= 52 && i > 50)
		num[i] = 0xF00FFFFFFFFFFFFF;
		else if (i <= 70 && i > 52)
		num[i] = 0xC000000000000003;
		else if (i <= 72 && i > 70)
		num[i] = 0xFFFFFFFFFFFFF00F;
		else if (i <= 90 && i > 72)
		num[i] = 0xC000000000000003;
		else if (i <= 92 && i > 90)
		num[i] = 0xF00FFFFFFFFFFFFF;
		else if (i <= 110 && i > 92)
		num[i] = 0xC000000000000003;
		else if (i <= 112 && i > 110)
		num[i] = 0xFFFFFFF00FFFFFFF;
		else if (i <= 117 && i > 112)
		num[i] = 0xC000000000000003;
		else if (i <= 125 && i >= 117)
		num[i] = 0x3;
	}
}

void middle(uint64_t num[128])
{
	if (rand() % 2 == 1)
	{
		for (int i = 0; i < 128; i++)
		{
			num[i] = 0;
			if (i == 0 || i == 1 || i == 126 || i == 127)
				num[i] = 0xFFFFFFFFFFFFFFFF;
			else if (i >= 2 && i <= 9)
				num[i] = 0xC00000300C030000;
			else if (i >= 10 && i <= 15)
				num[i] = 0xC00000300C030003;
			else if (i >= 16 && i <= 17)
				num[i] = 0xC03FFFF00C0300FF;
			else if (i >= 18 && i <= 31)
				num[i] = 0xC000000000030003;
			else if (i >= 32 && i <= 33)
				num[i] = 0xC03FFFFFFFFFFC03;
			else if ((i >= 34 && i <= 47) || (i >= 66 && i <= 79))
				num[i] = 0xC030000000000003;
			else if (i >= 48 && i <= 49)
				num[i] = 0xC03FFFF00003FFFF;
			else if ((i >= 50 && i <= 63) || (i >= 82 && i <= 95) || (i >= 98 && i <= 111))
				num[i] = 0xC000003000000003;
			else if (i >= 64 && i <= 65)
				num[i] = 0xFFFFC03FFFFF0003;
			else if ((i >= 80 && i <= 81) || (i >= 112 && i <= 113))
				num[i] = 0xC03FFFFFFFFF0003;
			else if (i >= 96 && i <= 97)
				num[i] = 0xFFFFC0300003FFFF;
			else if (i >= 114 && i <= 116)
				num[i] = 0xC000000000000003;
			else if (i >= 117 && i <= 125)
				num[i] = 0x3;
		}
	}
	else
	{
		for (int i = 0; i < 128; i++)
		{
			num[i] = 0;
			if (i == 0 || i == 1 || i == 126 || i == 127)
				num[i] = 0xFFFFFFFFFFFFFFFF;
			else if (i < 117 && i >= 2)
				num[i] = 0xC0300C0000C03000;
			else if (i <= 125 && i >= 117)
				num[i] = 0x0030000300003003;
		}
	}
}

void hard(uint64_t num[128])
{
	if (rand() % 2 == 1)
	{
		for (int i = 0; i < 128; i++)
		{
			num[i] = 0;
			if (i == 0 || i == 1 || i == 126 || i == 127)
				num[i] = 0xFFFFFFFFFFFFFFFF;
			else if (i >= 2 && i <= 9)
				num[i] = 0xC000000180000000;
			else if (i >= 10 && i <= 11)
				num[i] = 0xC03FFE01807FFFFF;
			else if (i >= 12 && i <= 19)
				num[i] = 0xC030000180000003;
			else if (i >= 20 && i <= 21)
				num[i] = 0xC03FFE01FFE01803;
			else if (i >= 22 && i <= 29)
				num[i] = 0xC030060000601803;
			else if (i >= 30 && i <= 31)
				num[i] = 0xC03007FF80601803;
			else if (i >= 32 && i <= 39)
				num[i] = 0xC030000180601803;
			else if (i >= 40 && i <= 41)
				num[i] = 0xC03FFE0180601803;
			else if (i >= 42 && i <= 49)
				num[i] = 0xC000060180601803;
			else if (i >= 50 && i <= 51)
				num[i] = 0xC03FFE0180601803;
			else if (i >= 52 && i <= 59)
				num[i] = 0xC000000180601803;
			else if (i >= 60 && i <= 61)
				num[i] = 0xFFFFFFFF807FF803;
			else if (i >= 62 && i <= 69)
				num[i] = 0xC000000180001803;
			else if (i >= 70 && i <= 71)
				num[i] = 0xC0300C01FFE01803;
			else if (i >= 72 && i <= 79)
				num[i] = 0xC0300C0000600003;
			else if (i >= 80 && i <= 81)
				num[i] = 0xC0300C03FFFFFC03;
			else if (i >= 82 && i <= 89)
				num[i] = 0xC0300C0300000003;
			else if (i >= 90 && i <= 91)
				num[i] = 0xFFF00FFF00FFFFFF;
			else if (i >= 92 && i <= 99)
				num[i] = 0xC0000C0000000003;
			else if (i >= 100 && i <= 101)
				num[i] = 0xC0300FFFFFFFFC03;
			else if (i >= 102 && i <= 109)
				num[i] = 0xC030000000000C03;
			else if (i >= 110 && i <= 111)
				num[i] = 0xC03FFC03FFFFFC03;
			else if (i >= 112 && i <= 116)
				num[i] = 0xC0300C0300000003;
			else if (i >= 117 && i <= 125)
				num[i] = 0xC0000000003;
		}
	}
	else
	{
		for (int i = 0; i < 128; i++)
		{
			num[i] = 0;
			if (i == 0 || i == 1 || i == 126 || i == 127)
				num[i] = 0xFFFFFFFFFFFFFFFF; // 1 & 13
			else if (i <= 10 && i >= 2)
				num[i] = 0xC0000C0000003000;
			else if (i <= 12 && i > 10)
				num[i] = 0xC0300C03FFFFF003; // 2
			else if (i <= 20 && i > 12)
				num[i] = 0xC030000300003003;
			else if (i <= 22 && i > 20)
				num[i] = 0xC0300FFF00C03003; // 3
			else if (i <= 30 && i > 22)
				num[i] = 0xC030000000C00003;
			else if (i <= 32 && i > 30)
				num[i] = 0xC03FFFFFFFFFFFFF; // 4
			else if (i <= 40 && i > 32)
				num[i] = 0xC000000000C00003;
			else if (i <= 42 && i > 40)
				num[i] = 0xFFFFFFFF00C03003; // 5
			else if (i <= 50 && i > 42)
				num[i] = 0xC000000300C03003;
			else if (i <= 52 && i > 50)
				num[i] = 0xC03FFC0300FFF003; // 6
			else if (i <= 60 && i > 52)
				num[i] = 0xC0000C0000000003;
			else if (i <= 62 && i > 60)
				num[i] = 0xFFF00FFFFFFFF003; // 7
			else if (i <= 70 && i > 62)
				num[i] = 0xC0000C0000003003;
			else if (i <= 72 && i > 70)
				num[i] = 0xFFF00C0300FFF003; // 8
			else if (i <= 80 && i > 72)
				num[i] = 0xC0300C0300000003;
			else if (i <= 82 && i > 80)
				num[i] = 0xC0300FFF00FFFFFF; // 9
			else if (i <= 90 && i > 82)
				num[i] = 0xC030000300C00003;
			else if (i <= 92 && i > 90)
				num[i] = 0xC03FF00300003003; // 10
			else if (i <= 100 && i > 92)
				num[i] = 0xC000000300003003;
			else if (i <= 102 && i > 100)
				num[i] = 0xC03FFFFFFFFFFFFF; // 11
			else if (i <= 110 && i > 102)
				num[i] = 0xC000000000000003;
			else if (i <= 112 && i > 110)
				num[i] = 0xFFFFFFFFFFFFF003; // 12
			else if (i <= 117 && i > 112)
				num[i] = 0xC0000C0000003003;
			else if (i <= 120 && i >= 117)
				num[i] = 0x0000000000000003;
			else if (i <= 125 && i >= 120)
				num[i] = 0x0030000300000003;
		}
	}
}

void draw_maze(void) {
	lcd_clear();
	ScreenBuffer_clear();
	for (int i = 0; i < 128; i++) {
		uint64_t row = maze_representation[i];
		
		if (row & ((uint64_t)1 << 63)) GLCD_Dot(0, i);
		if (row & ((uint64_t)1 << 62)) GLCD_Dot(1, i);
		if (row & ((uint64_t)1 << 61)) GLCD_Dot(2, i);
		if (row & ((uint64_t)1 << 60)) GLCD_Dot(3, i);
		if (row & ((uint64_t)1 << 59)) GLCD_Dot(4, i);
		if (row & ((uint64_t)1 << 58)) GLCD_Dot(5, i);
		if (row & ((uint64_t)1 << 57)) GLCD_Dot(6, i);
		if (row & ((uint64_t)1 << 56)) GLCD_Dot(7, i);
		if (row & ((uint64_t)1 << 55)) GLCD_Dot(8, i);
		if (row & ((uint64_t)1 << 54)) GLCD_Dot(9, i);
		if (row & ((uint64_t)1 << 53)) GLCD_Dot(10, i);
		if (row & ((uint64_t)1 << 52)) GLCD_Dot(11, i);
		if (row & ((uint64_t)1 << 51)) GLCD_Dot(12, i);
		if (row & ((uint64_t)1 << 50)) GLCD_Dot(13, i);
		if (row & ((uint64_t)1 << 49)) GLCD_Dot(14, i);
		if (row & ((uint64_t)1 << 48)) GLCD_Dot(15, i);
		if (row & ((uint64_t)1 << 47)) GLCD_Dot(16, i);
		if (row & ((uint64_t)1 << 46)) GLCD_Dot(17, i);
		if (row & ((uint64_t)1 << 45)) GLCD_Dot(18, i);
		if (row & ((uint64_t)1 << 44)) GLCD_Dot(19, i);
		if (row & ((uint64_t)1 << 43)) GLCD_Dot(20, i);
		if (row & ((uint64_t)1 << 42)) GLCD_Dot(21, i);
		if (row & ((uint64_t)1 << 41)) GLCD_Dot(22, i);
		if (row & ((uint64_t)1 << 40)) GLCD_Dot(23, i);
		if (row & ((uint64_t)1 << 39)) GLCD_Dot(24, i);
		if (row & ((uint64_t)1 << 38)) GLCD_Dot(25, i);
		if (row & ((uint64_t)1 << 37)) GLCD_Dot(26, i);
		if (row & ((uint64_t)1 << 36)) GLCD_Dot(27, i);
		if (row & ((uint64_t)1 << 35)) GLCD_Dot(28, i);
		if (row & ((uint64_t)1 << 34)) GLCD_Dot(29, i);
		if (row & ((uint64_t)1 << 33)) GLCD_Dot(30, i);
		if (row & ((uint64_t)1 << 32)) GLCD_Dot(31, i);
		if (row & ((uint64_t)1 << 31)) GLCD_Dot(32, i);
		if (row & ((uint64_t)1 << 30)) GLCD_Dot(33, i);
		if (row & ((uint64_t)1 << 29)) GLCD_Dot(34, i);
		if (row & ((uint64_t)1 << 28)) GLCD_Dot(35, i);
		if (row & ((uint64_t)1 << 27)) GLCD_Dot(36, i);
		if (row & ((uint64_t)1 << 26)) GLCD_Dot(37, i);
		if (row & ((uint64_t)1 << 25)) GLCD_Dot(38, i);
		if (row & ((uint64_t)1 << 24)) GLCD_Dot(39, i);
		if (row & ((uint64_t)1 << 23)) GLCD_Dot(40, i);
		if (row & ((uint64_t)1 << 22)) GLCD_Dot(41, i);
		if (row & ((uint64_t)1 << 21)) GLCD_Dot(42, i);
		if (row & ((uint64_t)1 << 20)) GLCD_Dot(43, i);
		if (row & ((uint64_t)1 << 19)) GLCD_Dot(44, i);
		if (row & ((uint64_t)1 << 18)) GLCD_Dot(45, i);
		if (row & ((uint64_t)1 << 17)) GLCD_Dot(46, i);
		if (row & ((uint64_t)1 << 16)) GLCD_Dot(47, i);
		if (row & ((uint64_t)1 << 15)) GLCD_Dot(48, i);
		if (row & ((uint64_t)1 << 14)) GLCD_Dot(49, i);
		if (row & ((uint64_t)1 << 13)) GLCD_Dot(50, i);
		if (row & ((uint64_t)1 << 12)) GLCD_Dot(51, i);
		if (row & ((uint64_t)1 << 11)) GLCD_Dot(52, i);
		if (row & ((uint64_t)1 << 10)) GLCD_Dot(53, i);
		if (row & ((uint64_t)1 << 9)) GLCD_Dot(54, i);
		if (row & ((uint64_t)1 << 8)) GLCD_Dot(55, i);
		if (row & ((uint64_t)1 << 7)) GLCD_Dot(56, i);
		if (row & ((uint64_t)1 << 6)) GLCD_Dot(57, i);
		if (row & ((uint64_t)1 << 5)) GLCD_Dot(58, i);
		if (row & ((uint64_t)1 << 4)) GLCD_Dot(59, i);
		if (row & ((uint64_t)1 << 3)) GLCD_Dot(60, i);
		if (row & ((uint64_t)1 << 2)) GLCD_Dot(61, i);
		if (row & ((uint64_t)1 << 1)) GLCD_Dot(62, i);
		if (row & ((uint64_t)1 << 0)) GLCD_Dot(63, i);
	}
}

void fill_maze_array(void)
{
	if (level == 1)
	{
		easy(maze_representation);
	}
	else if (level == 2)
	{
		middle(maze_representation);
	}
	else if (level == 3)
	{
		hard(maze_representation);
	}
	else if (level == 4)
	{
		level = (random() % 3) + 1;
		fill_maze_array();
	}
}

int get_bit_at(int x, int y) {
	if (x < 0 || x >= 64 || y < 0 || y >= 128) {
		return 0;
	}
	uint64_t row_value = maze_representation[y];
	int bit_position = 63 - x;
	return (row_value >> bit_position) & 1;
}

void change_player_position(void)
{
	unsigned int joystick_x = Read_Adc_Data(3) / 16;
	unsigned int joystick_y = 127 - Read_Adc_Data(4) / 8;

	if (abs(joystick_x - 31) > JOYSTICK_DEAD_ZONE)
	{
		if (joystick_x > 31) {
			if (!get_bit_at(x_position + 3, y_position - 2) && 
				!get_bit_at(x_position + 3, y_position - 1) && 
				!get_bit_at(x_position + 3, y_position) && 
				!get_bit_at(x_position + 3, y_position - 1) && 
				!get_bit_at(x_position + 3, y_position + 2)) {
				x_position += 1;
			}
		}
		else {
			if (!get_bit_at(x_position - 3, y_position - 2) &&
				!get_bit_at(x_position - 3, y_position - 1) &&
				!get_bit_at(x_position - 3, y_position) &&
				!get_bit_at(x_position - 3, y_position - 1) &&
				!get_bit_at(x_position - 3, y_position + 2)) {
				x_position -= 1;
			}
		}
	}
	if (abs(joystick_y - 63) > JOYSTICK_DEAD_ZONE)
	{
				if (joystick_y > 63) {
					if (!get_bit_at(x_position + 2, y_position + 3) &&
						!get_bit_at(x_position + 1, y_position + 3) &&
						!get_bit_at(x_position,     y_position + 3) &&
						!get_bit_at(x_position - 1, y_position + 3) &&
						!get_bit_at(x_position - 2, y_position + 3)) {
						y_position += 1;
					}
				}
				else {
					if (!get_bit_at(x_position + 2, y_position - 3) &&
						!get_bit_at(x_position + 1, y_position - 3) &&
						!get_bit_at(x_position,     y_position - 3) &&
						!get_bit_at(x_position - 1, y_position - 3) &&
						!get_bit_at(x_position - 2, y_position - 3)) {
						y_position -= 1;
					}
				}
	}

	x_position = (x_position > 63) ? 63 : (x_position < 0) ? 0
														   : x_position;
	y_position = (y_position > 127) ? 127 : (y_position < 0) ? 0
															 : y_position;
}

int check_win(void)
{
	return ((x_position == 0 || x_position == 1) && (y_position >= 118 && y_position <= 124));
}

void draw_win(void)
{
	lcd_clear();
	ScreenBuffer_clear();

	lcd_string(3, 2, "Congratulations!");
	lcd_string(4, 6, "You Won!");
	_delay_ms(2000);

	lcd_clear();
	ScreenBuffer_clear();
}

void play_level(void)
{
	int won = 0;
	fill_maze_array();
	while (!won)
	{
		draw_maze();
		GLCD_Circle(x_position, y_position, PLAYER_RADIUS);
		change_player_position();
		won = check_win();
		_delay_ms(100);
		if ((PINC & (1 << PC3)))
		{
			x_position = 60;
			y_position = 6;
			return;
		}
	}
	draw_win();
	x_position = 60;
	y_position = 6;
}

void main_project(void)
{
	unsigned int data = 31;
	init_clear();
	show_banner();
	_delay_ms(1000);
	while (1)
	{
		draw_levels();
		data = Read_Adc_Data(3) / 16;
		if (data > 40 || data < 20)
			check_level(data);
		if (!(PIND & (1 << PD7)))
		{
			play_level();
		}	
		_delay_ms(100);
	}
}
#endif
