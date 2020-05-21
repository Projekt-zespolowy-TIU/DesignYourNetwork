#include <catch2/catch.hpp>
#include <boost/dynamic_bitset.hpp>
#include <vector>
#include <memory>
#include <algorithm>
#include <string>

#include "SubnetsCalculatorV4.h"

using namespace core;

namespace SubnetsCalculatorV4Tests {
    TEST_CASE("SubnetsCalculatorV4 Tests"){
        Networkv4 net;
        std::vector<std::shared_ptr<Subnet>> subs;

        SECTION("Subneting with the same number of hosts")
        {
            *net.Ip = IPv4address{boost::dynamic_bitset<>(32, 3232235520)}; //192.168.0.0
            *net.NetMask = IPv4mask{boost::dynamic_bitset<>(32, 4294967232)}; //255.255.255.192 /26

            subs.push_back(std::make_shared<Subnetv4>());
            subs.back()->HostNumber = 10;
            subs.push_back(std::make_shared<Subnetv4>());
            subs.back()->HostNumber = 10;
            subs.push_back(std::make_shared<Subnetv4>());
            subs.back()->HostNumber = 10;
            subs.push_back(std::make_shared<Subnetv4>());
            subs.back()->HostNumber = 10;

            SubnetsCalculatorV4 calc;
            REQUIRE_NOTHROW(calc.calcSubnets(net, subs));

            SECTION("Check mask addresses"){
                for(const auto& sub : subs)
                    CHECK(sub->NetMask->asStringDec().toStdString() == "255.255.255.240");
            };

            SECTION("Check ip addresses"){
                std::vector<std::string> calculatedNetworks{
                    "192.168.0.0",
                    "192.168.0.16",
                    "192.168.0.32",
                    "192.168.0.48"
                };

                for(const auto& var : calculatedNetworks)
                    CHECK(std::any_of(subs.begin(), subs.end(), [&var](const auto& x){
                        return x->Ip->asStringDec().toStdString() == var;
                    }));
            };
        };
        SECTION("Subneting with the STS exam data")
        {
            *net.Ip = IPv4address{boost::dynamic_bitset<>(32, 391851264)}; //23.91.45.0
            *net.NetMask = IPv4mask{boost::dynamic_bitset<>(32, 4294967040)}; //255.255.255.0 /24

            subs.push_back(std::make_shared<Subnetv4>()); //1
            subs.back()->HostNumber = 31;
            subs.push_back(std::make_shared<Subnetv4>()); //2
            subs.back()->HostNumber = 30;
            subs.push_back(std::make_shared<Subnetv4>()); //3
            subs.back()->HostNumber = 7;
            subs.push_back(std::make_shared<Subnetv4>()); //4
            subs.back()->HostNumber = 6;
            subs.push_back(std::make_shared<Subnetv4>()); //5
            subs.back()->HostNumber = 2;
            subs.push_back(std::make_shared<Subnetv4>()); //6
            subs.back()->HostNumber = 2;

            SubnetsCalculatorV4 calc;
            REQUIRE_NOTHROW(calc.calcSubnets(net, subs));

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
                    CHECK(subs.at(i)->NetMask->asStringDec().toStdString() == calculatedMasks.at(i));
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
                    CHECK(subs.at(i)->Ip->asStringDec().toStdString() == calculatedIPs.at(i));
                };
            };
        };
    };
};
