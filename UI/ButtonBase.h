#pragma once
#include "MouseContactable.h"
#include "../ErrorDispatcher.h"

namespace UI{
    struct ButtonBase {
        int pressCall = -1; // signal that will be sended if the button was pressed
        std::string hintText; // text that will be displayed if the button had state 'Floating' long enough

        virtual ContactType update(){
            ErrorDispatcher::Throw("UI::Button", "Pure virtual update() called");
            return ContactType::None;
        }
    };
};