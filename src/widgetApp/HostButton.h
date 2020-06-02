#ifndef HOSTBUTTON_H
#define HOSTBUTTON_H

#include <QPushButton>

#include "core/Host.h"

using namespace core;

class HostButton : public QPushButton
{
    Q_OBJECT

public:

    HostButton(std::shared_ptr<Host> host, QWidget* parent):
        QPushButton(parent),
        host(host)
    {
        connect(this, SIGNAL(clicked()), this, SLOT(handleClick()));
    }

signals:
    void clicked(std::shared_ptr<Host>);

private slots:

    void handleClick()
    {
        emit clicked(host);
    }

private:

        std::shared_ptr<Host> host;
};

#endif // HOSTBUTTON_H
