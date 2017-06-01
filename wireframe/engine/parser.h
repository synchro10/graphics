#ifndef PARSER_H
#define PARSER_H

#include <QStringList>
#include <QFile>
#include "engine/graphicengine.h"
#include <QtWidgets>

class Parser
{
public:
    Parser(){}
    bool static initEngine(const QString &fileName, GraphicEngine& engine);
private:
    void static deleteComment(QString &str)
    {
        QStringList list = str.split("//");
        str = list.constFirst();
    }
};

#endif // PARSER_H
