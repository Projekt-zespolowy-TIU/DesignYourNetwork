#include <iostream>
#include <vector>
#include <memory>
#include <string>
#include <QCoreApplication>

#include "core/IPv4address.h"
#include "core/IPv4mask.h"
#include "core/Networkv4.h"
#include "core/SubnetsCalculatorV4.h"
#include "core/coreUtils.h"
#include "core/ReportGeneratorV4.h"

using namespace core;

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    IPv4address address;
    IPv4mask mask;

    std::cout << "Podaj adres IPv4 sieci glownej: ";
    try {
        std::cin >> address;
    } catch (const IPFormatExcept& e) {
        std::cout << "\nException: " << e.what() << '\n';
        return 1; //TODO: should return something more meaningful
    }

    std::cout << "Podaj maske IPv4 sieci glownej: ";
    try {
        std::cin >> mask;
    } catch (const IPFormatExcept& e) {
        std::cout << "\nException: " << e.what() << '\n';
        return 1; //TODO: should return something more meaningful
    }

    Networkv4 mainNetwork{address, mask};

    std::cout << "IP sieci glownej: " << mainNetwork.Ip() << '\n'
              << "Maska sieci glownej: " << mainNetwork.Mask() << '\n';

    std::cout << "Ile sieci zaadresowac?: ";
    int networkNumber = 0;
    std::cin >> networkNumber;

    for(int i = 0; i < networkNumber; i++)
    {
        std::cout << "Podaj nazwe podsieci [" << i << "]: ";
        QString subname;
        std::cin >> subname;
        std::cout << "Ilosc hostow w podsieci [" << i << "]: ";
        cpp_int hostNumber;
        std::cin >> hostNumber;
        mainNetwork.addSubnet(hostNumber, subname);
    }

    SubnetsCalculatorV4 calc;

    try {
        calc.calcSubnets(mainNetwork);
    } catch (const SubnetExcept& e) {
        std::cout << "\nException: " << e.what() << '\n';
        return 1; //TODO: should return something more meaningful
    }

    std::unique_ptr<IReportGenerator> reportGenerator = std::make_unique<ReportGeneratorV4>();

    reportGenerator->generate(mainNetwork, DetaiLevel::Detailed);

    std::cout << reportGenerator->getReport();

    reportGenerator->save("mainNetwork.txt");

    return a.exec();
}
