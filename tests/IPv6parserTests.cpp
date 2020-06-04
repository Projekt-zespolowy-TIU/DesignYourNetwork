#include <catch2/catch.hpp>

#include "core/IPv6parser.h"
#include "core/coreUtils.h"

using namespace core;

namespace IPv6parserTest {
    TEST_CASE("IPv6parser Tests"){
        const IPv6parser ip6parser;

        SECTION("Parsing string with valid ip address"){
            CHECK_NOTHROW(ip6parser.ipFromString("4ffe:2900:5545:3210:2000:f8ff:fe21:67cf"));
            CHECK_NOTHROW(ip6parser.ipFromString("ffff:ffff::"));
            CHECK_NOTHROW(ip6parser.ipFromString("fe80::"));
            CHECK_NOTHROW(ip6parser.ipFromString("fe80::1"));
        };
        SECTION("Parsing string with invalid ip address"){
            CHECK_THROWS_AS(ip6parser.ipFromString("fe80:g::"), IPFormatExcept);
            CHECK_THROWS_AS(ip6parser.ipFromString("fe80::/64"), IPFormatExcept);
            CHECK_THROWS_AS(ip6parser.ipFromString("foobar"), IPFormatExcept);
        };
    };
};
