#include <catch2/catch.hpp>
#include <exception>
#include <boost/dynamic_bitset.hpp>
#include <vector>

#include "IPv4address.h"
#include "IPv4parser.h"
#include "IPv4mask.h"

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
}
