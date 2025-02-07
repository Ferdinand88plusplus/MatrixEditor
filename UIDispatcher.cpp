#include "UIDispatcher.h"

#include "IO/ConfigParser.h"
#include "PlacementChain.h"

#include <iostream>

void UIDispatcher::Init()
{
    initMechosPanel();
    initToolBar();
    initHintRender();
};

void UIDispatcher::Update()
{
    frameCallStack.clear();
    loadMatrixID = -1;

    mechosesList.update();
    for(UI::ButtonBase* btn : buttons){
        UI::ContactType contactResult = btn->update();

        // ignore buttons without hint text
        if(btn->hintText.size())
        {
            if(hintTarget == btn){
                if(contactResult == UI::ContactType::Floating)
                {
                    hintCounter++;

                    if(hintCounter == hintDisplayTime){
                        hintRender.setString(btn->hintText);
                    }
                }
                else
                {
                    hintCounter = 0;
                    hintTarget = 0;
                }
            }
            else if(!hintTarget){
                if(contactResult == UI::ContactType::Floating)
                {
                    hintCounter++;
                    hintTarget = btn;
                }
            }
            
        }

        if(contactResult == UI::ContactType::Pressed)
        {
            int& call = frameCallStack.emplace_back();
            call = btn->pressCall;
            continue;
        }
    }

    if(hintCounter >= hintDisplayTime){
        hintRender.setPosition(SF::Input::curMousePos + sf::Vector2f(10, 10));
        allignHintRender();
        SF::Window::window.draw(hintRender);
    }

    int pressedIndex = mechosesList.getPressedElemIndex();

    if(pressedIndex != -1){
        loadMatrixID = pressedIndex;
    }
};

void UIDispatcher::DeInit()
{
}

void UIDispatcher::initMechosPanel() 
{
    PlacementChain mechosesPanelChain;

    sf::Vector2f mechosPanelElemSize = sf::Vector2f(300.0f, 30.0f);

    mechosesPanelChain.axis = Axis::Y;
    mechosesPanelChain.altSpace = SF::Window::resolution.x - mechosPanelElemSize.x;
    mechosesPanelChain.elemSize = mechosPanelElemSize.y;

    UI::RectButton& reloadListBtn = emplaceButton<UI::RectButton>(CallReloadList);
    UI::RectButton& saveListBtn = emplaceButton<UI::RectButton>(CallSaveList);
    
    reloadListBtn.create(
        mechosesPanelChain.getNextPos(),
        mechosPanelElemSize,
        "Reload"
    );

    reloadListBtn.hintText = "Reload mechoses from mechoses.lst";

    saveListBtn.create(
        mechosesPanelChain.getNextPos(),
        mechosPanelElemSize,
        "Save"
    );

    saveListBtn.hintText = "Save mechoses into mechoses.lst";

    mechosesList.create(
        {mechosesPanelChain.altSpace, mechosesPanelChain.usedSpace},
        {mechosPanelElemSize.x, mechosesPanelChain.getRemainingSpace()}
    );
}
void UIDispatcher::initToolBar() 
{
    PlacementChain toolBarChain;

    sf::Vector2f toolElemSize = sf::Vector2f(50.0f, 50.0f);

    toolBarChain.axis = Axis::X;
    toolBarChain.altSpace = SF::Window::resolution.y - toolElemSize.y;
    toolBarChain.elemSize = toolElemSize.x;

    UI::ImgButton& toolEraseBtn = emplaceButton<UI::ImgButton>(CallToolErase);
    UI::ImgButton& toolInventoryBtn = emplaceButton<UI::ImgButton>(CallToolInventory);
    UI::ImgButton& toolTerminatorBtn = emplaceButton<UI::ImgButton>(CallToolTerminator);
    UI::ImgButton& toolRigBtn = emplaceButton<UI::ImgButton>(CallToolRig);
    UI::ImgButton& toolWeaponBtn = emplaceButton<UI::ImgButton>(CallToolWeapon);

    toolEraseBtn.create(
        toolBarChain.getNextPos(),
        "rsrc/tool_erase.png"
    );

    toolEraseBtn.hintText = "Erase cell";

    toolInventoryBtn.create(
        toolBarChain.getNextPos(),
        "rsrc/tool_inv.png"
    );

    toolInventoryBtn.hintText = "Put inventory cell";

    toolTerminatorBtn.create(
        toolBarChain.getNextPos(),
        "rsrc/tool_term.png"
    );

    toolTerminatorBtn.hintText = "Put terminator cell";

    toolRigBtn.create(
        toolBarChain.getNextPos(),
        "rsrc/tool_rig.png"
    );

    toolRigBtn.hintText = "Put rig cell";

    toolWeaponBtn.create(
        toolBarChain.getNextPos(),
        "rsrc/tool_wpn.png"
    );

    toolWeaponBtn.hintText = "Put weapon cell";

}
void UIDispatcher::initHintRender() 
{
    hintRender.setFillColor(sf::Color::White);
    hintRender.setCharacterSize(20);
    hintRender.setFont(SF::RsrcDispatcher::stdFont);
    hintRender.setOutlineThickness(2);
    hintRender.setOutlineColor(sf::Color::Black);
}
void UIDispatcher::allignHintRender() 
{
    sf::FloatRect bounds = hintRender.getGlobalBounds();

    float rightPos = bounds.left + bounds.width;
    float bottomPos = bounds.top + bounds.height;

    sf::Vector2f totalShift;

    if(rightPos > SF::Window::resolution.x){
        totalShift.x = SF::Window::resolution.x - rightPos;
    }
    if(bottomPos > SF::Window::resolution.y){
        totalShift.y = SF::Window::resolution.y - bottomPos;
    }

    if(bounds.left < 0){
        totalShift.x = -bounds.left;
    }
    if(bounds.top < 0){
        totalShift.y = -bounds.top;
    }

    hintRender.move(totalShift);
};
