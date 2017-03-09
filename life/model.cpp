#include "model.h"
#include <assert.h>
#include <QPoint>
#include <vector>
#include <iostream>

Model::Model()
{
    resize(gridWidth, gridHeight);
}

Model::Model(uint width, uint height)
{
    assert(width*height != 0);
    gridWidth = width;
    gridHeight = height;
    resize(gridWidth, gridHeight);
}

Model::~Model()
{

}

void Model::aliveCell(int x, int y)
{
    currentState[y][x] = true;
}

void Model::killCell(int x, int y)
{
    currentState[y][x] = false;
}

void Model::invertCell(int x, int y)
{
    if (currentState[y][x]){
         currentState[y][x] = false;
    } else {
         currentState[y][x] = true;
    }
}

void Model::countNextState()
{
    if (isImpactCounted){
        return;
    }
    for(uint y = 0; y < gridHeight; y++){
        for(uint x = 0; x < gridWidth; x++){
            uint nearCount = 0;
            uint farCount = 0;
            uint parity = (y+1)%2;
            for(int i = 0; i < 6; i++){
                QPoint offset = offsetNearCells[parity][i];
                int x1 = x + offset.x();
                int y1 = y + offset.y();
                if (0 <= x1 && x1 < (int)gridWidth && 0 <= y1 && y1 < (int)gridHeight){
                    if (currentState[y1][x1])
                        nearCount++;
                }
            }
            for(int i = 0; i < 6; i++){
                QPoint offset = Model::offsetFarCells[parity][i];
                int x1 = x + offset.x();
                int y1 = y + offset.y();
                if (0 <= x1 && x1 < (int)gridWidth && 0 <= y1 && y1 < (int)gridHeight){
                    if (currentState[y1][x1])
                        farCount++;
                }
            }

            impact[y][x] = FST_IMPACT * nearCount + SND_IMPACT * farCount;
            nextState[y][x] = currentState[y][x];
            if (currentState[y][x]){
                if (!(LIVE_BEGIN <= impact[y][x] && impact[y][x] <= LIVE_END))
                    nextState[y][x] = false;
            } else {
                if (BIRTH_BEGIN <= impact[y][x] && impact[y][x] <= BIRTH_END)
                    nextState[y][x] = true;
            }
        }
    }
    isImpactCounted = true;
}

void Model::changeState()
{
    currentState.swap(nextState);
    isImpactCounted = false;
}

void Model::clear()
{
    for(uint y = 0; y < gridHeight; y++){
        for(uint x = 0; x < gridWidth; x++){
            currentState[y][x] = false;
            //nextState[y][x] = false;
            impact[y][x] = false;
        }
    }
}

void Model::resize(uint x, uint y)
{
    //todo copy
    gridHeight = y;
    gridWidth = x;

    currentState.resize(gridHeight);
    nextState.resize(gridHeight);
    impact.resize(gridHeight);
    for(uint i = 0; i < gridHeight; i++){
        int width = gridWidth - i%2;
        currentState[i] = std::vector<bool>(width);
        nextState[i] = std::vector<bool>(width);
        impact[i] = std::vector<uint>(width);
        for(int j = 0; j < width; j++){
            currentState[i][j] = false;
            nextState[i][j] = false;
            impact[i][j] = 0;
        }
    }

}

bool Model::changeRules(uint, uint, uint, uint, uint, uint)
{
    //todo check and set
}

uint Model::getGridWidth() const
{
    return gridWidth;
}


uint Model::getGridHeight() const
{
    return gridHeight;
}

std::vector<std::vector<bool> >& Model::getCurrentState()
{
    return currentState;
}

