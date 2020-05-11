#include <catch2/catch.hpp>
#include <boost/dynamic_bitset.hpp>
#include <vector>
#include <string>

#include "IPv4mask.h"
#include "coreUtils.h"

using namespace core;

namespace IPv4maskTests {
    TEST_CASE("IPv4mask Tests"){
        WHEN("Mask is valid format"){
            const std::vector<boost::dynamic_bitset<>> bitsets {
            boost::dynamic_bitset<> {32, 4294967295} //255.255.255.255
            , boost::dynamic_bitset<> {32, 2147483648} //128.0.0.0
            , boost::dynamic_bitset<> {32, 0} //0.0.0.0
            };

            for(const auto& element : bitsets)
            {
                std::string temps;
                to_string(element, temps);
                THEN(std::string{"Object created: "} + temps){
                    CHECK_NOTHROW(IPv4mask{element});
                };
            };
        };
        WHEN("Mask is invalid format"){
            boost::dynamic_bitset<> bitset_ip{32, 3232235521}; //192.168.0.1
            THEN("Ctor throws error"){
                CHECK_THROWS_AS(IPv4mask{bitset_ip}, IPFormatExcept);
            };
        };
        SECTION("Get proper ipv4 prefix"){
            CHECK(IPv4mask(boost::dynamic_bitset<> {32, 4294967232}).getPrefix() == 26); //255.255.255.255
        };
        SECTION("Default constructed mask should have all bit set to 1"){
            CHECK(IPv4mask{}.getPrefix() == 32);
        };
    };
};
