#include <QCoreApplication>
#include <iostream>
#include <vector>
#include <memory>
#include <QTextStream>
#include <string>

#include "IPstructs.h"
#include "SubnetsCalculatorV4.h"
#include "coreUtils.h"

using namespace core;

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    Networkv4 mainNetwork;

    std::cout << "Podaj adres IPv4 sieci glownej: ";
    std::cin >> mainNetwork.Ip;
    std::cout << "Podaj maske IPv4 sieci glownej: ";
    std::cin >> mainNetwork.NetMask;

    if(*mainNetwork.Ip != *(mainNetwork.Ip & mainNetwork.NetMask))
    {
        throw NotImplemented{"TODO: error handling"}; //check if passed address is network address
    }

    std::cout << "Ile sieci zaadresowac?: ";
    int networkNumber = 0;
    std::cin >> networkNumber;

    std::vector<std::shared_ptr<Subnet>> subnets;

    for(int i = 0; i< networkNumber; i++)
    {
        Subnetv4 tempSubnet;
        std::cout << "Podaj nazwe podsieci [" << i << "]: ";
        std::cin >> tempSubnet.SubName;
        std::cout << "Ilosc hostow w podsieci [" << i << "]: ";
        std::cin >> tempSubnet.HostNumber;
        subnets.push_back(std::make_shared<Subnetv4>(tempSubnet));
    }

    SubnetsCalculatorV4 calc;

    calc.calcSubnets(mainNetwork, subnets);

    for(int i = 0; i < networkNumber; i++)
    {
        std::cout << "\nPodsiec [" << i << "] - "
                  << "Nazwa podsieci: " << subnets.at(i)->SubName
                  << " IP: " << *subnets.at(i)->Ip
                  << " Maska: " << *subnets.at(i)->NetMask;
    }

    return a.exec();
}
