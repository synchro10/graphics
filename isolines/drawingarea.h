#ifndef DRAWINGAREA_H
#define DRAWINGAREA_H

#include <QWidget>
#include <QVector>
#include "zone.h"
#include "legend.h"
#include "options.h"

class DrawingArea : public QWidget
{
    Q_OBJECT
public:
    explicit DrawingArea(QWidget *parent = 0);
    void paintEvent(QPaintEvent *event) override;
    void open(const QString &fileName);
    void setInterpolation();
    void setGrid();
    void setIsoline();
    void clear();
    const Options getOptions();
    void setOptions(const Options options);
signals:
    void statusMessage(const QString& message);
public slots:
private:
    Zone* zone = nullptr;
    Legend* legend = nullptr;
    QVBoxLayout *mainLayout = nullptr;
    void deleteComment(QString& str);
};

#endif // DRAWINGAREA_H
