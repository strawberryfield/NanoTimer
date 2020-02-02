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

#ifndef _MULTIPLEXER_h
#define _MULTIPLEXER_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

///@brief
/// Generic multiplexer class
class MultiplexerClass
{
 protected:
	 uint8_t* pinList;			//!< List of used pins
	 uint8_t size;				//!< Size of pins list

 public:
	uint8_t active;				//!< actual active pin
	void init(uint8_t pins[], uint8_t muxsize);		//!< mux init
	void activateCurrent();		//!< make current pin LOW
	void deactivateCurrent();	//!< make current pin HIGH
	void next();				//!< advances to next pin
};

extern MultiplexerClass Multiplexer;

#endif

