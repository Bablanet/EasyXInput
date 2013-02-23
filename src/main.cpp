#include <iostream>
#include "easyxinput.hpp"

#pragma comment(lib, "xinput.lib")

int main() {
    while (true) {
        std::vector<int> buttons;
        ezx::Event e;

        ezx::DetectInput();
        while (ezx::GetEvent(&e)) {
            switch (e.type) {
            case EZX_PRESS:
                buttons.push_back(e.which);
                break;
            }
        }

        if (ezx::IsButtonCombo(buttons, "abx")) {
            printf("Combo 'abx'\n");
        }
    }
}