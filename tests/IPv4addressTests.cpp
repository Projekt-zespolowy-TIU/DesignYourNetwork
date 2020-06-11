#include <catch2/catch.hpp>

#include <boost/dynamic_bitset.hpp>

#include "core/IPv4address.h"
#include "core/IPv4mask.h"
#include "core/coreUtils.h"

using namespace core;

namespace IPv4addressTests {
    TEST_CASE("IPv4address Tests"){
        const boost::dynamic_bitset <> bitset_ip {32, 3'232'235'521} //192.168.0.1
        , bitset_mask1 {32, 4'294'967'040} //255.255.255.0
        , bitset_mask2 {32, 4'293'918'720}; //255.240.0.0

        const IPv4address ip4address {bitset_ip};
        const IPv4address mask1 {bitset_mask1};
        const IPv4address mask2 {bitset_mask2};

        SECTION("asStringDec conversion"){
            CHECK(ip4address.asStringDec().toStdString() == "192.168.0.1");
            CHECK(mask2.asStringDec().toStdString() == "255.240.0.0");
        };
        SECTION("asStringBin conversion"){
            CHECK(ip4address.asStringBin().toStdString() == "11000000.10101000.00000000.00000001");
            CHECK(mask2.asStringBin().toStdString() == "11111111.11110000.00000000.00000000");
        };
        SECTION("AND operation wit IP and mask"){
            const IPv4mask mask1 {bitset_mask1};
            const IPv4mask mask2 {bitset_mask2};

            IPv4address left = ip4address;
            IPv4mask right = mask1;

            IPv4address expected = left & right;
            CHECK(expected.asStringDec().toStdString() == "192.168.0.0");

            right = mask2;
            expected = left & right;
            CHECK(expected.asStringDec().toStdString() == "192.160.0.0");
        };
        SECTION("operator =="){
            IPv4address compareME{bitset_ip};
            CHECK(ip4address == compareME);
        };
        SECTION("operator !="){
            CHECK(mask1 != mask2);
        };
        SECTION("Ctors validation should not throw"){
            CHECK_NOTHROW(IPv4address{bitset_ip});
        }
        SECTION("Ctors validation should throw"){
            CHECK_THROWS_AS(IPv4address{boost::dynamic_bitset <> (33, 1)}, IPFormatExcept);
            CHECK_THROWS_AS(IPv4address{boost::dynamic_bitset <> (25, 1)}, IPFormatExcept);
        }
    };
};
