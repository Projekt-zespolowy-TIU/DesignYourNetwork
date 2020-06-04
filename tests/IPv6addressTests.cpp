#include <catch2/catch.hpp>

#include <boost/dynamic_bitset.hpp>

#include "core/IPv6address.h"
#include "core/coreUtils.h"

using namespace core;

namespace IPv6addressTests {
    TEST_CASE("IPv6address Tests"){
        const boost::dynamic_bitset <> bitset_ip1 {
            std::string{"01001111111111100010100100000000"
                        "01010101010001010011001000010000"
                        "00100000000000001111100011111111"
                        "11111110001000010110011111001111"}
        } //4ffe:2900:5545:3210:2000:f8ff:fe21:67cf
        , bitset_ip2 {
            std::string{"11011110101011010000000000000000"
                        "00000000000000000000000000000000"
                        "00000000000000000000000000000000"
                        "00000000000000001011111011101111"}
        } //dead::beef
        , bitset_ip3 {
            std::string{"00000000000000000000000000000000"
                        "00000000000000000000000000000000"
                        "00000000000000000000000000000000"
                        "00000000000000000000000000000000"}
        }; //::

        const IPv6address ip6address {bitset_ip1};
        const IPv6address mask1 {bitset_ip2};
        const IPv6address mask2 {bitset_ip3};

        SECTION("asStringDec conversion"){
            CHECK(ip6address.asStringDec().toStdString() == "4ffe:2900:5545:3210:2000:f8ff:fe21:67cf");
            CHECK(mask1.asStringDec().toStdString() == "dead::beef");
            CHECK(mask2.asStringDec().toStdString() == "::");
        };
        SECTION("asStringBin conversion"){
            CHECK(ip6address.asStringBin().toStdString() == "0100111111111110:0010100100000000"
                                                            ":0101010101000101:0011001000010000"
                                                            ":0010000000000000:1111100011111111"
                                                            ":1111111000100001:0110011111001111");
            CHECK(mask1.asStringBin().toStdString() == "1101111010101101:0000000000000000"
                                                       ":0000000000000000:0000000000000000"
                                                       ":0000000000000000:0000000000000000"
                                                       ":0000000000000000:1011111011101111");
            CHECK(mask2.asStringBin().toStdString() == "0000000000000000:0000000000000000"
                                                       ":0000000000000000:0000000000000000"
                                                       ":0000000000000000:0000000000000000"
                                                       ":0000000000000000:0000000000000000");
        };
        SECTION("operator =="){
            IPv6address compareME{bitset_ip1};
            CHECK(ip6address == compareME);
        };
        SECTION("operator !="){
            CHECK(mask1 != mask2);
        };
        SECTION("Ctors validation should not throw"){
            CHECK_NOTHROW(IPv6address{bitset_ip1});
        }
        SECTION("Ctors validation should throw"){
            CHECK_THROWS_AS(IPv6address{boost::dynamic_bitset <> (129, 1)}, IPFormatExcept);
            CHECK_THROWS_AS(IPv6address{boost::dynamic_bitset <> (120, 1)}, IPFormatExcept);
        }
    };
};
