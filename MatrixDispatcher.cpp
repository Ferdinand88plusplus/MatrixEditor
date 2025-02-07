#include "MatrixDispatcher.h"

#include "SF/RsrcDispatcher.h"
#include "SF/Window.h"
#include "SF/Input.h"

#include <iostream>

void MatrixDispatcher::create()
{
    matrixGraph.create(globconst::matrixWidth, globconst::matrixHeight);
}

void MatrixDispatcher::update()
{
    if(!matrixInfo) return;
    
    frameChoosedSlotNum = getChoosedSlotNum();
    bool isCurrentCellSelected = 0;

    globalInput();

    for(int y = 0;y < globconst::matrixHeight; y++){
        for(int x = 0; x < globconst::matrixWidth; x++){
            MatrixCellInfo& cell = matrixInfo->cells[y][x];
            MatrixCellGraphic& visualizer = matrixGraph.cells[y][x];

            sf::Vector2i currentPosVec2 = sf::Vector2i(x,y);

            isCurrentCellSelected = false;
            for(const sf::Vector2i& selectPos : selectedCells){
                if(selectPos == currentPosVec2){
                    isCurrentCellSelected = true;
                    break;
                }
            }

            cellInput(currentPosVec2);
            
            if(isCurrentCellSelected){
                visualizer.putSelectMask();
            }
            SF::Window::window.draw(visualizer.mySprite);
            if(cell.active){
                SF::Window::window.draw(visualizer.myText);
            }
        }
    }
}

bool MatrixDispatcher::processCellEdit(MatrixCellInfo& cell)
{

    if(SF::Input::lmbPress){ 

        switch(currentTool){
        case MechosMatrixTool::Erase:
            cell.active = cell.slotNum = cell.slotType = 0;
            break;
        case MechosMatrixTool::SetInventory:
            cell.active = 1;
            cell.slotNum = 0;
            cell.slotType = SlotType::None;
            break;
        case MechosMatrixTool::SetRig:
            cell.active = 1;
            cell.slotType = SlotType::Rig;
            break;
        case MechosMatrixTool::SetTerminator:
            cell.active = 1;
            cell.slotType = SlotType::Terminator;
            break;
        case MechosMatrixTool::SetWeapon:
            cell.active = 1;
            cell.slotType = SlotType::Weapon;
            break;
        }

        return 1;
    }

    if(frameChoosedSlotNum != -1){
        cell.slotNum = frameChoosedSlotNum;

        return 1;
    }
    return 0;
}

int MatrixDispatcher::getChoosedSlotNum()
{
    for(int i = sf::Keyboard::Num0 ; i <= sf::Keyboard::Num9; i++){
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key(i))){
            return i - sf::Keyboard::Num0;
        }
    }

    return -1;
}

void MatrixDispatcher::cellInput(const sf::Vector2i& matrixPosition)
{
    MatrixCellGraphic& graphCell = matrixGraph.cells[matrixPosition.y][matrixPosition.x];
    MatrixCellInfo& infoCell = matrixInfo->cells[matrixPosition.y][matrixPosition.x];

    if(!graphCell.collider.isContains(SF::Input::curMousePos)){
        return;
    }

    // selecting cell
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)){
        if(SF::Input::lmbPress){
            bool alredySelected = false;
            
            for(const sf::Vector2i& selectPos : selectedCells){
                if(selectPos == matrixPosition){
                    alredySelected = true;
                    break;
                }
            }

            if(!alredySelected){
                selectedCells.push_back(matrixPosition);
            }
        }
        return;
    }

    // editing cell
    if(SF::Input::lmbPress || SF::Input::rmbPress){
        for(const sf::Vector2i& selectPos : selectedCells){
            matrixGraph.cells[selectPos.y][selectPos.x].removeSelectMask();
        }

        selectedCells.clear();
    }

    if(processCellEdit(infoCell)){
        graphCell.updateGraphic(infoCell);
    }
}

void MatrixDispatcher::globalInput()
{
    if(frameChoosedSlotNum != -1){
        for(const sf::Vector2i& selectPos : selectedCells){
            MatrixCellInfo& infoCell = matrixInfo->cells[selectPos.x][selectPos.y];
            MatrixCellGraphic& graphCell = matrixGraph.cells[selectPos.y][selectPos.x];

            infoCell.slotNum = frameChoosedSlotNum;
            graphCell.updateGraphic(infoCell);
        }
    }
}
