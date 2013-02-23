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

#include "connectionstates.hpp"

namespace ezx
{
    /*
     * Constructor
     *
     * */
    ConnectionStates::ConnectionStates()
        : first(false),
          second(false),
          third(false),
          fourth(false)
    {
        /* Intentionally left blank. */
    }

    /*
     * Constructor
     *
        * @param  The connection state of the first controller.
        * @param  The connection state of the second controller.
        * @param  The connection state of the third controller.
        * @param  The connection state of the fourth controller.
     * */
    ConnectionStates::ConnectionStates(
        bool first,
        bool second,
        bool third,
        bool fourth)
        : first(first),
          second(second),
          third(third),
          fourth(fourth)
    {
        /* Intentionally left blank. */
    }

    /*
     * operator [] returns bool
     *
        * @param  The ID of the controller to get the state of (i.e. the integers 0-3)
     * */
    bool
    ConnectionStates::operator [] (
        int index) const
    {
        switch (index)
        {
        case 0:  return first;
        case 1:  return second;
        case 2:  return third;
        case 3:  return fourth;
        default: return false;
        }
    }
}