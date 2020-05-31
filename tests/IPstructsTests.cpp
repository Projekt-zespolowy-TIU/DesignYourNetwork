#include <catch2/catch.hpp>

#include "IPstructs.h"
#include "IPv4parser.h"

using namespace core;

namespace IPstructsTests {
    TEST_CASE("Network4 Tests"){
        Networkv4 network;
        network.Ip = IPv4parser{}.ipFromString("172.16.32.0");
        network.NetMask = IPv4parser{}.ipMaskFromString("255.255.248.0");

        Subnetv4 sub;
        sub.Ip = IPv4parser{}.ipFromString("192.168.1.0");
        sub.NetMask = IPv4parser{}.ipMaskFromString("255.255.255.252");

        SECTION("Host capacity test"){
            CHECK(network.hostsCapacity() == 2046);
        }
        SECTION("IP of network treat as non host"){
            CHECK(network.isHost(*IPv4parser{}.ipFromString("172.16.32.0")) == false);
        }
        SECTION("Check if IP is a host of network"){
            CHECK(network.isHost(*IPv4parser{}.ipFromString("172.16.32.1")) == true);
        }
        SECTION("Get Subnetv4 MinHost address"){
            CHECK(sub.getMinHost()->asStringDec().toStdString() == "192.168.1.1");
        }
        SECTION("Get Subnetv4 MaxHost address"){
            CHECK(sub.getMaxHost()->asStringDec().toStdString() == "192.168.1.2");
        }
        SECTION("Get Subnetv4 broadcast address"){
            CHECK(sub.getBroadcast()->asStringDec().toStdString() == "192.168.1.3");
        }
    }
}
