#ifndef NETWORKBUTTON_H
#define NETWORKBUTTON_H

#include <QPushButton>

#include "core/INetwork.h"

using namespace core;

class NetworkButton : public QPushButton
{
    Q_OBJECT

public:

    NetworkButton(const std::shared_ptr<INetwork>& net, QWidget* parent):
        QPushButton(parent),
        network(net)
    {
        connect(this, SIGNAL(clicked()), this, SLOT(handleClick()));
    }

signals:

    void clicked(std::shared_ptr<INetwork>);

private slots:

    void handleClick()
    {
        emit clicked(network);
    }

private:

        std::shared_ptr<INetwork> network;
};

#endif // NETWORKBUTTON_H
