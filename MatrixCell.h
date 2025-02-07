#pragma once
#include <SFML/Graphics.hpp>
#include "UI/Collider.h"

typedef unsigned char uchar;

enum SlotType{
    None,
    Weapon,
    Terminator,
    Rig,
};

struct MatrixCellInfo{
    bool active = 0;
    uchar slotType = 0;
    uchar slotNum = 0;
};

struct MatrixCellGraphic{
    UI::CircleCollider collider;
    sf::Sprite mySprite;
    sf::Text myText;
    sf::Color myColor;

    void updateGraphic(MatrixCellInfo& src);
    void putSelectMask();
    void removeSelectMask();

private:

    sf::Color selectColor(MatrixCellInfo& src);
};
