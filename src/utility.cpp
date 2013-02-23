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

#include "utility.hpp"
#include "input.hpp"

#include <algorithm>

namespace ezx
{
    /* IsButtonCombo() returns bool
     *
        * @param  The button IDs to compare against the combo.
        * @param  The button IDs that make up the combo to look for.
     *
     * This version of "IsButtonCombo" uses a vector of ints to contain the combo
     * of button IDs to check against.
     * */
    bool IsButtonCombo(
        const std::vector<int> &buttonIds,
        const std::vector<int> &comboIds)
    {
        bool result = false;

        for (std::vector<int>::const_iterator itr = buttonIds.begin(); itr != buttonIds.end(); itr++)
        {
            if (std::find(buttonIds.begin(), buttonIds.end(), *itr) != buttonIds.end()) {
                result = true;
            } else {
                return false;
            }
        }

        return result;
    }

    /* IsButtonCombo() returns bool
     *
        * @param  The button IDs to compare against the combo.
        * @param  The button IDs that make up the combo to look for.
     *
     * This version of "IsButtonCombo" uses a string to contain the combo of button IDs
     * to check against. An example is "abx" would mean the buttons A, B, and X.
     * */
    bool IsButtonCombo(
        const std::vector<int> &buttonIds,
        const char *combo)
    {
        bool result = false;
        std::string::size_type len = strlen(combo);

        for (std::string::size_type i=0; i<len; ++i)
        {
            if (std::find(buttonIds.begin(), buttonIds.end(), CharToId(combo[i])) != buttonIds.end()) {
                result = true;
            } else {
                return false;
            }
        }

        return result;
    }

    /*
     * IdToChar() returns char
     *
        * @param  The button ID to convert to a char.
     *
     * Converts the passed button ID to its char equivalent (in the context of EasyXInput).
     * Due to the limit of having only a single character for the representation
     * some of the results are a bit "random".
     * */
    char IdToChar(
        int buttonId)
    {
        switch (buttonId)
        {
            case XINPUT_GAMEPAD_A: return 'a';
            case XINPUT_GAMEPAD_B: return 'b';
            case XINPUT_GAMEPAD_X: return 'x';
            case XINPUT_GAMEPAD_Y: return 'y';
            case XINPUT_GAMEPAD_DPAD_LEFT: return 'l';
            case XINPUT_GAMEPAD_DPAD_RIGHT: return 'r';
            case XINPUT_GAMEPAD_DPAD_UP: return 'u';
            case XINPUT_GAMEPAD_DPAD_DOWN: return 'd';
            case XINPUT_GAMEPAD_LEFT_SHOULDER: return 'q';
            case XINPUT_GAMEPAD_RIGHT_SHOULDER: return 'p';
            case XINPUT_GAMEPAD_START: return 'm';
            case XINPUT_GAMEPAD_BACK: return 's';
            default: return '\0';
        }
    }

    /*
     * IdToChar() returns const char*
     *
        * @param  The button ID to convert to a string.
     *
     * Returns the same values as IdToChar() but as a c-string instead of a char.
     * */
    const char *IdToString(
        int buttonId)
    {
        switch (buttonId)
        {
            case XINPUT_GAMEPAD_A: return "a";
            case XINPUT_GAMEPAD_B: return "b";
            case XINPUT_GAMEPAD_X: return "x";
            case XINPUT_GAMEPAD_Y: return "y";
            case XINPUT_GAMEPAD_DPAD_LEFT: return "l";
            case XINPUT_GAMEPAD_DPAD_RIGHT: return "r";
            case XINPUT_GAMEPAD_DPAD_UP: return "u";
            case XINPUT_GAMEPAD_DPAD_DOWN: return "d";
            case XINPUT_GAMEPAD_LEFT_SHOULDER: return "q";
            case XINPUT_GAMEPAD_RIGHT_SHOULDER: return "p";
            case XINPUT_GAMEPAD_LEFT_THUMB: return "?"; //TODO: Figure out good value for this button.
            case XINPUT_GAMEPAD_RIGHT_THUMB: return "?"; //TODO: Figure out good value for this button.
            case XINPUT_GAMEPAD_START: return "m";
            case XINPUT_GAMEPAD_BACK: return "s";
            default: return "\0";
        }
    }

    /*
     * IdToName() returns const char*
     *
        * @param  The button ID to convert to its name.
     *
     * Converts the passed ID to its full textual name.
     * This function is really only useful for debugging purposes.
     * */
    const char *IdToName(
        int buttonId)
    {
        switch (buttonId)
        {
            case XINPUT_GAMEPAD_A: return "A";
            case XINPUT_GAMEPAD_B: return "B";
            case XINPUT_GAMEPAD_X: return "X";
            case XINPUT_GAMEPAD_Y: return "Y";
            case XINPUT_GAMEPAD_DPAD_LEFT: return "DPAD Left";
            case XINPUT_GAMEPAD_DPAD_RIGHT: return "DPAD Right";
            case XINPUT_GAMEPAD_DPAD_UP: return "DPAD Up";
            case XINPUT_GAMEPAD_DPAD_DOWN: return "DPAD Down";
            case XINPUT_GAMEPAD_LEFT_SHOULDER: return "Left Bumper";
            case XINPUT_GAMEPAD_RIGHT_SHOULDER: return "Right Bumper";
            case XINPUT_GAMEPAD_LEFT_THUMB: return "Left Thumb";
            case XINPUT_GAMEPAD_RIGHT_THUMB: return "Right Thumb";
            case XINPUT_GAMEPAD_START: return "Start";
            case XINPUT_GAMEPAD_BACK: return "Back";
            case EZX_LTRIGGER: return "Left Trigger";
            case EZX_RTRIGGER: return "Right Trigger";
            case EZX_LTHUMB_X: return "Left Thumb X";
            case EZX_LTHUMB_Y: return "Left Thumb Y";
            case EZX_RTHUMB_X: return "Right Thumb X";
            case EZX_RTHUMB_Y: return "Right Thumb Y";
            default: return "\0";
        }
    }

    /*
     * IdsToString() returns std::string
     *
        * @param  The button IDs to conver to an std::string
     *
     * Converts the vector of button IDs to a string containing the char
     * equivalents of said button IDs. Is basically just a "long form" version
     * of IdToChar().
     * */
    std::string IdsToString(
        const std::vector<int> &buttonIds)
    {
        std::string result;

        for (std::vector<int>::const_iterator itr = buttonIds.begin(); itr != buttonIds.end(); itr++) {
            result.push_back(IdToChar(*itr));
        }

        return result;
    }

    /*
     * CharToId() returns int
     *
        * @param  The char representation of the button ID.
     *
     * Converts a passed char to its equivalent representation as an integer.
     * Is the exact inverse of IdToChar().
     * */
    int CharToId(
        char keyCode)
    {
        switch (keyCode)
        {
            case 'a': return XINPUT_GAMEPAD_A;
            case 'b': return XINPUT_GAMEPAD_B;
            case 'x': return XINPUT_GAMEPAD_X;
            case 'y': return XINPUT_GAMEPAD_Y;
            case 'l': return XINPUT_GAMEPAD_DPAD_LEFT;
            case 'r': return XINPUT_GAMEPAD_DPAD_RIGHT;
            case 'u': return XINPUT_GAMEPAD_DPAD_UP;
            case 'd': return XINPUT_GAMEPAD_DPAD_DOWN;
            case 'q': return XINPUT_GAMEPAD_LEFT_SHOULDER;
            case 'p': return XINPUT_GAMEPAD_RIGHT_SHOULDER;
            case 'm': return XINPUT_GAMEPAD_START;
            case 's': return XINPUT_GAMEPAD_BACK;
            default:  return 0;
        }
    }

    /*
     * NameToId() returns int
     *
        * @param  The C-string name representation of the button.
     *
     * Converts a passed button name to its equivalent representation as an integer.
     * Is the exact inverse of IdToName().
     * */
    int NameToId(
        const char *name)
    {
        int result = 0;

        if (strcmp(name, "A") == 0) {
            result = EZX_A;
        } else if (strcmp(name, "B") == 0) {
            result = EZX_B;
        } else if (strcmp(name, "X") == 0) {
            result = EZX_X;
        } else if (strcmp(name, "Y") == 0) {
            result = EZX_Y;
        } else if (strcmp(name, "Y") == 0) {
            result = EZX_Y;
        } else if (strcmp(name, "DPAD Left") == 0) {
            result = EZX_LEFT;
        } else if (strcmp(name, "DPAD Right") == 0) {
            result = EZX_RIGHT;
        } else if (strcmp(name, "DPAD Up") == 0) {
            result = EZX_UP;
        } else if (strcmp(name, "DPAD Down") == 0) {
            result = EZX_DOWN;
        } else if (strcmp(name, "Left Bumper") == 0) {
            result = EZX_LBUMPER;
        } else if (strcmp(name, "Right Bumper") == 0) {
            result = EZX_RBUMPER;
        } else if (strcmp(name, "Left Thumb") == 0) {
            result = EZX_LTHUMB;
        } else if (strcmp(name, "Right Thumb") == 0) {
            result = EZX_RTHUMB;
        } else if (strcmp(name, "Start") == 0) {
            result = EZX_START;
        } else if (strcmp(name, "Back") == 0) {
            result = EZX_BACK;
        }

        return result;
    }

    /* StringToIds() returns std::vector<int>
     *
        * @param  C-string of button IDs to convert to integers.
     *
     * Takes C-string of button IDs which are converted to their corresponding
     * integer IDs that will inversely match the values returned by
     * IdToChar() and IdToString().
     * */
    std::vector<int> StringToIds(
        const char *keyCodes)
    {
        std::vector<int>::size_type len = strlen(keyCodes);
        std::vector<int> vec(len);

        for (std::vector<int>::size_type i = 0; i < len; ++i) {
            vec[i] = CharToId(keyCodes[i]);
        }

        return vec;
    }
}