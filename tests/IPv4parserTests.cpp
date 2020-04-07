#include <catch2/catch.hpp>

#include "IPv4address.h"
#include "IPv4parser.h"

using namespace core;

namespace IPv4parserTest {
    TEST_CASE("IPv4parser Tests"){
        SECTION("Parsowanie IP z postaci tekstowej decimal na postac binarna"){
            const boost::dynamic_bitset<> converted = IPv4parser::stringDecimal2octets("192.168.0.1");
            const boost::dynamic_bitset<> expected = boost::dynamic_bitset<>(32, 0b11000000101010000000000000000001);
            REQUIRE(converted == expected); //11000000 10101000 00000000 00000001
        }

        SECTION("Parsowanie postaci binarnej na string (rodzielenie oktetow kropkami)"){
            const boost::dynamic_bitset<> check(32, 3232235521);
            const std::string expected = IPv4parser::octetsToString(check); //11000000 10101000 00000000 00000001
            REQUIRE(expected == "11000000.10101000.00000000.00000001");
        }
    }
}
