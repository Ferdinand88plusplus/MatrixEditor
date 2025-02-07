#include "Window.h"

namespace SF::Window{
    sf::RenderWindow window;
    sf::Vector2f resolution;
}

void SF::Window::Open(int resX, int resY, int FPS)
{
    resolution = sf::Vector2f(resX, resY);
    window.create(sf::VideoMode(resX, resY), "RevCfgEditor");
    window.setFramerateLimit(60);
};