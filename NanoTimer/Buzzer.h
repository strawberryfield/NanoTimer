/// @file 
/// Buzzer manager class definition.
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

#ifndef _BUZZER_h
#define _BUZZER_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "pitches.h"
#include "Note.h"

///@brief
/// Buzzer manager
class BuzzerClass
{
 protected:
    uint8_t outPin;				//!< Pin for Tone output
	uint16_t beepFrequency;
	uint16_t beepDuration; 
	uint16_t beepPause;
	uint32_t oldMillis;			//!< Previous time storage

	///@brief
	/// Device status
	enum playStates {stop, note, pause};
	playStates status;

	///@brief
	/// Operating modes
	enum playModes {single, repeat};
	playModes mode;

 public:
	void init(uint8_t pin);				//!< Inits buzzer on specified pin
	void play(uint16_t frequency);		//!< Replacement of Tone function
	void play(uint16_t frequency, uint16_t duration);		//!< Plays note for specified duration
	void play(NoteClass note);
	void stopPlay();					//!< Replacement of NoTone function
	void loop();						//!< Function for main .ino loop

	void beepInit(uint16_t frequency, uint16_t duration, uint16_t pause);	//!< beeper parameters setting
	void beep(uint16_t frequency, uint16_t duration, uint16_t pause);		//!< starts beeper with parameters
	void beep();															//!< starts beeper with already set parameters 

	void song(char rtttl[]);
	void song(char rtttl[], bool repeat);
};

extern BuzzerClass Buzzer;

#endif
