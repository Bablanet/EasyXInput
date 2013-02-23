EasyXInput
----------
A C++ framework for detecting input from controllers with XInput.  
This project was created to remove the need to write boilerplate code to be able to use XInput in situations that are non trivial, for example detecting when a button was been _released_ rather than just detecting if a button is being held down. No setup code is required for use; just include the __easyxinput.hpp__ header, link the XInput library, and you're ready to go.

How to Use
----------
* [Basic Example](#basic-example)
* [Parsing Events](#parsing-events)
* [Detecting Connections and Disconnections](#detecting-connections-and-disconnections)
* [Detecting Button Combos](#detecting-button-combos)

Basic Example
----------
```cpp
#include <iostream>
#include <easyxinput/easyxinput.hpp>

int main() {
    while (true) {
        ezx::Event event;

        ezx::DetectInput();
        while (ezx::GetEvent(&event)) {
            std::cout << "Event Detected" << std::endl;
        }
    }
}
```

Parsing Events
----------
There are five types of events in EasyXInput:  

```  CONNECT     ```  Fires when a controller connection is detected.  
```  DISCONNECT  ```  Fires when a controller disconnection is detected.  
```  PRESS       ```  Fires repeatadly when a button, analog stick or trigger is pressed. This includes moving the analog sticks around.  
```  RELEASE     ```  Fires once when a button, analog stick or trigger is released.  
```  ANALOG      ```  Fires once whenever an analog stick or trigger is moved.

All of these events are parsed in a way that is comparable to the Windows API or X11: use a "get function" to store the event information inside of an object or some sort, and then perform a switch on the event type to determine what kind of event has been fired.  
The following is an example that listens for every possible event from any controller:

```cpp
#include <iostream>
#include <easyxinput/easyxinput.hpp>

int main() {
    while (true) {
        ezx::Event event;

        ezx::DetectInput();
        while (ezx::GetEvent(&event)) {
            switch (event.type) {
            case EZX_CONNECT:
                std::cout << "Connection Event" << std::endl;
                break;
            case EZX_DISCONNECT:
                std::cout << "Disconnection Event" << std::endl;
                break;
            case EZX_PRESS:
                std::cout << "Press Event" << std::endl;
                break;
            case EZX_RELEASE:
                std::cout << "Release Event" << std::endl;
                break;
            case EZX_ANALOG:
                std::cout << "Analog Event" << std::endl;
                break;
            }
        }
    }
}
```

Detecting Connections and Disconnections
----------
Controller connections/disconnections can be detected in two different ways with EasyXInput.  
The first is to use the __ezx::GetConnectionStates__ created function specifically for that purpose, and the second is to listen for the connection and disconnection events.

Example #1  
```cpp
#include <iostream>
#include <easyxinput/easyxinput.hpp>

int main() {
    ezx::ConnectionStates states;
    ezx::GetConnectionStates(&states);

    if (states[0]) std::cout << "Controller #1 Detected" << std::endl;
    if (states[1]) std::cout << "Controller #2 Detected" << std::endl;
    if (states[2]) std::cout << "Controller #3 Detected" << std::endl;
    if (states[3]) std::cout << "Controller #4 Detected" << std::endl;
}
```

Example #2  
```cpp
#include <iostream>
#include <easyxinput/easyxinput.hpp>

int main() {
    while (true) {
        ezx::Event event;

        ezx::DetectInput();
        while (ezx::GetEvent(&event)) {
            switch (event.type) {
            case EZX_CONNECT:
                std::cout << "Controller #" << (event.controllerId+1) << " Connected" << std::endl;
                break;
            case EZX_DISCONNECT:
                std::cout << "Controller #" << (event.controllerId+1) << " Disconnected" << std::endl;
                break;
            }
        }
    }
}
```

Detecting Button Combos
----------
Button combos in EasyXInput are detected by comparing a vector of IDs against another vector of IDs (the latter of which representing the desired combo). It is up to the programmer to choose how the vector of IDs are built; EasyXInput will not record any button presses or releases for you.  
One way of determining if a button combo is being held is to do the following:

```cpp
#include <iostream>
#include <easyxinput/easyxinput.hpp>

int main() {
    std::vector<int> abxCombo;

    abxCombo.push_back(EZX_A);
    abxCombo.push_back(EZX_B);
    abxCombo.push_back(EZX_X);

    while (true) {
        ezx::Event event;
        std::vector<int> buttonsPressed[4]; // Create four vectors; one for each possible controller.

        ezx::DetectInput();
        while (ezx::GetEvent(&event)) {
            switch (event.type) {
            case EZX_PRESS:
                buttonsPressed[event.controllerId].push_back(event.which);
                break;
            }
        }

        for (int i = 0; i < 4; ++i) {
            if (ezx::IsButtonCombo(buttonsPressed[i], abxCombo)) {
                std::cout << "Controller #" << (i+1) << " is Pressing ABX Combo" << std::endl;
            }
        }
    }
}
```

In that example it is possible that the array of vectors is not necessary. Just like building the vector of IDs it is up to the programmer to determine which amount of controllers will be necessary to track. If it is known that only ever one single controller will ever be connected then a single vector could be used instead.