#pragma once
#include "ui_AG2.h"
#include "Graf.h"
#include <QPaintEvent>
#include <QPainter>
#include <QPushButton>
#include <QGridLayout>

namespace Ui { class AG2; }

class AG2 : public QWidget
{
    Q_OBJECT

public:
    AG2(QWidget *parent = nullptr);
    ~AG2();
   
    void paintEvent(QPaintEvent* event);
    void paintPathNodes();
    friend bool operator<(const QPoint& First, const QPoint& Second);

private slots:
    void pushButton();

private:
    Graf m_graf;
    QPushButton* m_button;
    QGridLayout* m_layout;

};
