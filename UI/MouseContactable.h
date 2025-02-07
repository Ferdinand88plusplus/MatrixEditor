#pragma once
#include <SFML/Graphics.hpp>

#include "Collider.h"
#include "../SF/Input.h"
#include "../Palette.h"

namespace UI{
    
    enum ContactType{
        None,
        Floating,
        Pressed,
    };

    template<class collider_type>
    class MouseContactable {
    public:
        collider_type collider;

        inline ContactType getMouseContact(){
            sf::Vector2f mousePosition = SF::Input::curMousePos;

            if(!collider.isContains(mousePosition)){
                return ContactType::None;
            }

            if(SF::Input::lmbPress){
                return ContactType::Pressed;
            }

            return ContactType::Floating;
        };
    };

    static int contactType2PalID(ContactType contact){

        switch(contact){
            default:
                return Palette::ID::BtnNormal;
            case ContactType::Floating:
                return Palette::ID::BtnFloating;
            case ContactType::Pressed:
                return Palette::ID::BtnPressed;
        }
    };
};