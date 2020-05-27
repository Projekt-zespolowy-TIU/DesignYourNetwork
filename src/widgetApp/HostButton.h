#ifndef HOSTBUTTON_H
#define HOSTBUTTON_H

#endif // HOSTBUTTON_H

#pragma once

#include <QPushButton>

#include "IPstructs.h"

using namespace core;

class HostButton : public QPushButton
{
    Q_OBJECT

public:
    HostButton(Networkv4 network)
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
