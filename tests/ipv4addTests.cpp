#include <catch2/catch.hpp>
#include "ipv4add.h"
#include "ipv4parser.h"


using namespace core;

namespace ipv4addressTest {
    TEST_CASE("Parsowanie IP z postaci decimal na postac binarna"){
        const auto converted = ipv4parser::stringDecimal2octets("192.168.0.1");
        REQUIRE(converted == 0b11000000101010000000000000000001); //11000000 10101000 00000000 00000001
    }

    TEST_CASE("Parsowanie postaci binarnej na string (rodzielenie kropkami"){
        const auto expected = ipv4parser::octetsToString(3232235521); //11000000 10101000 00000000 00000001
        REQUIRE(expected == "11000000.10101000.00000000.00000001");
    }
}
