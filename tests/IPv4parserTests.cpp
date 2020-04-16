#include <catch2/catch.hpp>
#include <exception>
#include <boost/dynamic_bitset.hpp>
#include <vector>

#include "IPv4address.h"
#include "IPv4parser.h"
#include "IPv4mask.h"
#include "SubnetsCalculatorV4.h"

using namespace core;

namespace IPv4parserTest {
    TEST_CASE("IPv4parser Tests"){
        IPv4parser ip4parser;

        SECTION("Parsing string with valid ip address into IP object"){
            REQUIRE_NOTHROW(ip4parser.ipFromString("192.168.0.1"));
        }
        SECTION("Parsing string with invalid ip address into IP object"){
            REQUIRE_THROWS_AS(ip4parser.ipFromString("192.168.0.256"), std::nested_exception);
            REQUIRE_THROWS_AS(ip4parser.ipFromString("192.168.0.255/21"), std::nested_exception);
            REQUIRE_THROWS_AS(ip4parser.ipFromString("foobar"), std::nested_exception);
            REQUIRE_THROWS_AS(ip4parser.ipFromString("fe80::1"), std::nested_exception);
        }
    }

    TEST_CASE("IPaddressBase Tests"){
        const boost::dynamic_bitset <> bitset_ip {32, 3232235521} //192.168.0.1
        , bitset_mask1 {32, 4294967040} //255.255.255.0
        , bitset_mask2 {32, 4293918720}; //255.240.0.0

        IPaddressBase ip4address {bitset_ip};
        IPaddressBase mask1 {bitset_mask1};
        IPaddressBase mask2{bitset_mask2};

        SECTION("asStringDec conversion"){
            REQUIRE(ip4address.asStringDec() == "192.168.0.1");
            REQUIRE(mask2.asStringDec() == "255.240.0.0");
        }
        SECTION("AND operation wit IP and mask"){
            IPaddressBase expected = ip4address & mask1;
            CHECK(expected.asStringDec() == "192.168.0.0");
            expected = ip4address & mask2;
            CHECK(expected.asStringDec() == "192.160.0.0");
        }
    }

    TEST_CASE("IPv4mask Tests"){
        WHEN("Mask is valid format"){
            const std::vector<boost::dynamic_bitset<>> bitsets {
            boost::dynamic_bitset<> {32, 4294967295} //255.255.255.255
            , boost::dynamic_bitset<> {32, 2147483648} //128.0.0.0
            , boost::dynamic_bitset<> {32, 0} //0.0.0.0
            };

            for(const auto &element : bitsets)
            {
                std::string temps;
                to_string(element, temps);
                THEN(std::string("Object created: ") + temps){
                    REQUIRE_NOTHROW(IPv4mask{element});
                }
            }
        }
        WHEN("Mask is invalid format"){
            boost::dynamic_bitset<> bitset_ip{32, 3232235521}; //192.168.0.1
            THEN("Ctor throws error"){
                REQUIRE_THROWS_AS(IPv4mask{bitset_ip}, std::invalid_argument);
            }
        }
    }

    TEST_CASE("SubnetsCalculatorV4 Tests"){
        std::shared_ptr<NetworkBase> net = std::make_shared<Networkv4>();
        std::vector<std::shared_ptr<Subnet>> subs;

        SECTION("Subneting with constant mask length")
        {
            *net->Ip = IPv4address{boost::dynamic_bitset<>(32, 3232235520)}; //192.168.0.0
            *net->NetMask = IPv4mask{boost::dynamic_bitset<>(32, 4294967232)}; //255.255.255.192 /26

            for(unsigned short i = 0; i <= 4; i++)
            {
                subs.push_back(std::make_shared<Subnetv4>());
                subs.back()->HostNumber = 10;
            }

            SubnetsCalculatorV4 calc;
            calc.calcSubnets(net, subs);

            for(const auto& sub : subs)
                CHECK(sub->NetMask->asStringDec() == "255.255.255.240");

            std::vector<std::string> calculatedNetworks;
            calculatedNetworks.emplace_back("192.168.0.0");
            calculatedNetworks.emplace_back("192.168.0.16");
            calculatedNetworks.emplace_back("192.168.0.32");
            calculatedNetworks.emplace_back("192.168.0.48");

            for(const auto& var : calculatedNetworks)
                CHECK(std::any_of(subs.begin(), subs.end(), [&var](std::shared_ptr<Subnet> x){
                    return x->Ip->asStringDec() == var;
                }));
        }
    }
}
