#ifndef MODEL_H
#define MODEL_H

#include <vector>
#include <QPoint>

class Model
{
public:
    Model();
    Model(uint width, uint height);
    ~Model();
    void aliveCell(int x, int y);
    void killCell(int x, int y);
    void invertCell(int x, int y);
    void countNextState();
    void changeState();
    void clear();

    void resize(uint x, uint y);
    bool changeRules(uint, uint, uint, uint, uint, uint);

    uint getGridWidth() const;
    uint getGridHeight() const;

    uint LIVE_BEGIN = 20;
    uint LIVE_END = 33;
    uint BIRTH_BEGIN = 23;
    uint BIRTH_END = 29;
    uint FST_IMPACT = 10;
    uint SND_IMPACT = 3;

    std::vector<std::vector<bool> >& getCurrentState();

private:
    uint gridWidth = 5;
    uint gridHeight = 5;
    std::vector<std::vector<bool> > currentState;
    std::vector<std::vector<bool> > nextState;
    std::vector<std::vector<uint>> impact;

    //[0][] for even line, [1][] for odd line
    QPoint offsetNearCells[2][6] = {
        { QPoint(0, -1), QPoint(1, -1), QPoint (-1, 0), QPoint (1, 0), QPoint(0, 1), QPoint(1, 1) },
        { QPoint(-1, -1), QPoint(0, -1), QPoint (-1, 0), QPoint (1, 0), QPoint(-1, 1), QPoint(0, 1) }
    };
    QPoint offsetFarCells[2][6] = {
        { QPoint(0, -2), QPoint(-1, -1), QPoint (2, -1), QPoint (-1, 1), QPoint(2, 1), QPoint(0, 2) },
        { QPoint(0, -2), QPoint(-2, -1), QPoint (1, -1), QPoint (-2, 1), QPoint(1, 1), QPoint(0, 2) }
    };

    bool isImpactCounted = false;

};

#endif // MODEL_H
