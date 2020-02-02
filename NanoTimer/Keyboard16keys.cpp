/// @file 
/// Keyboard 16 keys class definition.
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

#include "Keyboard16keys.h"

const PROGMEM char Keyboard16keysClass::keymap[4][4] = {
		{ '1', '2', '3', 'A'},
		{ '4', '5', '6', 'B'},
		{ '7', '8', '9', 'C'},
		{ '*', '0', '#', 'D'}
};

#pragma region Init

void Keyboard16keysClass::init()
{
	init(A7);
}

void Keyboard16keysClass::init(int input)
{
	inputPin = input;
	currentKeyCol = 0;
	currentKeyRow = 0;
}

#pragma endregion

#pragma region Multidigit numeric input

void Keyboard16keysClass::numericInputInit(char buffer[], uint8_t bufferSize)
{
	numericInputInit(buffer, bufferSize, bufferSize);
}

void Keyboard16keysClass::numericInputInit(char buffer[], uint8_t bufferSize, uint8_t maxLen)
{
	inputBuffer = buffer;
	inputBufferSize = bufferSize;
	inputMaxSize = maxLen;
	inputPos = bufferSize - 1;
	inputLastKey = 0;
	inputBuffer[inputBufferSize - 1] = 0;
}

void Keyboard16keysClass::numericInputReInit() {
	inputLastKey = 0;
	int j = 0;
	for(; j < inputBufferSize; ++j) {
		if((inputBuffer[j] & 0xFF)  != BLANK) break;
	}
	inputPos = j - 1;
}

char Keyboard16keysClass::numericInput()
{
	char ck = currentKey();
	if (ck == 0) {		// no key pressed: do nothing
		inputLastKey = 0;
		return 0;
	}
	if (isAlpha(ck) || ck == '#') {		// alpha char: return to caller
		inputLastKey = ck;
		return ck;
	}
	if (ck != inputLastKey) {		// wait for the last key released
		inputLastKey = ck;
		if (ck == '*') {			// star: delete last char
			if (inputPos >= inputBufferSize - 2) {				// zeroes first digit
				inputPos = inputBufferSize - 1;
				inputBuffer[inputPos] = 0;
			}
			else {
				// shifts chars to right
				for (int j = inputBufferSize - 2; j >= inputBufferSize - inputMaxSize; j--) {
					inputBuffer[j + 1] = inputBuffer[j];
				}
				inputBuffer[inputBufferSize - inputMaxSize] = BLANK;
				inputPos++;
			}
		}
		else if (inputPos >= 0) {			// numeric keys input
			if (ck == '0' && inputPos == inputBufferSize - 1) {		// ignore zero on rightmost digit
				return 0;
			}
			// shifts chars to left if needed
			if (inputPos < inputMaxSize - 1) {
				for (int j = inputBufferSize - inputMaxSize + 1; j < inputBufferSize; j++) {
					inputBuffer[j - 1] = inputBuffer[j];
				}
			}
			inputBuffer[inputBufferSize - 1] = ck - '0';
			inputPos--;
		}
	}
	return 0;
}

#pragma endregion

#pragma region Hardware scanner

int Keyboard16keysClass::readColumn()
{
	int v = analogRead(inputPin);
	if (v < ROW4EDGE) return 0;
	if (v > ROW1EDGE) return 1;
	if (v > ROW2EDGE) return 2;
	if (v > ROW3EDGE) return 3;
	return 4;
}

void Keyboard16keysClass::scanKey(uint8_t col)
{
	if (col < 4) {
		uint8_t row = readColumn();
		if (row > 0) {
			currentKeyCol = col + 1;
			currentKeyRow = row;
		}
		else if (currentKeyCol == col + 1) {
			currentKeyCol = 0;
			currentKeyRow = 0;
		}
	}
}

char Keyboard16keysClass::currentKey()
{
	if (currentKeyCol == 0) {
		return 0;
	}
	return pgm_read_byte(&(keymap[currentKeyRow - 1][currentKeyCol - 1]));
}

#pragma endregion

Keyboard16keysClass Keyboard16keys;
