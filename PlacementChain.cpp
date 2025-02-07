#include "PlacementChain.h"

#include "SF/Window.h"

void PlacementChain::push(sf::Shape &shape, float size)
{
    if(size == -1.0f){
        size = elemSize;
    }
    
    switch(axis){
    case Axis::X:
        shape.setPosition(usedSpace, altSpace);
        break;
    case Axis::Y:
        shape.setPosition(altSpace, usedSpace);
        break;
    }

    usedSpace += size;
}

sf::Vector2f PlacementChain::getNextPos(float size)
{
    if(size == -1.0f){
        size = elemSize;
    }

    float curPosition = usedSpace;
    usedSpace += size;

    switch(axis){
    case Axis::X:
        return {curPosition, altSpace};
    case Axis::Y:
        return {altSpace, curPosition};
    }
}

float PlacementChain::getRemainingSpace()
{
    switch(axis){
    case Axis::X:
        return SF::Window::resolution.x - usedSpace;
    case Axis::Y:
        return SF::Window::resolution.y - usedSpace;
    }

    return 0.0f;
}
