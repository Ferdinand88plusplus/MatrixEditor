#include "Matrix.h"

#include "UI/Collider.h"


namespace globconst{
    int matrixWidth;
    int matrixHeight;

    sf::Vector2f matrixSpaces = sf::Vector2f(19, 27);
    sf::Vector2f matrixCellSize = sf::Vector2f(37, 37);
};

void InfoMatrix::create(int width, int height)
{
    cells = new MatrixCellInfo*[height];
    for(int i = 0 ; i< height; i++){
        cells[i] = new MatrixCellInfo[width];
    }
}

void InfoMatrix::load(InfoMatrix &from)
{
    for(int x = 0; x < globconst::matrixWidth; x++){
        for(int y = 0; y < globconst::matrixHeight; y++){
            cells[y][x] = from.cells[y][x];
        }
    }
}

void GraphMatrix::create(int width, int height)
{
    
    sf::Vector2f matrixPosition = sf::Vector2f(50, 50);

    sf::Vector2f cellPosition = matrixPosition;

    cells = new MatrixCellGraphic*[height];

    for(int y  = 0 ; y < height; y++){
        cells[y] = new MatrixCellGraphic[width];

        for(int x =0 ; x < width; x++){
            MatrixCellGraphic& cell = cells[y][x];

            cell.mySprite.setTexture(SF::RsrcDispatcher::slotTxr);
            cell.mySprite.setPosition(cellPosition);

            cell.collider.radius = globconst::matrixCellSize.x / 2.5f;
            cell.collider.position = cellPosition + globconst::matrixCellSize / 2.0f;
            
            cell.myText.setPosition(cellPosition);
            cell.myText.setCharacterSize(20);
            cell.myText.setFont(SF::RsrcDispatcher::stdFont);

            cellPosition.x += globconst::matrixCellSize.x;
        }

        cellPosition.x = matrixPosition.x;

        if(!(y%2)){
            cellPosition.x += globconst::matrixSpaces.x;
        }
        cellPosition.y += globconst::matrixSpaces.y;
    }
}

void GraphMatrix::load(InfoMatrix &from)
{
    for(int y = 0; y < globconst::matrixHeight; y++){
        for(int x = 0 ; x < globconst::matrixWidth; x++){
            cells[y][x].updateGraphic(from.cells[y][x]);
        }
    }
}


