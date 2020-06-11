#ifndef GRAPHFRAME_H
#define GRAPHFRAME_H

#include "SubnetButton.h"
#include "NetworkButton.h"

#include <QWidget>
#include <QFrame>
#include <QPainter>
#include "core/INetwork.h"

using namespace core;

class GraphFrame : public QFrame
{
    Q_OBJECT

public:

    GraphFrame(NetworkButton *networkButton, QList<SubnetButton*> subnetButtons,
               QWidget *scrollArea, bool draw, float gridSize, float scale,
               QWidget *parent);

protected:

    void paintEvent(QPaintEvent * event);

private:

    bool draw = false;
    float gridSize = 1.0f;
    float scale = 1.0f;

    QPoint a;
    QPoint b;
    QWidget *scrollArea;    

    NetworkButton *networkButton;
    QList<SubnetButton*> subnetButtons;
};

#endif // GRAPHFRAME_H
