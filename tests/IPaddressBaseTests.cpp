#include <catch2/catch.hpp>
#include <boost/dynamic_bitset.hpp>

#include "IPaddressBase.h"

using namespace core;

namespace IPaddressBaseTests {
    TEST_CASE("IPaddressBase Tests"){
        const boost::dynamic_bitset <> bitset_ip {32, 3232235521} //192.168.0.1
        , bitset_mask1 {32, 4294967040} //255.255.255.0
        , bitset_mask2 {32, 4293918720}; //255.240.0.0

        const IPaddressBase ip4address {bitset_ip};
        const IPaddressBase mask1 {bitset_mask1};
        const IPaddressBase mask2 {bitset_mask2};

        SECTION("asStringDec conversion"){
            REQUIRE(ip4address.asStringDec() == "192.168.0.1");
            REQUIRE(mask2.asStringDec() == "255.240.0.0");
        };
        SECTION("asStringBin conversion"){
            REQUIRE(ip4address.asStringBin() == "11000000.10101000.00000000.00000001");
            REQUIRE(mask2.asStringBin() == "11111111.11110000.00000000.00000000");
        };
        SECTION("AND operation wit IP and mask"){
            IPaddressBase expected = ip4address & mask1;
            CHECK(expected.asStringDec() == "192.168.0.0");
            expected = ip4address & mask2;
            CHECK(expected.asStringDec() == "192.160.0.0");
        };
        SECTION("operator =="){
            const IPaddressBase compareME{bitset_ip};
            CHECK(ip4address == compareME);
        };
        SECTION("operator !="){
            CHECK(mask1 != mask2);
        };
    };
};
