#include <catch2/catch.hpp>
#include <exception>
#include <boost/dynamic_bitset.hpp>

#include "IPv4address.h"
#include "IPv4parser.h"

using namespace core;

namespace IPv4parserTest {
    TEST_CASE("IPv4parser Tests"){
        const IPv4parser ip4parser;

        SECTION("Parsing string with valid ip address into IP object"){
            REQUIRE_NOTHROW(ip4parser.ipFromString("192.168.0.1"));
        };
        SECTION("Parsing string with invalid ip address into IP object"){
            REQUIRE_THROWS_AS(ip4parser.ipFromString("192.168.0.256"), std::nested_exception);
            REQUIRE_THROWS_AS(ip4parser.ipFromString("192.168.0.255/21"), std::nested_exception);
            REQUIRE_THROWS_AS(ip4parser.ipFromString("foobar"), std::nested_exception);
            REQUIRE_THROWS_AS(ip4parser.ipFromString("fe80::1"), std::nested_exception);
        };
    };
};
