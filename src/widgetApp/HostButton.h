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

    HostButton(Subnet::Host host)
    {
        this->host = host;
        connect(this, SIGNAL(clicked()), this, SLOT(handleClick()));
    }

signals:
    void clicked(Subnet::Host);

private slots:

    void handleClick()
    {
        emit clicked(host);
    }

private:

        Subnet::Host host;
};
