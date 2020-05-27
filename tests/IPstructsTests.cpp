#include <catch2/catch.hpp>

#include "core/Networkv4.h"

using namespace core;

namespace IPstructsTests {
    TEST_CASE("Network4 Tests"){
        Networkv4 network(QString{"172.16.32.0"}, QString{"255.255.248.0"});

//        SECTION("Host capacity test"){
//            CHECK(network.hostsCapacity() == 2046);
//        }
        SECTION("IP of network can be a subnetwork"){
            CHECK(network.isSubnet(IPv4address{"172.16.32.0"}) == true);
        }
        SECTION("Check if IP is a subnetwork"){
            CHECK(network.isSubnet(IPv4address{"172.16.32.1"}) == true);
        }
    }

    TEST_CASE("Subnetv4 Tests"){
        Subnetv4 sub(10, "Test");
        sub.Ip(std::make_unique<IPv4address>("192.168.1.0"));
        sub.Mask(std::make_unique<IPv4mask>("255.255.255.252"));

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
