/// @file 
/// Display manager class implementation.
///
/// @author
/// copyright (c) 2019 Roberto Ceccarelli - Casasoft  
/// http://strawberryfield.altervista.org 
/// 
/// @copyright
/// This is free software: 
/// you can redistribute it and/or modify it
/// under the terms of the GNU General Public License as published by
/// the Free Software Foundation, either version 3 of the License, or
/// (at your option) any later version.
/// 
/// You should have received a copy of the GNU General Public License
/// along with these files.  
/// If not, see <http://www.gnu.org/licenses/>.
///
/// @remark
/// This software is distributed in the hope that it will be useful,
/// but WITHOUT ANY WARRANTY; without even the implied warranty of
/// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  
/// See the GNU General Public License for more details.
/// 

#include "MX4_C301.h"

#pragma region Inits

// inits the display
void MX4_C301Class::init()
{
	DDRD = DDRD | DMASK; // sets pins 2 to 6 as outputs
	DDRB = DDRB | B00011111; // sets pins 8 to 12 as outputs

	clear();
}

// clears blinking flags
void MX4_C301Class::reset_blinking()
{
	for (int j = 0; j <= DISPLAY_SIZE; j++) {
		blink[j] = 0;               // No blinking
		blink_status[j] = 0xFF;     // All segments visible
	}
}

// clears the display
void MX4_C301Class::clear()
{
	dots = 0;
	for (int j = 0; j < DISPLAY_SIZE; j++) {
		display[j] = BLANK;
	}
	reset_blinking();
}

// set display to 0
void MX4_C301Class::zero()
{
	clear();
	display[DISPLAY_SIZE - 1] = 0;
}

#pragma endregion

#pragma region Low level writes

// writes raw data to output ports with blinking mask
void  MX4_C301Class::writeDigit(uint8_t picture, uint8_t blink_mask) {
	picture &= blink_mask;
	PORTD = (PORTD & ~DMASK) | (picture & DMASK);
	PORTB = (PORTB & ~BMASK) | (picture & BMASK);
}

// writes raw data to output ports
void  MX4_C301Class::writeDigit(uint8_t picture) {
	writeDigit(picture, 0xFF);
}

// writes built-incharacter to output ports with blinking mask
void MX4_C301Class::writeChar(char digit, uint8_t blink_mask) {
	if ((digit & 0x80) > 0) {
		writeDigit(digit, blink_mask);
	}
	else {
		writeDigit(pgm_read_byte_near(charmap + digit), blink_mask);
	}
}

// writes built-incharacter to output ports
void MX4_C301Class::writeChar(char digit) {
	writeChar(digit, 0xFF);
}

#pragma endregion

#pragma region multiplexing

// performs the digits multiplexing
void  MX4_C301Class::refresh(int active) {
	if (active == DISPLAY_SIZE) {
		writeDigit(dots, blink_status[DISPLAY_SIZE]);
	}
	else {
		writeChar(display[active], blink_status[active]);
	}
}

// make blinking
void MX4_C301Class::blinking()
{
	blink_counter++;
	if (blink_counter >= blink_speed) {
		blink_counter = 0;
		for (int j = 0; j <= DISPLAY_SIZE; j++) {
			blink_status[j] ^= blink[j];
			blink_status[j] |= ~blink[j];
		}
	}
}

#pragma endregion

#pragma region writes

/// displays an integer value
/// range from -999 to 9999
void MX4_C301Class::write(int value)
{
	clear();
	if (value == 0) {
		zero();
		return;
	}

	if (value < -999) {             // underflow
		set_all_digits(9, 0xFF);
		display[0] = MINUS;
		return;
	}
	if (value > 9999) {             // overflow
		set_all_digits(9, 0xFF);
		return;
	}

	bool negative = false;
	if (value < 0) {
		value = -value;
		negative = true;
	}

	int pos = DISPLAY_SIZE - 1;
	while (value > 0)
	{
		display[pos] = value % 10;
		value = value / 10;
		pos--;
	}

	if (negative) {
		display[pos] = MINUS;
	}
}

void MX4_C301Class::set_all_digits(uint8_t picture) {
	for (int j = 0; j < DISPLAY_SIZE; j++) {
		display[j] = picture;
	}
}

void MX4_C301Class::set_all_digits(uint8_t picture, uint8_t blink_mask) {
	set_all_digits(picture);
	set_all_blink(blink_mask);
}

void MX4_C301Class::set_all_blink(uint8_t blink_mask) {
	reset_blinking();
	for (int j = 0; j < DISPLAY_SIZE; j++) {
		blink[j] = blink_mask;
	}
}

#pragma endregion

#pragma region Conversions

uint8_t MX4_C301Class::ascii2keymap(char c)
{
	if (isDigit(c)) {
		return c - '0';
	}
	if (isAlpha(c)) {
		return c - 'A' + 10;
	}
	switch (c)
	{
	case '#':
		return SHARP;
	case '*':
		return ASTERISK;
	case '-':
		return MINUS;
	case '°':
		return DEGREES;
	case '"':
		return QUOTES;
	case '_':
		return UNDERSCORE;
	default:
		return BLANK;
	}

	return BLANK;
}

char MX4_C301Class::keymap2ascii(uint8_t c)
{
	if (c < 10) {
		return c + '0';
	}
	if (c >= 10 && c < 36) {
		return c - 10 + 'A';
	}
	switch (c)
	{
	case SHARP:
		return '#';
	case ASTERISK:
		return '*';
	case MINUS:
		return '-';
	case DEGREES:
		return '°';
	case QUOTES:
		return '"';
	case UNDERSCORE:
		return '_';
	default:
		return '?';
	}

	return 0;
}

#pragma endregion

const PROGMEM char MX4_C301Class::charmap[CHARMAP_SIZE] = {
	B00111111,  //!<0
	B00000110,	//!<1
	B01011011,	//!<2
	B01001111,	//!<3
	B01100110,	//!<4
	B01101101,	//!<5
	B01111101,	//!<6
	B00000111,	//!<7
	B01111111,	//!<8
	B01101111,	//!<9
	B01110111,  //!<A
	B01111100,	//!<b
	B00111001,	//!<C
	B01011110,	//!<d
	B01111001,	//!<E
	B01110001,	//!<F
	B00111101,  //!<G
	B01110110,  //!<H
	B00110000,  //!<I
	B00001110,  //!<J
	B00000000,  //!<K
	B00111000,  //!<L
	B00000000,  //!<M
	B01010100,  //!<n
	B00111111,  //!<O
	B01110011,  //!<P
	B00000000,  //!<Q
	B01010000,  //!<r
	B01101101,  //!<S
	B00110001,  //!<T
	B00111110,  //!<U
	B00000000,  //!<V
	B00000000,  //!<W
	B00000000,  //!<X
	B01101110,  //!<y
	B01011011   //!<Z
};

// MX4_C301Class MX4_C301;
