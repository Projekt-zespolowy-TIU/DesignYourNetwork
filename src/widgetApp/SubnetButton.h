#ifndef SUBNETBUTTON_H
#define SUBNETBUTTON_H

#endif // SUBNETBUTTON_H

#pragma once

#include <QPushButton>

#include "IPstructs.h"

using namespace core;

class SubnetButton : public QPushButton
{
    Q_OBJECT

public:

    SubnetButton(std::shared_ptr<Subnet> subnet)
    {
        this->subnet = subnet;
        connect(this, SIGNAL(clicked()), this, SLOT(handleClick()));

    }

signals:

    void clicked(std::shared_ptr<Subnet>);

private slots:

    void handleClick()
    {
        emit clicked(subnet);
    }

private:
        std::shared_ptr<Subnet> subnet;
};
