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
               QWidget *parent = NULL) : QFrame(parent){

         this->networkButton = networkButton;
         this->subnetButtons = subnetButtons;
         this->scrollArea = scrollArea;
         this->draw = draw;
         this->gridSize = gridSize;
         this->scale = scale;
     }

protected:

    void paintEvent(QPaintEvent * event){
        QFrame::paintEvent(event);

        QPainter painter = QPainter(this);
        QPen pen = QPen(QColor(38,94,84).lighter());
        painter.setPen(pen);

        if(draw)
        {
            for(int i = 0 ; i < scrollArea->width() * subnetButtons.count(); i += 30 * gridSize)
            {
                painter.drawLine(QPoint(0, i), QPoint(scrollArea->height() * subnetButtons.count(), i));
            }

            for(int i = 0 ; i < scrollArea->height() * subnetButtons.count(); i += 30 * gridSize)
            {
                painter.drawLine(QPoint(i, 0), QPoint(i, scrollArea->width() * subnetButtons.count()));
            }
        }

        pen.setColor(QColor(255,255,255));
        pen.setWidth(3 * scale);
        painter.setPen(pen);

        for(int i = 0; i < static_cast<int>(subnetButtons.size()); i++)
        {
             QPoint a = networkButton->mapTo(this, networkButton->rect().center());
             QPoint b = networkButton->mapTo(this, QPoint(0, networkButton->rect().center().y()));
             QPoint c = subnetButtons.at(i)->mapTo(this, QPoint(subnetButtons.at(i)->rect().center().x(), 0));
             QPoint d = QPoint(c.x(), b.y());

             painter.drawLine(a, d);
             painter.drawLine(d, subnetButtons.at(i)->mapTo(this, subnetButtons.at(i)->rect().center()));
        }
    }

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
