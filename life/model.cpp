#include "model.h"
#include <assert.h>
#include <QPoint>
#include <vector>
#include <iostream>
#include <QDebug>
#include <QFile>
#include <QIODevice>
#include <QTextStream>
#include <QStringList>

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
    if (currentState[y][x] == false){
        currentState[y][x] = true;
        isImpactCounted = false;
        liveCount++;
    }
}

void Model::killCell(int x, int y)
{
    if (currentState[y][x] == true){
        currentState[y][x] = false;
        isImpactCounted = false;
        liveCount--;
    }
}

void Model::invertCell(int x, int y)
{
    if (currentState[y][x] == true){
         currentState[y][x] = false;
         liveCount--;
    } else {
         currentState[y][x] = true;
         liveCount++;
    }
    isImpactCounted = false;
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
            if (true == currentState[y][x]){
                if (!(LIVE_BEGIN <= impact[y][x] && impact[y][x] <= LIVE_END)){
                    nextState[y][x] = false;
                }
            } else {
                if (BIRTH_BEGIN <= impact[y][x] && impact[y][x] <= BIRTH_END){
                    nextState[y][x] = true;
                }
            }
        }
    }
    isImpactCounted = true;
}

void Model::changeState()
{
    currentState.swap(nextState);
    isImpactCounted = false;
    recountLiveCells();
}

void Model::clear()
{
    for(uint y = 0; y < gridHeight; y++){
        for(uint x = 0; x < gridWidth; x++){
            currentState[y][x] = false;
            nextState[y][x] = false;
            impact[y][x] = false;
        }
    }
    liveCount = 0;
}

uint Model::getImpact(int x, int y)
{
    return impact[y][x];
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
        //may be resize?
        currentState[i] = std::vector<bool>(width);
        nextState[i] = std::vector<bool>(width);
        impact[i] = std::vector<uint>(width);
        for(int j = 0; j < width; j++){
            currentState[i][j] = false;
            nextState[i][j] = false;
            impact[i][j] = 0;
        }
    }
    recountLiveCells();
    isImpactCounted = false;
}

//return k = cellSize
uint Model::initFromFile(QString fileName)
{
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly)){
        return 0;
    }
    QTextStream in(&file);
    int m = 0;
    int n = 0;
    int line = 0;
    int k = 0;
    int all = 0;

    QString str = in.readLine();
    QStringList words = str.split(" ");
    if (words.length() < 2){
        file.close();
        return 0;
    }
    m = words.at(0).toInt();
    n = words.at(1).toInt();

    str = in.readLine();
    words = str.split(" ");
    if (words.length() < 1){
        file.close();
        return 0;
    }
    line = words.at(0).toInt();

    str = in.readLine();
    words = str.split(" ");
    if (words.length() < 1){
        file.close();
        return 0;
    }
    k = words.at(0).toInt();

    str = in.readLine();
    words = str.split(" ");
    if (words.length() < 1){
        file.close();
        return 0;
    }
    all = words.at(0).toInt();

    if (m < 1 || n < 1 || k < 4 || all < 0){
        file.close();
        return 0;
    }
    std::vector<std::vector<bool> > newCurrentState;
    std::vector<std::vector<bool> > newNextState;
    std::vector<std::vector<uint>> newImpact;
    uint newGridHeight = n;
    uint newGridWidth = m;
    newCurrentState.resize(newGridHeight);
    newNextState.resize(newGridHeight);
    newImpact.resize(newGridHeight);
    for(uint i = 0; i < newGridHeight; i++){
        int width = newGridWidth - i%2;
        newCurrentState[i] = std::vector<bool>(width);
        newNextState[i] = std::vector<bool>(width);
        newImpact[i] = std::vector<uint>(width);
        for(int j = 0; j < width; j++){
            newCurrentState[i][j] = false;
            newNextState[i][j] = false;
            newImpact[i][j] = 0;
        }
    }

    int x = 0;
    int y = 0;
    for(int i = 0; i < all; i++){
        if (in.atEnd()){
            file.close();
            return 0;
        }
        str = in.readLine();
        words = str.split(" ");
        x = words.at(0).toInt();
        y = words.at(1).toInt();
        if (y < 0 || y >= n){
            file.close();
            return 0;
        }
        if (x < 0 || x >= m - y%2){
            file.close();
            return 0;
        }
        newCurrentState[y][x] = true;
    }
    gridHeight = newGridHeight;
    gridWidth = newGridWidth;
    currentState = newCurrentState;
    nextState = newNextState;
    impact = newImpact;
    liveCount = all;
    isImpactCounted = false;
    file.close();
    return k;
}

void Model::saveToFile(QString fileName, uint cellSize)
{
    QFile file(fileName);
    if (!file.open(QIODevice::ReadWrite)){
        return;
    }
    QTextStream out(&file);
    out << gridWidth << " " << gridHeight << "\n";
    out << "1" << "\n";
    out << cellSize << "\n";
    out << liveCount << "\n";
    for(uint y = 0; y < gridHeight; y++){
        for(uint x = 0; x < gridWidth; x++){
            if (true == currentState[y][x]){
                out << x << " " << y << "\n";
            }
        }
    }
    out.flush();
    file.close();
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

std::vector<std::vector<uint> > &Model::getImpact()
{
    return impact;
}

void Model::recountLiveCells()
{
    liveCount = 0;
    for(uint y = 0; y < gridHeight; y++){
        for(uint x = 0; x < gridWidth; x++){
            if (true == currentState[y][x]){
                liveCount++;
            }
        }
    }
}

