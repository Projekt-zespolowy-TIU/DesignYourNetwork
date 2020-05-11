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
    try {
        std::cin >> mainNetwork.Ip;
    } catch (const IPFormatExcept& e) {
        std::cout << "\nException: " << e.what();
        return 1; //should return something more meaningful
    }

    std::cout << "Podaj maske IPv4 sieci glownej: ";
    try {
        std::cin >> mainNetwork.NetMask;
    } catch (const IPFormatExcept& e) {
        std::cout << "\nException: " << e.what();
        return 1; //TODO: should return something more meaningful
    }

    if(mainNetwork.isHost(*mainNetwork.Ip)) //without this UNDEFINED BEHAVIOR
    {
        mainNetwork.fix();
    }

    std::cout << "Ile sieci zaadresowac?: ";
    int networkNumber = 0;
    std::cin >> networkNumber;

    std::vector<std::shared_ptr<Subnet>> subnets;

    for(int i = 0; i < networkNumber; i++)
    {
        Subnetv4 tempSubnet;
        std::cout << "Podaj nazwe podsieci [" << i << "]: ";
        std::cin >> tempSubnet.SubName;
        std::cout << "Ilosc hostow w podsieci [" << i << "]: ";
        std::cin >> tempSubnet.HostNumber;
        subnets.push_back(std::make_shared<Subnetv4>(tempSubnet));
    }

    SubnetsCalculatorV4 calc;

    try {
        calc.calcSubnets(mainNetwork, subnets);
    } catch (const IPSubnetworkExcept& e) {
        std::cout << "\nException: " << e.what();
        return 1; //TODO: should return something more meaningful
    }

    for(const auto& sub : subnets)
    {
        std::cout << "\nNazwa podsieci: " << sub->SubName // print subnetwork name instead
                  << " IP: " << *sub->Ip
                  << " Maska: " << *sub->NetMask;
    }

    return a.exec();
}
