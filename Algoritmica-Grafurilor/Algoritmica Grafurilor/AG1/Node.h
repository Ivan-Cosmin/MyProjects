#pragma once
#include <QtWidgets/QMainWindow>
#include <QPainter>
#include <QMouseEvent>
class Node
{
public:
    Node();
    ~Node();
    Node(QPoint, int);
    Node(Node*);
    void setCoord(QPoint p);
    void setValue(int val);
    void setNode(Node* val);
    void setIsSelected(bool);
    QPoint getCoord();
    int getX();
    int getY();
    int getValue();
    bool getIsSelected();
    static const int DimNODE = 40;
private:
    int value;
    QPoint coordinates; 
    bool isSelected;
};

