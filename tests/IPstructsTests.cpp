#include <catch2/catch.hpp>

#include "IPstructs.h"
#include "IPv4parser.h"

using namespace core;

namespace IPstructsTests {
    TEST_CASE("Network4 Tests"){
        Networkv4 network;
        network.Ip = IPv4parser{}.ipFromString("172.16.32.0");
        network.NetMask = IPv4parser{}.ipMaskFromString("255.255.248.0");

        SECTION("Host capacity test"){
            CHECK(network.hostsCapacity() == 2046);
        }
        SECTION("Check if IP is a host of network"){
            CHECK(network.isHost(*IPv4parser{}.ipFromString("172.16.32.1")) == true);
        }
    }
}
