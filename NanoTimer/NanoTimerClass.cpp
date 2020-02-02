/// @file 
/// NanoTimer class implementation.
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

#include "NanoTimerClass.h"
#include "Keyboard16keys.h"
#include "Buzzer.h"

void NanoTimerClass::init() {
    MX4_C301Class::init();
    counter = 0;
    prescaler = 0;
    currentStatus = states::stopped;
}

void NanoTimerClass::counterTick() {
    if (currentStatus == states::count_down || currentStatus == states::count_up)
    {
        if(++prescaler >= prescalerLimit) {
            prescaler = 0;
            if(currentStatus == states::count_down) {
                --counter;
            }
            else {
                ++counter;
            }
        }
    }    
}

void NanoTimerClass::buffer2counter() {
    counter = 0;
    if(dots && LED_8) {
        // with 1/10 sec detail
        if ((display[3] & 0xFF) != BLANK) {
            counter += display[3];
            if ((display[2] & 0xFF) != BLANK) {
                counter += display[2] * 10;  
                if ((display[1] & 0xFF) != BLANK) counter += display[1] * 100;
            }
        }
    }
    else {
        // mm:ss
        if ((display[3] & 0xFF) != BLANK) {
            counter += display[3];
            if ((display[2] & 0xFF) != BLANK) {
                counter += display[2] * 10;  
                if ((display[1] & 0xFF) != BLANK) {
                    counter += display[1] * 60;
                    if ((display[0] & 0xFF) != BLANK) counter += display[0] * 600;
                }
            }
        }
        counter *= 10;
    }
}

void NanoTimerClass::counter2buffer() {
    if (counter < 600) {
        // last minute with 1/10 sec detail
        write(counter);
        dots = LED_8;
    }
    else {
        // mm:ss 
        uint8_t mm = counter / 600;
        uint8_t ss = (counter % 600) / 10;

        display[3] = ss % 10;
        display[2] = ss / 10;
        display[1] = mm % 10;
        display[0] = (mm > 9 ? mm/10 : BLANK);
        dots = LED_67;
    }
}

void NanoTimerClass::stoppedHandler(char inkey) {
    switch (inkey)
    {
    case 'A':
        buffer2counter();
        currentStatus = states::count_up;
        break;
    case 'D':
        buffer2counter();
        currentStatus = states::count_down;
        break;  
    case 'C':
        clear();
        Keyboard16keys.init();  
    default:
        break;
    }
}

void NanoTimerClass::counterHandler(char inkey) {
    counter2buffer();
    if (inkey == 'B') {
        currentStatus = states::stopped;
        Keyboard16keys.numericInputReInit();
    }
    if(counter == 0 && currentStatus == states::count_down) {
        currentStatus = states::alarm;
        Buzzer.beep();
    }
}

void NanoTimerClass::alarmHandler(char inkey) {
    if(inkey == 'C') {
        Buzzer.stopPlay();
        clear();
        Keyboard16keys.numericInputInit(display, DISPLAY_SIZE);
    }
}

NanoTimerClass NanoTimer;
