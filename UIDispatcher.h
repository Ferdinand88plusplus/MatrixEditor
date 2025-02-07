#pragma once
#include "UI/ScrollList.h"
#include "UI/ImgButton.h"
#include "UI/ButtonBase.h"

#include "SF/Window.h"

enum UICall {
    CallUndefined = -1,

    CallReloadList,
    CallSaveList,
    
    CallToolErase,
    CallToolInventory,
    CallToolWeapon,
    CallToolTerminator,
    CallToolRig,
};


static constexpr int toolsCallsStart = CallToolErase;

class UIDispatcher{
public:

    void Init();
    void Update();
    void DeInit();

    UI::ScrollList mechosesList;

    std::vector<UI::ButtonBase*> buttons;

    std::vector<int> frameCallStack;

    int loadMatrixID = -1;

    template<class btn_type>
    btn_type& emplaceButton(int btnCall){
        UI::ButtonBase*& baseptr = buttons.emplace_back();
        baseptr = new btn_type();

        btn_type* ptr = (btn_type*)baseptr;

        ptr->pressCall = btnCall;
        return *ptr;
    }

private:

    sf::Text hintRender;
    int hintCounter = 0;
    static constexpr int hintDisplayTime = 30;
    UI::ButtonBase* hintTarget = 0;

    void initMechosPanel();
    void initToolBar();
    void initHintRender();

    void allignHintRender();
};
