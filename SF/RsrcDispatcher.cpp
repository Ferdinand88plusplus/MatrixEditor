#include "RsrcDispatcher.h"

#include "../ErrorDispatcher.h"

namespace SF::RsrcDispatcher{
    sf::Font stdFont;
    sf::Texture slotTxr;
}

void SF::RsrcDispatcher::Load()
{
    if(!stdFont.loadFromFile("rsrc/FiraMono-Medium.ttf")){
        ErrorDispatcher::Throw("RsrcDispatcher", "Font loading failed");
    }

    if(!slotTxr.loadFromFile("rsrc/slot.png")){
        ErrorDispatcher::Throw("RsrcDispatcher", "Slot image loading failed");
    }
}