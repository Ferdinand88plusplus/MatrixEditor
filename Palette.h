#pragma once
#include <SFML/Graphics.hpp>

namespace Palette{
    enum ID{
        BtnNormal,
        BtnFloating,
        BtnPressed,

        ScrollListBody,

        ScrollListSliderBack,
        ScrollListSlider,

        EmptySlot,
        InventorySlot,
        WeaponSlot,
        TerminatorSlot,
        RigSlot,

        ErrorMsg,
        InfoMsg,

        enumSize,
    };

    enum Blocks{
        BlockBtns = BtnNormal,
        BlockScrollList = ScrollListBody,
        BlockScrollListSlider = ScrollListSliderBack,
        BlockSlots = EmptySlot,
        BlockMsgs = ErrorMsg,
    };

    static sf::Color Table[ID::enumSize] = {
        sf::Color(200, 200, 200),
        sf::Color(240, 240, 240),
        sf::Color(160, 160, 160),

        sf::Color(140, 140, 140),

        sf::Color(150, 150, 150),
        sf::Color(180, 180, 180),

        sf::Color(40, 40, 40),
        sf::Color(70, 90, 30),
        sf::Color(90, 40, 0),
        sf::Color(70, 70, 0),
        sf::Color(150, 40, 0),

        sf::Color(200, 0, 0),
        sf::Color(200, 200, 0),
    };
};