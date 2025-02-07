#pragma once
#include "RectButton.h"

#include "../SF/Input.h"

#include <vector>

namespace UI{
    class ScrollListElement : public RectButton{
    public:

    };

    class ScrollListSlider : public MouseContactable<RectCollider>, public BasicContainer{
    public:

        sf::RectangleShape sliderRender;

        void update();

        void resize(int newNumSlidePoints);

        void create(const sf::Vector2f& pos, const sf::Vector2f& size);


        // returns -1 if didnt slided
        int getNewSlide(){
            return hasSlided ? currentSlide : -1;
        }
        void setNewSlide(int newSlide){
            currentSlide = newSlide;
            reTransposeSlider();
        }

    private:

        bool hasSlided = 0;
        int currentSlide = 0;
        float slideDelta = 0.0f;
        int numSlidePoints = 0;

        void reTransposeSlider(){
            sliderRender.setPosition(sliderRender.getPosition().x, bodyRender.getPosition().y + slideDelta * currentSlide);
        }
    };

    class ScrollList : BasicContainer{
    public:

        std::vector<ScrollListElement> myElements;

        ScrollListSlider sliderBar;

        void update();

        void pushElement(const std::string& text);

        void create(const sf::Vector2f& pos, const sf::Vector2f& size);

        void clear();

        const int getPressedElemIndex(){
            return lastPressedElement;
        }

    private:

        static constexpr int maxVisibleElems = 15;
        static constexpr float elementsSpace = 5.0f;
        static constexpr float sliderWidth = 20.0f;

        float elementsHeight = 0.0f;
        int currentScroll = 0;
        int lastPressedElement = -1;

        float calculateElemHeight(float myBodyHeight);

        void reTransposeElems();
        
        
        
        int getMaxScrollElem(){
            return currentScroll + maxVisibleElems > myElements.size() ? myElements.size() : currentScroll + maxVisibleElems;
        }

        sf::Vector2f getElemsStartingPos(){
            return bodyRender.getPosition() + sf::Vector2f(sliderWidth, 0);
        };
    };
};