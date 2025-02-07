#include "ImgButton.h"

UI::ContactType UI::ImgButton::update()
{
    ContactType contactResult = getMouseContact();

    sf::Color& currentColor = Palette::Table[contactType2PalID(contactResult)];
    
    spriteRender.setColor(currentColor);

    SF::Window::window.draw(spriteRender);

    return contactResult;
}

void UI::ImgButton::create(const sf::Vector2f &pos, const std::string &imgname)
{
    if(!spriteTexture.loadFromFile(imgname)){
        ErrorDispatcher::Throw("UI::ImgButton", "Failed to load image '"+imgname+"'");
    }

    spriteRender.setPosition(pos);
    spriteRender.setTexture(spriteTexture);

    collider.position = pos;
    collider.size = (sf::Vector2f)spriteTexture.getSize();
}
