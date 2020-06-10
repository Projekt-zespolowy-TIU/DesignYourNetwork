#include <nlohmann/json.hpp>
#include <string>
#include <fstream>
#include <iostream>

#include "FileIO.h"
#include "IPv4parser.h"
#include "IPv6parser.h"

namespace core{

using json = nlohmann::json;

    void FileIO::saveIPv4(Networkv4 netv4, QString path)
    {
        std::ofstream o(path.toStdString());

        info["IPv4IP"] = netv4.Ip().asStringDec().toStdString();
        info["IPv4NetMask"] = netv4.Mask().asStringDec().toStdString();

        info["IPv4SubnetNames"].clear();
        info["IPv4SubnetHostNumbers"].clear();

        for (auto i : netv4.Subnets())
        {
            info["IPv4SubnetNames"].push_back(i->SubName().toStdString());
            info["IPv4SubnetHostNumbers"].push_back(int(i->HostNumber()));
        }

        o<<info;
    }

    void FileIO::loadIPv4(Networkv4& netv4, QString path)
    {
        info.clear();
        std::ifstream i(path.toStdString());
        i>>info;


        Networkv4 temp_network{
            QString{std::string(info["IPv4IP"]).c_str()},
            QString{std::string(info["IPv4NetMask"]).c_str()}
            };

        netv4 = temp_network;

        for (int i=0; i<int(info["IPv4SubnetNames"].size()) ; i++)
        {
            netv4.addSubnet(static_cast<int>(info["IPv4SubnetHostNumbers"][i]), std::string(info["IPv4SubnetNames"][i]).c_str());
        }
    }

    void FileIO::saveIPv6(Networkv6 netv6, QString path)
    {
        std::ofstream o(path.toStdString());

        info["IPv6IP"] = netv6.Ip().asStringDec().toStdString();
        info["IPv6NetMask"] = netv6.Mask().asStringDec().toStdString();

        info["IPv6SubnetNames"].clear();
        info["IPv6SubnetHostNumbers"].clear();
        for (auto i : netv6.Subnets())
        {
            info["IPv6SubnetNames"].push_back(i->SubName().toStdString());
            info["IPv6SubnetHostNumbers"].push_back(int(i->HostNumber()));
        }

        o<<info;
    }


    void FileIO::loadIPv6(Networkv6 &netv6, QString path)
    {
        info.clear();
        std::ifstream i(path.toStdString());
        i>>info;

        Networkv6 temp_network{
            QString{std::string(info["IPv6IP"]).c_str()},
            QString{std::string(info["IPv6NetMask"]).c_str()}
            };

        netv6 = temp_network;

        for (int i=0; i<int(info["IPv6SubnetNames"].size()) ; i++)
        {
            netv6.addSubnet(static_cast<int>(info["IPv6SubnetHostNumbers"][i]), std::string(info["IPv6SubnetNames"][i]).c_str());
        }
    }
}
