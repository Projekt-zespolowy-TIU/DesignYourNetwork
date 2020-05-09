#include <catch2/catch.hpp>
#include <boost/dynamic_bitset.hpp>

#include "IPv4address.h"
#include "IPv4mask.h"
#include "coreUtils.h"

using namespace core;

namespace IPv4addressTests {
    TEST_CASE("IPv4address Tests"){
        const boost::dynamic_bitset <> bitset_ip {32, 3232235521} //192.168.0.1
        , bitset_mask1 {32, 4294967040} //255.255.255.0
        , bitset_mask2 {32, 4293918720}; //255.240.0.0

        const IPv4address ip4address {bitset_ip};
        const IPv4address mask1 {bitset_mask1};
        const IPv4address mask2 {bitset_mask2};

        SECTION("asStringDec conversion"){
            CHECK(ip4address.asStringDec() == "192.168.0.1");
            CHECK(mask2.asStringDec() == "255.240.0.0");
        };
        SECTION("asStringBin conversion"){
            CHECK(ip4address.asStringBin() == "11000000.10101000.00000000.00000001");
            CHECK(mask2.asStringBin() == "11111111.11110000.00000000.00000000");
        };
        SECTION("AND operation wit IP and mask"){
            const IPv4mask mask1 {bitset_mask1};
            const IPv4mask mask2 {bitset_mask2};

            std::shared_ptr<IPaddressBase> left = std::make_shared<IPv4address>(ip4address);
            std::shared_ptr<IPmaskBase> right = std::make_shared<IPv4mask>(mask1);

            auto expected = left & right;
            CHECK(expected->asStringDec() == "192.168.0.0");

            right = std::make_shared<IPv4mask>(mask2);
            expected = left & right;
            CHECK(expected->asStringDec() == "192.160.0.0");
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
            CHECK_THROWS_AS(IPv4address{boost::dynamic_bitset <> (33, 1)}, IPinvalidFormat);
            CHECK_THROWS_AS(IPv4address{boost::dynamic_bitset <> (25, 1)}, IPinvalidFormat);
        }
    };
};
