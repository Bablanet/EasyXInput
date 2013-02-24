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

#include "input.hpp"

#include <algorithm>
#include <queue>

/*
 * Some macros that make the code below a little easier to read.
 * All of them are used for creating arrays.
 * */
#define EZX_ANALOG_STICK_ANGLES(state) {(state).Gamepad.sThumbLX, (state).Gamepad.sThumbLY, (state).Gamepad.sThumbRX, (state).Gamepad.sThumbRY}
#define EZX_TRIGGER_ANGLES(state)      {(state).Gamepad.bLeftTrigger, (state).Gamepad.bRightTrigger}
#define EZX_BUTTONS                    {XINPUT_GAMEPAD_START,XINPUT_GAMEPAD_BACK,XINPUT_GAMEPAD_DPAD_UP,XINPUT_GAMEPAD_DPAD_DOWN,XINPUT_GAMEPAD_DPAD_LEFT,XINPUT_GAMEPAD_DPAD_RIGHT,XINPUT_GAMEPAD_A,XINPUT_GAMEPAD_B,XINPUT_GAMEPAD_X,XINPUT_GAMEPAD_Y,XINPUT_GAMEPAD_LEFT_THUMB,XINPUT_GAMEPAD_RIGHT_THUMB,XINPUT_GAMEPAD_LEFT_SHOULDER,XINPUT_GAMEPAD_RIGHT_SHOULDER}
#define EZX_ANALOG_STICK_DEADZONES     {XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE, XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE, XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE, XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE}
#define EZX_ANALOG_ANGLES_ARRAY_INIT   {{0,0,0,0,0,0}, {0,0,0,0,0,0}, {0,0,0,0,0,0}, {0,0,0,0,0,0}}
#define EZX_BUTTONS_DOWN_ARRAY_INIT    {EZX_FALSE_ARRAY, EZX_FALSE_ARRAY, EZX_FALSE_ARRAY, EZX_FALSE_ARRAY}
#define EZX_FALSE_ARRAY                {false, false, false, false, false, false, false, false, false, false, false, false, false, false}
#define EZX_CONNECTIONS_ARRAY_INIT     {false, false, false, false}

namespace ezx
{
    /*
     * Arrays of IDs/values that are used by the detection functions.
     * */
    const int BUTTONS[14] = EZX_BUTTONS;
    const int DEADZONES[4] = EZX_ANALOG_STICK_DEADZONES;

    /*
     * The main event queue.
     * Is populated by the Detect functions below.
     * */
    std::queue<Event> eventQueue;

    /*
     * Arrays of statuses that are used by the detection functions.
     * Each array is two-dimensional; one for each of the four controllers.
     * */
    namespace status
    {
        short analogAngles[4][6] = EZX_ANALOG_ANGLES_ARRAY_INIT;
        bool  controllersDetected[4];
        bool  buttonsDown[4][14];
    }

    /*
     * AnalogAngleIDToButtonID() returns int
     *
        * @param  The ID of the analog button.
     *
     * Each analog is given a unique ID (which are used for getting/setting values
     * from arrays) and this function converts those analog IDs to their equivalent button IDs.
     * */
    int AnalogAngleIDToButtonID(
        short analogID)
    {
        switch (analogID)
        {
        case 0:  return EZX_LTRIGGER;
        case 1:  return EZX_RTRIGGER;
        case 2:  return EZX_LTHUMB_X;
        case 3:  return EZX_LTHUMB_Y;
        case 4:  return EZX_RTHUMB_X;
        case 5:  return EZX_RTHUMB_Y;
        default: return -1;
        }
    }

    /*
     * DetectConnection() returns nothing
     *
        * @param  The ID of the controller to detect a connection for.
     *
     * Detects if the controller determined by the passed ID just connected.
     * If the controller is already connected, or not connected at all,
     * this function will do nothing.
     * */
    inline void DetectConnection(
        short controllerID)
    {
        if (status::controllersDetected[controllerID] == false)
        {
            status::controllersDetected[controllerID] = true;
            eventQueue.push(Event(controllerID, EZX_CONNECT, controllerID));
        }
    }

    /*
     * DetectDisconnection() returns nothing
     *
        * @param  The ID of the controller to detect a disconnection for.
     *
     * Detects if the controller determined by the passed ID just disconnected.
     * If the controller is already disconnected or connected this function will do nothing.
     * */
    inline void DetectDisconnection(
        short controllerID)
    {
        if (status::controllersDetected[controllerID])
        {
            status::controllersDetected[controllerID] = false;
            eventQueue.push(Event(controllerID, EZX_DISCONNECT, controllerID));
        }
    }

    /*
     * DetectPressedAnalog()
     *
        * @param  The controller ID to detect analog presses for.
        * @param  The analog ID to detect. Will be an integer between 2-5.
        * @param  The current angle of the analog.
        * @param  Pointer to the XINPUT state to be used.
     *
     * */
    inline void DetectPressedAnalog(
        short controllerID,
        short analogAngleID,
        short angle,
        PXINPUT_STATE state)
    {
        int buttonID = AnalogAngleIDToButtonID(analogAngleID);

        if (status::analogAngles[controllerID][analogAngleID] != angle) {
            eventQueue.push(Event(controllerID, EZX_ANALOG, buttonID, angle));
        }

        status::analogAngles[controllerID][analogAngleID] = angle;
        eventQueue.push(Event(controllerID, EZX_PRESS, buttonID, angle));
    }

    /*
     * DetectReleasedAnalog()
     *
        * @param  The controller ID to detect analog releases for.
        * @param  The analog ID to detect. Will be an integer between 2-5.
        * @param  The current angle of the analog.
        * @param  Pointer to the XINPUT state to be used.
     *
     * */
    inline void DetectReleasedAnalog(
        short controllerID,
        short analogAngleID,
        PXINPUT_STATE state)
    {
        int buttonID = AnalogAngleIDToButtonID(analogAngleID);

        if (status::analogAngles[controllerID][analogAngleID]) {
            eventQueue.push(Event(controllerID, EZX_RELEASE, buttonID));
        }

        status::analogAngles[controllerID][analogAngleID] = 0;
    }

    /*
     * DetectTriggers() returns nothing
     *
        * @param  The ID of the controller to detect the trigger angles for.
        * @param  Pointer to the XINPUT state object.
     *
     * */
    void DetectTriggers(
        short controllerID,
        PXINPUT_STATE state)
    {
        unsigned char angles[2] = EZX_TRIGGER_ANGLES(*state);

        for (char i = 0; i < 2; i++)
        {
            if (angles[i] > 0) {
                DetectPressedAnalog(controllerID, i, angles[i], state);
            } else {
                DetectReleasedAnalog(controllerID, i, state);
            }
        }
    }

    /*
     * DetectAnalogSticks() returns nothing
     * 
        * @param
        * @param
     *
     * */
    void DetectAnalogSticks(
        short controllerID,
        PXINPUT_STATE state)
    {
        short angles[4] = EZX_ANALOG_STICK_ANGLES(*state);

        for (char i = 0; i < 4; i++)
        {
            char j = i+2;

            if (angles[i] >= DEADZONES[i] || angles[i] <= -DEADZONES[i]) {
                DetectPressedAnalog(controllerID, j, angles[i], state);
            } else {
                DetectReleasedAnalog(controllerID, j, state);
            }
        }
    }

    /*
     * DetectButtons()
     *
        * @param  The controller ID to detect buttons for.
        * @param  Pointer to the XINPUT state to be used.
     *
     * */
    void DetectButtons(
        short controllerID,
        PXINPUT_STATE state)
    {
        /*
         * Iterate once for each of these fourteen buttons:
         * A, B, X, Y, DPAD-UP, DPAD-DOWN, DPAD-LEFT, DPAD-RIGHT,
         * START, BACK, LEFT SHOULDER, RIGHT SHOULDER,
         * LEFT THUMB STICK, RIGHT THUMB STICK
         * */
        for (char i = 0; i < 14; ++i)
        {
            if (state->Gamepad.wButtons & BUTTONS[i])
            {
                status::buttonsDown[controllerID][i] = true;
                eventQueue.push(Event(controllerID, EZX_PRESS, BUTTONS[i]));
            }
            else
            {
                if (status::buttonsDown[controllerID][i]) {
                    eventQueue.push(Event(controllerID, EZX_RELEASE, BUTTONS[i]));
                }

                status::buttonsDown[controllerID][i] = false;
            }
        }
    }

    /*
     * DetectInput() returns nothing
     *
     * Performs an update on the controller detection.
     * This is the function that builds the events used in the message loop.
     * */
    void DetectInput()
    {
        XINPUT_STATE state;
        ZeroMemory(&state, sizeof XINPUT_STATE);

        /* 
         * Iterate once for each possible controller.
         * The "i" variable is used as the controller index.
         * */
        for (char i = 0; i < 4; ++i)
        {
            if (XInputGetState(i, &state) == ERROR_SUCCESS)
            {
                DetectConnection(i);
                DetectAnalogSticks(i, &state);
                DetectTriggers(i, &state);
                DetectButtons(i, &state);
            } else {
                DetectDisconnection(i);
            }
        }
    }

    /*
     * FlushEvents() returns nothing
     * Removes all current Event objects in the event queue.
     * */
    void FlushEvents()
    {
        std::swap(eventQueue, std::queue<Event>());
    }

    /*
     * GetControllerConnectionStatuses() returns bool
     *
        * @param  The ConnectionStates object to store the results in.
     *
     * Polls each of the controllers to detect which are connected.
     * If the passed pointer is valid (i.e. non-NULL) then it will be filled
     * with the results of the polling.
     *
     * If any controllers are connected this will return true.
     * If no controllers are connected, or a NULL pointer is given, this will return false.
     * */
    bool GetConnectionStates(
        ConnectionStates *states)
    {
        if (states == NULL) {
            return false;
        }
        else
        {
            XINPUT_STATE state;
            ZeroMemory(&state, sizeof XINPUT_STATE);

            states->first = (XInputGetState(0,&state)==ERROR_SUCCESS);
            states->second = (XInputGetState(1,&state)==ERROR_SUCCESS);
            states->third = (XInputGetState(2,&state)==ERROR_SUCCESS);
            states->fourth = (XInputGetState(3,&state)==ERROR_SUCCESS);

            return states->first || states->second || states->third || states->fourth;
        }
    }

    /*
     * GetEvent() returns bool
     *
         * @param  Pointer to the Event object to provide data to.
     *
     * The function which controls the message loop.
     * Will only ever return true if there are events to be handled.
     * */
    bool GetEvent(
        Event *event)
    {
        if (event == NULL) {
            return false;
        }
        else
        {
            std::queue<Event>::size_type previousSize = eventQueue.size();

            if (previousSize > 0)
            {
                *event = eventQueue.front();
                eventQueue.pop();
            }

            return previousSize != eventQueue.size();
        }
    }

    /*
     * SetVibrationAmount() returns nothing
     * */
    void SetVibrationAmount(
        short controllerID,
        WORD vibration)
    {
        SetVibrationAmount(controllerID, vibration, vibration);
    }

    /*
     * SetVibrationAmount() returns nothing
     * */
    void SetVibrationAmount(
        short controllerID,
        WORD leftVibration,
        WORD rightVibration)
    {
        XINPUT_VIBRATION vibrate;
        ZeroMemory(&vibrate, sizeof XINPUT_VIBRATION);

        vibrate.wLeftMotorSpeed = leftVibration;
        vibrate.wRightMotorSpeed = rightVibration;

        XInputSetState(controllerID, &vibrate);
    }

    /*
     * SetVibrationAmount() returns nothing
     * */
    void SetVibrationLevel(
        short controllerID,
        float vibrationPercentage)
    {
        WORD vibration = (WORD)(65535.0f * vibrationPercentage);
        SetVibrationAmount(controllerID, vibration, vibration);
    }
}