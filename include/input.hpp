/*
* EasyXInput
* https://github.com/TylerOBrien/EasyXInput
*
* Copyright (c) 2012 Tyler O'Brien
*
* Permission is hereby granted, free of charge, to any person obtaining
* a copy of this software and associated documentation files (the
* "Software"), to deal in the Software without restriction, including
* without limitation the rights to use, copy, modify, merge, publish,
* distribute, sublicense, and/or sell copies of the Software, and to
* permit persons to whom the Software is furnished to do so, subject to
* the following conditions:
*
* The above copyright notice and this permission notice shall be
* included in all copies or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
* EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
* MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
* NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
* LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
* OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
* WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
* */

#ifndef _EZX_INPUT_HPP_
#define _EZX_INPUT_HPP_

#include <windows.h>
#include <XInput.h>

#include "connectionstates.hpp"
#include "event.hpp"

#define EZX_A        XINPUT_GAMEPAD_A
#define EZX_B        XINPUT_GAMEPAD_B
#define EZX_X        XINPUT_GAMEPAD_X
#define EZX_Y        XINPUT_GAMEPAD_Y
#define EZX_UP       XINPUT_GAMEPAD_DPAD_UP
#define EZX_DOWN     XINPUT_GAMEPAD_DPAD_DOWN
#define EZX_LEFT     XINPUT_GAMEPAD_DPAD_LEFT
#define EZX_RIGHT    XINPUT_GAMEPAD_DPAD_RIGHT
#define EZX_START    XINPUT_GAMEPAD_START   
#define EZX_BACK     XINPUT_GAMEPAD_BACK
#define EZX_LBUMPER  XINPUT_GAMEPAD_LEFT_SHOULDER
#define EZX_RBUMPER  XINPUT_GAMEPAD_RIGHT_SHOULDER
#define EZX_LTHUMB   XINPUT_GAMEPAD_LEFT_THUMB
#define EZX_RTHUMB   XINPUT_GAMEPAD_RIGHT_THUMB
#define EZX_LTHUMB_X 0x10AA
#define EZX_LTHUMB_Y 0x20AA
#define EZX_RTHUMB_X 0x10BB
#define EZX_RTHUMB_Y 0x20BB
#define EZX_LTRIGGER 0x10CC
#define EZX_RTRIGGER 0x20CC

namespace ezx
{   
    void DetectInput();
    void FlushEvents();

    bool GetConnectionStates(ezx::ConnectionStates *states);
    bool GetEvent(Event *event);

    void SetVibrationAmount(short controllerID, WORD vibration);
    void SetVibrationAmount(short controllerID, WORD leftVibration, WORD rightVibration);
    void SetVibrationLevel(short controllerID, float vibrationPercentage);
    void SetVibrationLevel(short controllerID, float leftVibrationPercentage, float rightVibrationPercentage);
}

#endif