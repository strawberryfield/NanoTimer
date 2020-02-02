/// @file 
/// Display manager for timer class definition.
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

#ifndef _NANOTIMERCLASS_h
#define _NANOTIMERCLASS_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
#include "WProgram.h"
#endif

#include "MX4_C301.h"

///@brief
/// States list
enum states {stopped, alarm, count_up, count_down };

///@brief 
/// NanoTimer manager
class NanoTimerClass : public MX4_C301Class
{
protected:
    uint8_t prescaler;                  //!< Prescaler counter
    uint8_t const prescalerLimit = 25;  //!< Prescaler ticks

    void buffer2counter();              //!< reads counter value from display
    void counter2buffer();              //!< writes counter value to display

public:
    uint16_t counter;                   
    states currentStatus;

    void init();
    void counterTick();
    void stoppedHandler(char inkey);
    void counterHandler(char inkey);
    void alarmHandler(char inkey);
};

extern NanoTimerClass NanoTimer;

#endif