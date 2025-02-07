#include <SFML/Graphics.hpp>

namespace UI{
    struct BasicContainer{
        bool positionUpdated = 0;

        sf::RectangleShape bodyRender;
        
        virtual void resetPosition(const sf::Vector2f& newPosition) {
            bodyRender.setPosition(newPosition);

            positionUpdated = true;
        }

        void createBody(const sf::Vector2f& pos, const sf::Vector2f& size, float thickness){
            bodyRender.setPosition(pos);
            bodyRender.setSize(size);
            bodyRender.setOutlineThickness(thickness);
        };
    };
};