#ifndef NETWORKBUTTON_H
#define NETWORKBUTTON_H

#include <QPushButton>

#include "core/Networkv4.h"

using namespace core;

class NetworkButton : public QPushButton
{
    Q_OBJECT

public:

    NetworkButton(std::shared_ptr<Networkv4> net, QWidget* parent):
        QPushButton(parent),
        network(net)
    {
        connect(this, SIGNAL(clicked()), this, SLOT(handleClick()));
    }

signals:

    void clicked(std::shared_ptr<Networkv4>);

private slots:

    void handleClick()
    {
        emit clicked(network);
    }

private:

        std::shared_ptr<Networkv4> network;
};

#endif // NETWORKBUTTON_H
