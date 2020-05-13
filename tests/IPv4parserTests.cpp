#include <catch2/catch.hpp>
#include <stdexcept>
#include <boost/dynamic_bitset.hpp>

#include "IPv4parser.h"

using namespace core;

namespace IPv4parserTest {
    TEST_CASE("IPv4parser Tests"){
        const IPv4parser ip4parser;

        SECTION("Parsing string with valid ip address into IP object"){
            CHECK_NOTHROW(ip4parser.ipFromString("192.168.0.1"));
        };
        SECTION("Parsing string with invalid ip address"){
            CHECK_THROWS_AS(ip4parser.ipFromString("192.168.0.256"), std::nested_exception);
            CHECK_THROWS_AS(ip4parser.ipFromString("192.168.0.255/21"), std::nested_exception);
            CHECK_THROWS_AS(ip4parser.ipFromString("foobar"), std::nested_exception);
            CHECK_THROWS_AS(ip4parser.ipFromString("fe80::1"), std::nested_exception);
        };

        SECTION("Parsing string with valid ip mask address into IPmask object"){
            CHECK_NOTHROW(ip4parser.ipMaskFromString("255.255.255.128"));
        };
        SECTION("Parsing string with invalid ip mask address"){
            CHECK_THROWS_AS(ip4parser.ipMaskFromString("255.256.0.0"), std::nested_exception);
            CHECK_THROWS_AS(ip4parser.ipMaskFromString("255.0.0.0/21"), std::nested_exception);
            CHECK_THROWS_AS(ip4parser.ipMaskFromString("foobar"), std::nested_exception);
            CHECK_THROWS_AS(ip4parser.ipMaskFromString("fe80::1"), std::nested_exception);
        };
    };
};
