/// @file 
/// Timer manager class implementation.
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

#include "Timer.h"

// Inits timer 2
void TimerClass::init(int frequency)
{
    // 16MHz / 64 = 250 KHz after prescaler
    noInterrupts();
    // reset registers
    TCCR1A = 0;
    TCCR1B = 0;
    TCNT1 = 0;

    OCR1A = 250000 / frequency;  // Counter after prescaler
    TCCR1B |= (1 << WGM12);   // CTC mode
    TCCR1B |= (1 << CS11) | (1 << CS10);    // 64 prescaler 
    TIMSK1 |= (1 << OCIE1A);  // enable timer compare interrupt
    interrupts();
}


TimerClass Timer;

