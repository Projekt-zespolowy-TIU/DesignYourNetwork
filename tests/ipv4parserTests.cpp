#include <catch2/catch.hpp>

#include "ipv4add.h"
#include "ipv4parser.h"

using namespace core;

namespace ipv4parserTest {
    TEST_CASE("ipv4parser Tests"){
        SECTION("Parsowanie IP z postaci tekstowej decimal na postac binarna"){
            const boost::dynamic_bitset<> converted = ipv4parser::stringDecimal2octets("192.168.0.1");
            const boost::dynamic_bitset<> expected = boost::dynamic_bitset<>(32, 0b11000000101010000000000000000001);
            REQUIRE(converted == expected); //11000000 10101000 00000000 00000001
        }

        SECTION("Parsowanie postaci binarnej na string (rodzielenie oktetow kropkami)"){
            const boost::dynamic_bitset<> check(32, 3232235521);
            const std::string expected = ipv4parser::octetsToString(check); //11000000 10101000 00000000 00000001
            REQUIRE(expected == "11000000.10101000.00000000.00000001");
        }
    }
}
