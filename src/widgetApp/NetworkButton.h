#ifndef NETWORKBUTTON_H
#define NETWORKBUTTON_H

#endif // NETWORKBUTTON_H

#pragma once

#include <QPushButton>
#include "IPstructs.h"

using namespace core;

class NetworkButton : public QPushButton
{
    Q_OBJECT

public:
    NetworkButton(Networkv4 network)
    {
        this->network = network;
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
