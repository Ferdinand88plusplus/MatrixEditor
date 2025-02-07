#pragma once
#include "Matrix.h"
#include "MechosMatrixTool.h"

// Class for matrix editing
class MatrixDispatcher{
public:

    void create();

    void update();

    //returns true if need update graphic
    bool processCellEdit(MatrixCellInfo& cell);

    MechosMatrixTool currentTool = MechosMatrixTool::SetInventory;

    InfoMatrix *matrixInfo = 0;
    GraphMatrix matrixGraph;

    std::vector<sf::Vector2i> selectedCells;

private:

    int frameChoosedSlotNum = -1;

    // keys num0-num9
    int getChoosedSlotNum();

    // check cell editing (for example, changing slottype on one cell)
    void cellInput(const sf::Vector2i& matrixPosition);
    // check global editing (for example, changing slotnum of selected cells)
    void globalInput();
};