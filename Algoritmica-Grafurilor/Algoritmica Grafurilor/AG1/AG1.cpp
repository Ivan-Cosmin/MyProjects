#include "AG1.h"
#include <fstream>

AG1::AG1(QWidget *parent)
    : QMainWindow{parent}
    ,firstNode{nullptr}
    ,secondNode{nullptr}
    ,isMousePressed{false}
    ,offset{0,0}
{
    ui.setupUi(this);
}
AG1::~AG1()
{}

void AG1::mousePressEvent(QMouseEvent* e)
{
    if (e->button() == Qt::RightButton)
    {
        if (graf.verifyNods(e))
            graf.addNode(e->pos());
        else
        {
            for (Node* n : graf.getNodes())
            {
                if (fabs(n->getX() - e->pos().x()) < Node::DimNODE / 2.0 &&
                    fabs(n->getY() - e->pos().y()) < Node::DimNODE / 2.0)
                    if (firstNode == nullptr)
                    {
                        firstNode = n;
                        firstNode->setIsSelected(true);
                    }
                    else
                    {
                        secondNode = n;
                        if (firstNode->getValue() != secondNode->getValue())
                        {
                            Edge* ed = new Edge(firstNode, secondNode);
                            if (graf.verifyEdges(ed))
                                graf.addEdge(ed);
                            else
                                delete ed;
                        } 
                        firstNode->setIsSelected(false);
                        firstNode = nullptr;
                        secondNode = nullptr;
                    }
            }
        }
    }
    else
        if (e->button() == Qt::LeftButton)
        {
            for (Node* n : graf.getNodes())
            {
                if (fabs(n->getX() - e->pos().x()) < Node::DimNODE / 2.0 &&
                    fabs(n->getY() - e->pos().y()) < Node::DimNODE / 2.0)
                {
                    n->setIsSelected(true);
                    isMousePressed = true;
                    break;
                }
            }
        }
    update();
}
void AG1::mouseMoveEvent(QMouseEvent* e)
{
    if (isMousePressed)
        if (Qt::LeftButton)
        {
            for (Node* n : graf.getNodes())
                if (n->getIsSelected())
                {
                    if(graf.verifyNods(e))
                    n->setCoord(e->pos());
                }
            update();
        }
}
void AG1::mouseReleaseEvent(QMouseEvent* e)
{
    if (e->button() == Qt::LeftButton)
    {
        isMousePressed = false;
        for (Node* n : graf.getNodes())
        {
            n->setIsSelected(false);
        }
    }
}
void AG1::paintNode(QPainter& p,Node* n)
{
    if (n->getIsSelected())
        p.setPen(Qt::red);
    else
        p.setPen(Qt::black);

    QRect r(n->getX() - Node::DimNODE/2, n->getY() - Node::DimNODE/2, Node::DimNODE,Node::DimNODE);
    p.drawEllipse(r);
    QString s;
    s.setNum(n->getValue());
    p.drawText(r, Qt::AlignCenter, s);
}
void AG1::on_radioButton_clicked1()
{
    if (graf.isOrientedOrNot())
    {
        if (ui.radioButton1->isChecked())
            graf.saveMatrixOriented();
        else
            if (ui.radioButton2->isChecked())
            {
                graf.setOrientedOrNot(false);
                graf.reset();
            }
    }
    else
    {
        if (ui.radioButton1->isChecked())
        {
            graf.setOrientedOrNot(true);
            graf.reset();
        }
        else
            if (ui.radioButton2->isChecked())
                graf.saveMatrixUnoriented();
    }
}
void AG1::drawLine(Node* N1, Node* N2, int radius, QPainter& p) 
{
    p.setPen(Qt::black);
    qreal dx = N2->getX() - N1->getX();
    qreal dy = N2->getY() - N1->getY();
    qreal distance = qSqrt(dx * dx + dy * dy);
    qreal x1_intersec = N1->getX() + (dx * radius / distance);
    qreal y1_intersec = N1->getY() + (dy * radius / distance);
    qreal x2_intersec = N2->getX() - (dx * radius / distance);
    qreal y2_intersec = N2->getY() - (dy * radius / distance);

    p.drawLine(x1_intersec, y1_intersec, x2_intersec, y2_intersec);

    if(graf.isOrientedOrNot())
    drawArrow(QPoint(x1_intersec, y1_intersec), QPoint(x2_intersec, y2_intersec), p);
}
void AG1::drawArrow(QPoint Q1, QPoint Q2, QPainter& p)
{
    qreal arrowSize = Node::DimNODE / 2.0;
    p.setBrush(Qt::black);
    QLineF line(Q2, Q1);

    double angle = std::atan2(-line.dy(), line.dx());
    QPointF arrowP1 = line.p1() + QPointF(sin(angle + M_PI / 3) * arrowSize, cos(angle + M_PI / 3) * arrowSize);
    QPointF arrowP2 = line.p1() + QPointF(sin(angle + M_PI - M_PI / 3) * arrowSize, cos(angle + M_PI - M_PI / 3) * arrowSize);

    QPolygonF arrowHead;
    arrowHead.clear();
    arrowHead << line.p1() << arrowP1 << arrowP2;
    p.drawPolygon(arrowHead);

    p.setBrush(Qt::white);
}
void AG1::paintEvent(QPaintEvent* e)
{
    QPainter p(this);
    for (Node* n : graf.getNodes())
        paintNode(p, n);
    
    for (Edge* ed : graf.getEdges())
        drawLine(ed->getFirstNode(), ed->getSecondNode(), Node::DimNODE/2, p);

    on_radioButton_clicked1();
    update();
}
