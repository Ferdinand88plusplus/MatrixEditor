#include "ScrollList.h"

#include <iostream>

//! ScrollListSlider

void UI::ScrollListSlider::update()
{
    sf::Vector2f mpos = SF::Input::curMousePos;

    if(bodyRender.getGlobalBounds().contains(mpos) && numSlidePoints){
        if(SF::Input::lmbPress){
            float pointHeight = (mpos - bodyRender.getPosition()).y;
            hasSlided = true;
            currentSlide = pointHeight / slideDelta;

            reTransposeSlider();
        }
    }

    SF::Window::window.draw(bodyRender);
    SF::Window::window.draw(sliderRender);
}

void UI::ScrollListSlider::resize(int newNumSlidePoints)
{
    numSlidePoints = newNumSlidePoints;

    if(!numSlidePoints){
        slideDelta = 0;
        return;
    }

    slideDelta = bodyRender.getSize().y / (float)numSlidePoints;

    reTransposeSlider();

    sliderRender.setSize({sliderRender.getSize().x, slideDelta});
}

void UI::ScrollListSlider::create(const sf::Vector2f &pos, const sf::Vector2f &size)
{
    createBody(pos, size, 0.0f);
    
    resize(0);
    
    sliderRender.setPosition(pos);
    sliderRender.setSize({size.x, slideDelta});

    bodyRender.setFillColor(Palette::Table[Palette::ID::ScrollListSlider]);
    sliderRender.setFillColor(Palette::Table[Palette::ID::ScrollListSliderBack]);
}

//! ScrollList

void UI::ScrollList::update()
{
    lastPressedElement = -1;

    int maxScrollElem = getMaxScrollElem();

    SF::Window::window.draw(bodyRender);

    for(int i = currentScroll; i < maxScrollElem; i++){
        ScrollListElement& element = myElements[i];

        ContactType contact = element.update();

        if(contact == ContactType::Pressed){
            lastPressedElement = i;
        }
    }

    sliderBar.update();

    int newScroll = sliderBar.getNewSlide();

    if(newScroll != -1){
        currentScroll = newScroll;
        reTransposeElems();
    }
    else{
        // if cursor is in my body and mouse wheel scrolled
        if(SF::Input::mouseWheelScroll != 0 && bodyRender.getGlobalBounds().contains(SF::Input::curMousePos)){
            if(SF::Input::mouseWheelScroll > 0 && currentScroll != 0){
                currentScroll--;
            }
            else if (currentScroll != myElements.size() - 1){
                currentScroll++;
            }

            reTransposeElems();
            sliderBar.setNewSlide(currentScroll);
        }
    }
}

void UI::ScrollList::pushElement(const std::string &text)
{
    ScrollListElement& newElement = myElements.emplace_back();

    newElement.create(sf::Vector2f(0,0), sf::Vector2f(bodyRender.getSize().x - sliderWidth, elementsHeight), text);

    if(myElements.size() <= currentScroll + maxVisibleElems){
        reTransposeElems();
    }

    sliderBar.resize(myElements.size());
}

void UI::ScrollList::create(const sf::Vector2f &pos, const sf::Vector2f &size)
{
    createBody(pos, size, -5.0f);

    elementsHeight = calculateElemHeight(size.y);

    bodyRender.setFillColor(Palette::Table[Palette::ID::ScrollListBody]);
    bodyRender.setOutlineColor(Palette::Table[Palette::ID::ScrollListBody] - sf::Color(40, 40, 40, 0));

    sliderBar.create(pos, {sliderWidth, size.y});
}

void UI::ScrollList::clear()
{
    currentScroll = 0;
    sliderBar.setNewSlide(0);
    myElements.clear();
}

float UI::ScrollList::calculateElemHeight(float myBodyHeight)
{
    float elementsHeight = 0.0f;

    elementsHeight = myBodyHeight - elementsSpace * (maxVisibleElems - 1);
    elementsHeight /= maxVisibleElems;

    return elementsHeight;
}

void UI::ScrollList::reTransposeElems()
{
    int maxScrollElem = getMaxScrollElem();

    sf::Vector2f elementPos = getElemsStartingPos();
    
    for(int i = currentScroll; i < maxScrollElem; i++){
        ScrollListElement& element = myElements[i];

        element.resetPosition(elementPos);

        elementPos.y += elementsHeight + elementsSpace;
    }
}