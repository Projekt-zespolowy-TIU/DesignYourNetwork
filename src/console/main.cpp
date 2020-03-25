#include <QCoreApplication>
#include <iostream>

#include "ipv4add.h"
#include "ipv4parser.h"

using namespace core;

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    ipv4add addressIPv4;

    std::cout << "Podaj adres IPv4: ";    
    std::cin >> addressIPv4;
    std::cout << "Adres binarnie: " << addressIPv4;

    return a.exec();
}
