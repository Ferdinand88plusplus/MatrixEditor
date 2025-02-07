#include "Input.h"

namespace InputMemory{
    bool lmbPress = 0, rmbPress = 0;
}

namespace SF::Input{
    sf::Vector2f curMousePos;
    float mouseWheelScroll;
    bool lmbPress, rmbPress;
}

void SF::Input::clear()
{
    curMousePos = {0,0};
    mouseWheelScroll = 0;
    lmbPress = rmbPress = 0;
}

void SF::Input::getFrameInput()
{
    if(SF::Window::window.hasFocus()){
        bool newLmbPress, newRmbPress;

        newLmbPress = sf::Mouse::isButtonPressed(sf::Mouse::Left);
        newRmbPress = sf::Mouse::isButtonPressed(sf::Mouse::Right);

        // set mouse buttons true only if its first frame of input
        lmbPress = newLmbPress && !InputMemory::lmbPress;
        rmbPress = newRmbPress && !InputMemory::rmbPress;

        InputMemory::lmbPress = newLmbPress;
        InputMemory::rmbPress = newRmbPress;
        


        curMousePos = (sf::Vector2f)sf::Mouse::getPosition(SF::Window::window);
    }
}
