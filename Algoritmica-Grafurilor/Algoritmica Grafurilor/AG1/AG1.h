#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_AG1.h"
#include "Graph.h"
#include "Node.h"
#include <QMainWindow>
#include <QMouseEvent>
#include <QPaintEvent>
namespace Ui { class AG1; }

class AG1 : public QMainWindow
{
    Q_OBJECT

public:
    AG1(QWidget *parent = nullptr);
    ~AG1();

    virtual void mousePressEvent(QMouseEvent* e);
    virtual void mouseReleaseEvent(QMouseEvent* e);
    virtual void mouseMoveEvent(QMouseEvent* e);
    virtual void paintEvent(QPaintEvent* e);
    void drawLine(Node* N1, Node* N2, int radius, QPainter& p);
    void drawArrow(QPoint Q1, QPoint Q2, QPainter& p);
    void paintNode(QPainter&, Node*);

private slots:
    void on_radioButton_clicked1();

private:
    Graf graf;
    Node* firstNode;
    Node* secondNode;
    Ui::AG1Class ui;
    bool isMousePressed;
    QPoint offset;
};
