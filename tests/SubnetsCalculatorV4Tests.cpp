#include <catch2/catch.hpp>
#include <boost/dynamic_bitset.hpp>
#include <vector>
#include <memory>
#include <algorithm>

#include "SubnetsCalculatorV4.h"

using namespace core;

namespace SubnetsCalculatorV4Tests {
    TEST_CASE("SubnetsCalculatorV4 Tests"){
        Networkv4 net;
        std::vector<std::shared_ptr<Subnet>> subs;

        SECTION("Subneting with constant mask length")
        {
            *net.Ip = IPv4address{boost::dynamic_bitset<>(32, 3232235520)}; //192.168.0.0
            *net.NetMask = IPv4mask{boost::dynamic_bitset<>(32, 4294967232)}; //255.255.255.192 /26

            for(unsigned short i = 0; i <= 4; i++)
            {
                subs.push_back(std::make_shared<Subnetv4>());
                subs.back()->HostNumber = 10;
            };

            SubnetsCalculatorV4 calc;
            calc.calcSubnets(net, subs);

            for(const auto& sub : subs)
                CHECK(sub->NetMask->asStringDec() == "255.255.255.240");

            std::vector<QString> calculatedNetworks;
            calculatedNetworks.emplace_back("192.168.0.0");
            calculatedNetworks.emplace_back("192.168.0.16");
            calculatedNetworks.emplace_back("192.168.0.32");
            calculatedNetworks.emplace_back("192.168.0.48");

            for(const auto& var : calculatedNetworks)
                CHECK(std::any_of(subs.begin(), subs.end(), [&var](const auto& x){
                    return x->Ip->asStringDec() == var;
                }));
        };
    };
};
