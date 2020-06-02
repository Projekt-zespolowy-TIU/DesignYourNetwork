#ifndef SUBNETBUTTON_H
#define SUBNETBUTTON_H

#include <QPushButton>

#include "core/Subnetv4.h"

using namespace core;

class SubnetButton : public QPushButton
{
    Q_OBJECT

public:

    SubnetButton(Subnetv4 subnet):
        subnet(subnet)
    {
        connect(this, SIGNAL(clicked()), this, SLOT(handleClick()));
    }

signals:

    void clicked(Subnetv4);

private slots:

    void handleClick()
    {
        emit clicked(subnet);
    }

private:
        Subnetv4 subnet;
};

#endif // SUBNETBUTTON_H
