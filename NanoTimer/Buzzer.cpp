/// @file 
/// Buzzer manager class implementation.
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

#include "Buzzer.h"

// Inits buzzer
void BuzzerClass::init(uint8_t pin)
{
    outPin = pin;
    status = playStates::stop;
    mode = playModes::single;
}

void BuzzerClass::play(uint16_t frequency) {
    tone(outPin, frequency);
    oldMillis = millis();
}

void BuzzerClass::play(uint16_t frequency, uint16_t duration) {
    mode = playModes::single;
    status = playStates::note;
    beepDuration = duration;
    play(frequency);
}

void BuzzerClass::play(NoteClass note) {
    play(note.frequency, note.duration);
}

void BuzzerClass::stopPlay() {
    noTone(outPin);
    status = playStates::stop;
}

void BuzzerClass::loop() {
    switch (status)
    {
    case playStates::stop :
        break;
    case playStates::note :
        if(millis()-oldMillis >= beepDuration) {
            noTone(outPin);
            if(mode == playModes::single) {
                status = playStates::stop;
            }
            else {
                oldMillis = millis();
                status = playStates::pause;
            }            
        }
        break;
    case playStates::pause :
        if(millis()-oldMillis >= beepPause) {
            play(beepFrequency);
            status = playStates::note;
        }
        break;
    }

}

void BuzzerClass::beepInit(uint16_t frequency, uint16_t duration, uint16_t pause) {
    beepFrequency = frequency;
    beepDuration = duration;
    beepPause = pause;
}

void BuzzerClass::beep(uint16_t frequency, uint16_t duration, uint16_t pause) {
    beepInit(frequency, duration, pause);
    beep();
}

void BuzzerClass::beep() {
    mode = playModes::repeat;
    status = playStates::note;
    play(beepFrequency);
}

void BuzzerClass::song(char rtttl[]) {
    song(rtttl, false);
}

void BuzzerClass::song(char rtttl[], bool repeat) {

}

BuzzerClass Buzzer;
