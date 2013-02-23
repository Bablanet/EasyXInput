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

#ifndef _EZX_EVENT_HPP_
#define _EZX_EVENT_HPP_

#define EZX_PRESS      0x0100
#define EZX_RELEASE    0x0200
#define EZX_ANALOG     0x0300
#define EZX_CONNECT    0x0400
#define EZX_DISCONNECT 0x0500

namespace ezx
{
    /*
     * class Event
     * A generic catch-all object for any possible event.
     * The angle member is only used for analog events (the triggers and sticks), so it has its
     * own constructor. If not in use (i.e. a non-analog event) then angle will always equal zero.
     * */
    struct Event
    {
        short type;
        short controllerId;
        short angle;
        int   which;

        Event();
        Event(short controllerId, short type, int which);
        Event(short controllerId, short type, int which, short angle);
    };
}

#endif