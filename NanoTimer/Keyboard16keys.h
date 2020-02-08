/// @file 
/// Keyboard 16 keys class definition.
///
/// @author
/// copyright (c) 2019-2020 Roberto Ceccarelli - Casasoft  
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

#ifndef _KEYBOARD16KEYS_h
#define _KEYBOARD16KEYS_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
#include "WProgram.h"
#endif

#include "MX4_C301.h"

/// Rows values detected   
/// 1009    
///  507  
///  338  
///  253  
static const unsigned int ROW1EDGE =	750;
static const unsigned int ROW2EDGE =	420;
static const unsigned int ROW3EDGE =	295;
static const unsigned int ROW4EDGE =	120;

///@brief
/// 16 keys keypad manager
class Keyboard16keysClass
{
protected:
	int inputPin = A7;		//!< default input on pin A7
	int	readColumn();			//!< return pressed row for current column
	static const PROGMEM char keymap[4][4];			//!< keys map

	/// @name multidigit numeric input
	/// Numeric input on display buffer
	/// @{
	char* inputBuffer;			//!< display buffer for multidigit input
	uint8_t inputBufferSize;	//!< size of display buffer
	uint8_t inputMaxSize;		//!< input max size
	int inputPos;				//!< current input position
	char inputLastKey;			//!< last key pressed (0 if none)
	/// @} 

public:
	uint8_t currentKeyRow;		//!< active key row
	uint8_t currentKeyCol;		//!< active key column
	char currentKey();			//!< active key
	void init();				//!< init on default pin
	void init(int input);		//!< init on user pin
	void scanKey(uint8_t col);	//!< keyboard scanner

	/// @name multidigit numeric input
	/// Numeric input on display buffer
	/// @{
	void numericInputInit(char buffer[], uint8_t bufferSize);					//!< multidigit numeric input init routine
	void numericInputInit(char buffer[], uint8_t bufferSize, uint8_t maxLen);	//!< multidigit numeric input init routine
	void numericInputReInit();													//!< input restart
	char numericInput();														//!< multidigit numeric input
	/// @} 
};

extern Keyboard16keysClass Keyboard16keys;

#endif
