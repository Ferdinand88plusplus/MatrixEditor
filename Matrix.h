#pragma once

#include "MatrixCell.h"

#include "SF/RsrcDispatcher.h"

namespace globconst{
    extern int matrixWidth;
    extern int matrixHeight;

    extern sf::Vector2f matrixSpaces;
    extern sf::Vector2f matrixCellSize;
};

struct InfoMatrix{
    MatrixCellInfo** cells = 0;

    void create(int width, int height);
    void load(InfoMatrix& from);
};

struct GraphMatrix{
    MatrixCellGraphic** cells = 0;

    void create(int width, int height);
    void load(InfoMatrix& from);
};