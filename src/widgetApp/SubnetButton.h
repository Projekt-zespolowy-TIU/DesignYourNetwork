#ifndef SUBNETBUTTON_H
#define SUBNETBUTTON_H

#include <QPushButton>

#include "core/Subnetv4.h"

using namespace core;

class SubnetButton : public QPushButton
{
    Q_OBJECT

public:

    SubnetButton(std::shared_ptr<ISubnet> subnet):
        subnet(subnet)
    {
        connect(this, SIGNAL(clicked()), this, SLOT(handleClick()));
    }

signals:

    void clicked(std::shared_ptr<ISubnet>);

private slots:

    void handleClick()
    {
        emit clicked(subnet);
    }

private:
        std::shared_ptr<ISubnet> subnet;
};

#endif // SUBNETBUTTON_H
