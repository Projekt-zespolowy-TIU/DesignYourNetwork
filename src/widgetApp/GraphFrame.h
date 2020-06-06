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

    GraphFrame( NetworkButton *networkButton, QList<SubnetButton*> subnetButtons, QWidget *scrollArea, QWidget *parent = NULL) : QFrame(parent){
         this->networkButton = networkButton;
         this->subnetButtons = subnetButtons;
         this->scrollArea = scrollArea;
     }

protected:
    void paintEvent( QPaintEvent * event){
        QFrame::paintEvent(event);
        QPainter painter = QPainter(this);
        QPen pen = QPen(QColor(38,94,84).lighter());
        painter.setPen(pen);

        for(int i = 0 ; i < scrollArea->width(); i += 50)
        {
                painter.drawLine(QPoint(0, i), QPoint(1000, i));
        }

        for(int i = 0 ; i < scrollArea->height(); i += 50)
        {
                painter.drawLine(QPoint(i, 0), QPoint(i, 1000));
        }

        pen.setColor(QColor(255,255,255));
        pen.setWidth(2);
        painter.setPen(pen);


        for(int i = 0; i < static_cast<int>(subnetButtons.size()); i++)
        {
             QPoint a = networkButton->mapTo(this, networkButton->rect().center());
             int dist = subnetButtons.at(i)->rect().topLeft().y() - networkButton->rect().bottomLeft().y();
             QPoint b = QPoint((subnetButtons.at(i)->mapTo(this, QPoint(subnetButtons.at(i)->rect().center().x(), dist))));

             painter.drawLine(a, b);
             painter.drawLine(b, subnetButtons.at(i)->mapTo(this, subnetButtons.at(i)->rect().center()));
        }
    }
private:
    QPoint a;
    QPoint b;
    QWidget *scrollArea;

    NetworkButton *networkButton;
    QList<SubnetButton*> subnetButtons;

};

#endif // GRAPHFRAME_H
