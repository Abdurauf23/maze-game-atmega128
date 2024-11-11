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

void init_clear(void) {
	init_devices();
	lcd_clear();
	ScreenBuffer_clear();
}

void show_banner(void) {
	lcd_clear();
	lcd_string(1,5,"Maze  Game");
	lcd_string(3,6,"U2110077");
	lcd_string(4,6,"U2110222");
	lcd_string(5,6,"U2110283");
	lcd_string(6,6,"U2110285");
}

void draw_levels() {
	lcd_clear();
	char score_text[8];
	sprintf(score_text, "Level = %d", level);
	lcd_string(1, 6, score_text);
	
	lcd_string(3,4,"1. Easy");
	lcd_string(4,4,"2. Mid");
	lcd_string(5,4,"3. Difficult");
	lcd_string(6,4,"4. Random");
}

void check_level(unsigned int data) {
	if (data < 10 && level != 1)
		level--;
	else if (data > 50 && level != 4)
		level++;
}

void easy(uint64_t num[128]) {
	for (int i = 0; i < 128; i++) {
		num[i] = 0;
		if (i == 0 || i == 1 || i == 126 || i == 127)
			num[i] = 0xFFFFFFFFFFFFFFFF;
		else if (i <= 10 && i >= 2)
			num[i] = 0xC000000000000000;
		else if (i <= 125 && i >= 117)
			num[i] = 0x3;
		else
			num[i] = 0xC000000000000003;
	}
}

void middle(uint64_t numbers[128]) {
	// set numbers array with actual maze values
}

void hard(uint64_t numbers[128]) {
	// set numbers array with actual maze values
}

void draw_maze() {
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

void fill_maze_array() {
	if (level == 1) {
		easy(maze_representation);
	} else if (level == 2) {
		middle(maze_representation);
	} else if (level == 3) {
		hard(maze_representation);
	} else if (level == 4) {
		level = 1;
		fill_maze_array();
	}
}

void change_player_position() {
	unsigned int joystick_x = Read_Adc_Data(3) / 16;
	unsigned int joystick_y = 127 - Read_Adc_Data(4) / 8;

	if(abs(joystick_x - 31) > JOYSTICK_DEAD_ZONE) {
		x_position += (joystick_x > 31) ? 1 : -1;
	}
	if(abs(joystick_y - 63) > JOYSTICK_DEAD_ZONE) {
		y_position += (joystick_y > 63) ? 1 : -1;
	}

	x_position = (x_position > 63) ? 63 : (x_position < 0) ? 0 : x_position;
	y_position = (y_position >127) ? 127 : (y_position < 0) ? 0 : y_position;
}

int check_win() {
	return ((x_position == 0 || x_position == 1) && (y_position >= 119 && y_position <= 122));
}

void draw_win() {
	lcd_clear();
	ScreenBuffer_clear();
	
	lcd_string(3,2,"Congratulations!");
	lcd_string(4,6,"You Won!");
	_delay_ms(2000);
	
	lcd_clear();
	ScreenBuffer_clear();
}

void play_level() {
	int won = 0;
	fill_maze_array(level);
	while (!won) {
		draw_maze();
		GLCD_Circle(x_position, y_position, PLAYER_RADIUS);
		change_player_position();
		won = check_win();
		_delay_ms(100);
	}
	draw_win();
	x_position = 60;
	y_position = 6;
}

void main_project(void) {
	unsigned int data = 31;
	init_clear();
	show_banner();
	_delay_ms(2000);
	while(1){
		draw_levels();
		data = Read_Adc_Data(3) / 16;
		if (data > 40 || data < 20)
			check_level(data);
		if (!(PIND & (1 << PD7))) {
			play_level();
		}
		_delay_ms(100);
	}
}
#endif
