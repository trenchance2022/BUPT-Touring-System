#include "mylabel.h"

myLabel::myLabel(QWidget *parent)
    :QLabel(parent)
{
    m_Img = QPixmap("./bupt_map.bmp");
    setPixmap(m_Img);
    setGeometry(10, 10, m_Img.width(), m_Img.height());
    m_flag = 0;
}

void myLabel::paintEvent(QPaintEvent *e)
{
    QLabel::paintEvent(e);
    if(m_flag == 1) PaintRoute(m_start, m_end);
    if(m_flag == 2) multiRoutePaint();
}

void myLabel::routePaint(Attraction a, int flag, int start, int end)
{
    m_attract = a;
    m_flag = flag;
    m_start = start;
    m_end = end;
    update();
}

void myLabel::PaintRoute(int start, int end)
{
    int s = start;
    int e = end;
    ALGraph g = m_attract.graph;
    if (s == e) {
        return;
    }
    if (prevNode[e] == -1) {
        return;
    }
    PaintRoute(s, prevNode[e]);
    double sx = g.vertexes[prevNode[e]].x * 1.715;
    double sy = g.vertexes[prevNode[e]].y * 1.715;
    double ex = g.vertexes[e].x *  1.715;
    double ey = g.vertexes[e].y *  1.715;
    double mx, my;
    ArcNode* p = g.vertexes[prevNode[e]].first;
    while(p){
        if(p->name == g.vertexes[e].name){
            mx = p->midx *  1.715;
            my = p->midy *  1.715;
            break;
        }
        p = p->next;
    }
    QPen pen;
    pen.setColor(QColor(255,0,0,255));
    pen.setWidth(2);
    QPainter painter(this);
    painter.setPen(pen);
    painter.setBrush(pen.color());
    painter.drawLine(QLineF(sx, sy, mx, my));
    painter.drawLine(QLineF(mx, my, ex, ey));

    QLineF line;
    if(sx == ex || sy == ey){
        line = QLineF(QPointF(ex, ey), QPointF(sx, sy));
    }
    else{
        line = QLineF(QPointF(ex, ey), QPointF(mx, my));
    }
        qreal arrowSize = 8;
        double angle = std::atan2(-line.dy(), line.dx());
        QPointF arrowP1 = line.p1() + QPointF(sin(angle + M_PI / 3) * arrowSize,
                                              cos(angle + M_PI / 3) * arrowSize);
        QPointF arrowP2 = line.p1() + QPointF(sin(angle + M_PI - M_PI / 3) * arrowSize,
                                              cos(angle + M_PI - M_PI / 3) * arrowSize);
        QPolygonF arrowHead;
        arrowHead.clear();
        arrowHead << line.p1() << arrowP1 << arrowP2;
        painter.drawPolygon(arrowHead);
}

void myLabel::multiRoutePaint()
{
    ALGraph g = m_attract.graph;
    int seq = 0;
    int offset = 0;
    for(int i = 1; i < idx; i++){
        double sx = g.vertexes[anspath[i-1]].x * 1.715;
        double sy = g.vertexes[anspath[i-1]].y * 1.715;
        double ex = g.vertexes[anspath[i]].x *  1.715;
        double ey = g.vertexes[anspath[i]].y *  1.715;
        double mx, my;
        ArcNode* p = g.vertexes[anspath[i-1]].first;
        while(p){
            if(p->name == g.vertexes[anspath[i]].name){
                mx = p->midx *  1.715;
                my = p->midy *  1.715;
                break;
            }
            p = p->next;
        }
        QPen pen;
        pen.setColor(QColor(255,0,0,255));
        pen.setWidth(2);
        QPainter painter(this);
        painter.setPen(pen);
        painter.setBrush(pen.color());
        painter.drawLine(QLineF(sx, sy, mx, my));
        painter.drawLine(QLineF(mx, my, ex, ey));

        QLineF line;
        if(sx == ex || sy == ey){
            line = QLineF(QPointF(ex, ey), QPointF(sx, sy));
        }
        else{
            line = QLineF(QPointF(ex, ey), QPointF(mx, my));
        }
        qreal arrowSize = 7;
        double angle = std::atan2(-line.dy(), line.dx());
        QPointF arrowP1 = line.p1() + QPointF(sin(angle + M_PI / 3) * arrowSize,
                                              cos(angle + M_PI / 3) * arrowSize);
        QPointF arrowP2 = line.p1() + QPointF(sin(angle + M_PI - M_PI / 3) * arrowSize,
                                              cos(angle + M_PI - M_PI / 3) * arrowSize);
        QPolygonF arrowHead;
        arrowHead.clear();
        arrowHead << line.p1() << arrowP1 << arrowP2;
        painter.drawPolygon(arrowHead);


        //painter.drawText(mx, my, QString("%1").arg(++seq));
        //painter.drawText(ex, ey, QString("%1").arg(++seq));
    }
}
