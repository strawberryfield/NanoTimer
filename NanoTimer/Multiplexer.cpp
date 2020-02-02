/// @file 
/// Multiplexer class definition.
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

#include "Multiplexer.h"

void MultiplexerClass::init(uint8_t pins[], uint8_t muxsize)
{
	pinList = pins;
	size = muxsize;
	for (int j = 0; j < size; j++) {
		pinMode(pinList[j], OUTPUT);
	}
	active = 0;
}

void MultiplexerClass::activateCurrent()
{
	digitalWrite(pinList[active], HIGH);
}

void MultiplexerClass::deactivateCurrent()
{
	digitalWrite(pinList[active], LOW);
}

void MultiplexerClass::next()
{
	if (active == size-1) {
		active = 0;
	}
	else {
		active++;
	}
}


MultiplexerClass Multiplexer;

