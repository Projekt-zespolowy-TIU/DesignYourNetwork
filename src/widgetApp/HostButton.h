#ifndef HOSTBUTTON_H
#define HOSTBUTTON_H

#include <QPushButton>

#include "core/Host.h"

using namespace core;

class HostButton : public QPushButton
{
    Q_OBJECT

public:

    HostButton(Host host):
        host(host)
    {
        this->host = host;
        connect(this, SIGNAL(clicked()), this, SLOT(handleClick()));
    }

signals:
    void clicked(Host);

private slots:

    void handleClick()
    {
        emit clicked(host);
    }

private:

        Host host;
};

#endif // HOSTBUTTON_H
