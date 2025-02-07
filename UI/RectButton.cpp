#include "RectButton.h"


UI::ContactType UI::RectButton::update()
{
    if(positionUpdated){
        collider.position = bodyRender.getPosition();

        positionUpdated = false;
    }

    ContactType contactResult = getMouseContact();

    sf::Color& currentColor = Palette::Table[contactType2PalID(contactResult)];
    
    bodyRender.setFillColor(currentColor);
    bodyRender.setOutlineColor(currentColor - sf::Color(40, 40, 40, 0));

    SF::Window::window.draw(bodyRender);
    SF::Window::window.draw(textRender);


    return contactResult;
}

void UI::RectButton::create(const sf::Vector2f &pos, const sf::Vector2f &size, const std::string &text)
{

    static const float thickness = -5;

    createBody(pos, size, thickness);
    textOffset = sf::Vector2f(-thickness, -thickness);
    createText(text, 20, pos, sf::Color::Black);

    bodyRender.setOutlineThickness(thickness);

    collider.position = pos;
    collider.size = size;
}