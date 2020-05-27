#include <catch2/catch.hpp>

#include <vector>
#include <memory>
#include <algorithm>
#include <string>
#include <boost/dynamic_bitset.hpp>

#include "core/SubnetsCalculatorV4.h"

using namespace core;

namespace SubnetsCalculatorV4Tests {
    TEST_CASE("SubnetsCalculatorV4 Integration Tests"){
        SECTION("Subneting with the same number of hosts")
        {
            auto ip = IPv4address{boost::dynamic_bitset<>(32, 3'232'235'520)}; //192.168.0.0
            auto mask = IPv4mask{boost::dynamic_bitset<>(32, 4'294'967'232)}; //255.255.255.192 /26

            Networkv4 net{ip,mask};

            net.addSubnet(10);
            net.addSubnet(10);
            net.addSubnet(10);
            net.addSubnet(10);

            SubnetsCalculatorV4 calc;
            REQUIRE_NOTHROW(calc.calcSubnets(net));

            SECTION("Check mask addresses"){
                for(const auto& sub : net.Subnets())
                    CHECK(sub.Mask().asStringDec().toStdString() == "255.255.255.240");
            };

            SECTION("Check ip addresses"){
                std::vector<std::string> calculatedNetworks{
                    "192.168.0.0",
                    "192.168.0.16",
                    "192.168.0.32",
                    "192.168.0.48"
                };

                auto subs = net.Subnets();

                for(const auto& var : calculatedNetworks)
                    CHECK(std::any_of(subs.begin(), subs.end(), [&var](const auto& x){
                        return x.Ip().asStringDec().toStdString() == var;
                    }));
            };

        };
        SECTION("Subneting with the STS exam data")
        {
            auto ip = IPv4address{boost::dynamic_bitset<>(32, 391851264)}; //23.91.45.0
            auto mask = IPv4mask{boost::dynamic_bitset<>(32, 4294967040)}; //255.255.255.0 /24

            Networkv4 net{ip, mask};

            net.addSubnet(31); //1
            net.addSubnet(30); //2
            net.addSubnet(7); //3
            net.addSubnet(6); //4
            net.addSubnet(2); //5
            net.addSubnet(2); //6

            SubnetsCalculatorV4 calc;
            REQUIRE_NOTHROW(calc.calcSubnets(net));

            auto subs = net.Subnets();

            SECTION("Check mask addresses"){
                std::vector<std::string> calculatedMasks{
                    "255.255.255.192", //1
                    "255.255.255.224", //2
                    "255.255.255.240", //3
                    "255.255.255.248", //4
                    "255.255.255.252", //5
                    "255.255.255.252" //6
                };

                for(size_t i = 0; i < 6; i++)
                    CHECK(subs.at(i).Mask().asStringDec().toStdString() == calculatedMasks.at(i));
            };

            SECTION("Check ip addresses"){
                std::vector<std::string> calculatedIPs{
                    "23.91.45.0", //1
                    "23.91.45.64", //2
                    "23.91.45.96", //3
                    "23.91.45.112", //4
                    "23.91.45.120", //5
                    "23.91.45.124" //6
                };

                for(size_t i = 0; i < 6; i++){
                    CHECK(subs.at(i).Ip().asStringDec().toStdString() == calculatedIPs.at(i));
                }
            }

            SECTION("Check host's IPs"){
                REQUIRE(subs.at(2).HostsList().size() == 7);
                CHECK(subs.at(2).HostsList().at(0).Ip().asStringDec().toStdString() == "23.91.45.97"); //1
                CHECK(subs.at(2).HostsList().at(1).Ip().asStringDec().toStdString() == "23.91.45.98"); //2
                CHECK(subs.at(2).HostsList().at(2).Ip().asStringDec().toStdString() == "23.91.45.99"); //3
                CHECK(subs.at(2).HostsList().at(3).Ip().asStringDec().toStdString() == "23.91.45.100"); //4
                CHECK(subs.at(2).HostsList().at(4).Ip().asStringDec().toStdString() == "23.91.45.101"); //5
                CHECK(subs.at(2).HostsList().at(5).Ip().asStringDec().toStdString() == "23.91.45.102"); //6
                CHECK(subs.at(2).HostsList().at(6).Ip().asStringDec().toStdString() == "23.91.45.103"); //7
            }
        };
    };
};
