/// @file 
/// Note class definition.
///
/// @author
/// copyright (c) 2020 Roberto Ceccarelli - Casasoft  
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

#ifndef _NOTE_h
#define _NOTE_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "pitches.h"

class NoteClass
{
 public:
	uint16_t frequency;
	uint16_t duration;

	NoteClass(uint16_t Frequency, uint16_t Duration) :
	frequency(Frequency), duration(Duration) { }

	NoteClass(char note, char diesis, uint8_t octave, uint16_t Duration);
};

#endif
