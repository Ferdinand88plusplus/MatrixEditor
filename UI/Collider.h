#pragma once
#include <SFML/Graphics.hpp>

#include "../SF/Math.h"

namespace UI{
    struct ColliderBase{

        sf::Vector2f position;
        

        virtual bool isContains(const sf::Vector2f& point) = 0;
    };

    struct RectCollider : ColliderBase{
        sf::Vector2f size;

        inline bool isContains(const sf::Vector2f& point) override {
            return 
                point.x >= position.x && point.y >= position.y && 
                point.x <= position.x + size.x && point.y <= position.y + size.y;
        };
    };

    struct CircleCollider : ColliderBase{
        float radius;

        inline bool isContains(const sf::Vector2f& point) override {
            return SF::Math::vecDist(position, point) <= radius;
        };
    };
};