#include <QCoreApplication>
#include <iostream>

#include "IPv4address.h"
#include "IPv4parser.h"

using namespace core;

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    IPv4address addressIPv4;

    std::cout << "Podaj adres IPv4: ";    
    std::cin >> addressIPv4;
    std::cout << "Adres binarnie: " << addressIPv4;

    return a.exec();
}
