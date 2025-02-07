#include <SFML/Graphics.hpp>

#include "Window.h"

namespace SF::Input{
    extern sf::Vector2f curMousePos;
    extern float mouseWheelScroll;
    extern bool lmbPress, rmbPress;

    void clear();

    void getFrameInput();
};