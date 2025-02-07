#include "LogstackManager.h"

#include "EditorLogstack.h"

#include "SF/Window.h"
#include "SF/RsrcDispatcher.h"
#include "Palette.h"

void LogstackManager::init()
{
    textRender.setFont(SF::RsrcDispatcher::stdFont);
    textRender.setCharacterSize(24);
}

void LogstackManager::update()
{
    for(int i = 0 ; i < EditorLogstack::stack.size(); i++){
        EditorLogMsg& message = EditorLogstack::stack[i];

        if(!--message.lifetime){
            EditorLogstack::stack.erase(EditorLogstack::stack.begin() + i);
            i--;
            continue;
        }

        textRender.setFillColor(Palette::Table[message.type + Palette::BlockMsgs]);
        textRender.setString(message.text);

        SF::Window::window.draw(textRender);
        textRender.move(0, textRender.getLocalBounds().height);
    }
    
    textRender.setPosition(0,0);
}
