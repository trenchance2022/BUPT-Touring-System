#ifndef MYLABEL_H
#define MYLABEL_H

#include <QLabel>
#include <QObject>
#include <QWidget>
#include "route_plan.h"
#include "myGraph.h"
#include <QPen>
#include <QPoint>
#include <QPainter>

class myLabel : public QLabel
{
    Q_OBJECT
public:
    myLabel(QWidget *parent);
    void paintEvent(QPaintEvent *e) override;
    void routePaint(Attraction a, int flag, int start, int end);
    void PaintRoute(int start, int end);
    void multiRoutePaint();


private:
    QPixmap m_Img;
    Attraction m_attract;
    int m_flag;
    int m_start;
    int m_end;
};

#endif // MYLABEL_H
