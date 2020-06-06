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

    GraphFrame( NetworkButton *networkButton, QList<SubnetButton*> subnetButtons,
                QList<QWidget*> hostsFrames, QWidget *scrollArea, QWidget *parent = NULL) : QFrame(parent){
         this->networkButton = networkButton;
         this->subnetButtons = subnetButtons;
         this->scrollArea = scrollArea;
         this->hostsFrames = hostsFrames;
     }

protected:

    void paintEvent( QPaintEvent * event){
        QFrame::paintEvent(event);
        QPainter painter = QPainter(this);
        QPen pen = QPen(QColor(38,94,84).lighter());
        painter.setPen(pen);

        for(int i = 0 ; i < scrollArea->width(); i += 30)
        {
                painter.drawLine(QPoint(0, i), QPoint(1000, i));
        }

        for(int i = 0 ; i < scrollArea->height(); i += 30)
        {
                painter.drawLine(QPoint(i, 0), QPoint(i, 1000));
        }

        pen.setColor(QColor(255,255,255));
        pen.setWidth(3);
        painter.setPen(pen);


        for(int i = 0; i < static_cast<int>(subnetButtons.size()); i++)
        {
             QPoint a = networkButton->mapTo(this, networkButton->rect().center());
             QPoint b = networkButton->mapTo(this, QPoint(0, networkButton->rect().center().y()));
             QPoint c = subnetButtons.at(i)->mapTo(this, QPoint(subnetButtons.at(i)->rect().center().x(), 0));

             QPoint d = QPoint(c.x(), b.y());
             QPoint e = hostsFrames.at(i)->mapTo(this, QPoint(hostsFrames.at(i)->rect().center().x(),
                                                                hostsFrames.at(i)->rect().topRight().y()));
             painter.drawLine(a, d);
             painter.drawLine(d, subnetButtons.at(i)->mapTo(this, subnetButtons.at(i)->rect().center()));
             painter.drawLine(subnetButtons.at(i)->mapTo(this, subnetButtons.at(i)->rect().center()), e);
        }
    }
private:
    QPoint a;
    QPoint b;
    QWidget *scrollArea;

    NetworkButton *networkButton;
    QList<SubnetButton*> subnetButtons;
    QList<QWidget*> hostsFrames;

};

#endif // GRAPHFRAME_H
