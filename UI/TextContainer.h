#include "BasicContainer.h"
#include "../SF/RsrcDispatcher.h"

namespace UI{
    struct TextContainer : BasicContainer{
        sf::Text textRender;
        sf::Vector2f textOffset;

        void resetPosition(const sf::Vector2f& newPos) override{
            bodyRender.setPosition(newPos);
            textRender.setPosition(newPos + textOffset);

            positionUpdated = true;
        }

        void createText(const std::string& textString, float charSize, const sf::Vector2f& pos, const sf::Color& color){
            textRender.setString(textString);
            textRender.setFont(SF::RsrcDispatcher::stdFont);
            textRender.setCharacterSize(charSize);
            textRender.setPosition(pos + textOffset);
            textRender.setFillColor(color);
        };
    };
};