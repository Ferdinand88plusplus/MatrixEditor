#include <SFML/Graphics.hpp>
#include <SFML/Window/VideoMode.hpp>

namespace SF{
    namespace Window{
        extern sf::RenderWindow window;
        extern sf::Vector2f resolution;

        void Open(int resX, int resY, int FPS);
    };
};