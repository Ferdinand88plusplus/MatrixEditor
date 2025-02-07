#pragma once
#include "MouseContactable.h"
#include "TextContainer.h"
#include "ButtonBase.h"

#include "../SF/RsrcDispatcher.h"

namespace UI{
    class RectButton : public MouseContactable<RectCollider>, public TextContainer, public ButtonBase {
    public:

        ContactType update() override;

        void create(const sf::Vector2f& pos, const sf::Vector2f& size, const std::string& text);
    };
};