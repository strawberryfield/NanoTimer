/// @file 
/// Main Arduino entry point.
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
/// @name Wiring diagram
/// @image html BaseDisplay_bb.jpg
///

#include "Multiplexer.h"
#include "Keyboard16keys.h"
#include "NanoTimerClass.h"
#include "Timer.h"
#include "Buzzer.h"

/// @name Wiring
/// Pin 11: Enable dots  
/// Pin 12: Enable digit 1  
/// Pin A1: Enable digit 2  
/// Pin A2: Enable digit 3  
/// Pin A3: Enable digit 4  
uint8_t cathodes[] = {
	12, A1, A2, A3, 11
};

/** the setup function runs once when you press reset or power the board */
void setup() {
	NanoTimer.init();
	Multiplexer.init(cathodes, DISPLAY_SIZE + 1);
	Keyboard16keys.init();
	Timer.init(250);	    //Base interrupt frequency 250Hz
	Keyboard16keys.numericInputInit(NanoTimer.display, DISPLAY_SIZE);
	Buzzer.init(7);
	Buzzer.beepInit(NoteClass('A', ' ', 4, 300), 150);   // Diapason standard frequency A4 = 440Hz
}

/** the loop function runs over and over again until power down or reset */
void loop() {
	NanoTimer.loop();
	Buzzer.loop();
}

/// timer compare interrupt service routine
/// Called every 4 milliseconds
ISR(TIMER1_COMPA_vect) { 
	NanoTimer.counterTick();
	NanoTimer.blinking();
	Multiplexer.deactivateCurrent();
	Multiplexer.next();
	NanoTimer.refresh(Multiplexer.active);
	Multiplexer.activateCurrent();
	Keyboard16keys.scanKey(Multiplexer.active);
}
