#ifndef NETWORKBUTTON_H
#define NETWORKBUTTON_H

#include <QPushButton>

#include "core/Networkv4.h"

using namespace core;

class NetworkButton : public QPushButton
{
    Q_OBJECT

public:

    NetworkButton(Networkv4 network):
        network(network)
    {
        connect(this, SIGNAL(clicked()), this, SLOT(handleClick()));
    }

signals:

    void clicked(Networkv4);

private slots:

    void handleClick()
    {
        emit clicked(network);
    }

private:

        Networkv4 network;
};

#endif // NETWORKBUTTON_H
