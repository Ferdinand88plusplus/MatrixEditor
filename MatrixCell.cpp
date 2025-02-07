#include "MatrixCell.h"

#include "Palette.h"

sf::Clock globalClock;

sf::Color MatrixCellGraphic::selectColor(MatrixCellInfo& src)
{
    if(!src.active){
        return Palette::Table[Palette::EmptySlot];
    }

    return Palette::Table[src.slotType + Palette::BlockSlots];

}

void MatrixCellGraphic::updateGraphic(MatrixCellInfo& src)
{
    myColor = selectColor(src);
    mySprite.setColor(myColor);

    if(src.active){
        std::string strNumber;
        //strNumber = std::to_string(src.slotNum); 
        strNumber += char(src.slotNum + 48);  // slotnum is >= 0 && <= 9, so we can storage it in one byte
        myText.setString(strNumber);
    }
}

void MatrixCellGraphic::putSelectMask()
{
    float sinValue = std::sin(globalClock.getElapsedTime().asSeconds()*10);

    int rawColValue = sinValue * 10.0f;
    unsigned char absColValue = abs(rawColValue);

    sf::Color maskColor = sf::Color(absColValue, absColValue, absColValue, 0);

    sf::Color newColor = myColor;

    newColor = rawColValue < 0 ? myColor - maskColor : myColor + maskColor;

    mySprite.setColor(newColor);
}

void MatrixCellGraphic::removeSelectMask()
{
    mySprite.setColor(myColor);
}
