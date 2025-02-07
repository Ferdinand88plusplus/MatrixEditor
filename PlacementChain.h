#pragma once
#include <vector>
#include "SF/Window.h"

enum Axis{
    X,
    Y,
};

// Fill line of screen with many UI Elements.
// -1.0f in 'size' parameter means 'use elemSize'
class PlacementChain{
public:

    float usedSpace = 0.0f;
    float elemSize = 0.0f;

    float altSpace = 0.0f; // for example, X position of elements on Y axis chain 

    Axis axis = Axis::X;

    // add element into chain
    void push(sf::Shape& shape, float size = -1.0f);

    sf::Vector2f getNextPos(float size = -1.0f);

    float getRemainingSpace();

};