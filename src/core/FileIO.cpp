#include "FileIO.h"

#include <string>
#include <fstream>
#include <nlohmann/json.hpp>

#include "Networkv4.h"
#include "Networkv6.h"

namespace core{

using json = nlohmann::json;

    void FileIO::saveIPv4(const INetwork& netv4, const QString& path)
    {
        std::ofstream o(path.toStdString());

        info["IPv4IP"] = netv4.Ip().asStringDec().toStdString();
        info["IPv4NetMask"] = netv4.Mask().asStringDec().toStdString();

        info["IPv4SubnetNames"].clear();
        info["IPv4SubnetHostNumbers"].clear();

        for(const auto& i : netv4.Subnets())
        {
            info["IPv4SubnetNames"].push_back(i->SubName().toStdString());
            info["IPv4SubnetHostNumbers"].push_back(i->HostNumber().str());
        }

        o<<info;
    }

    void FileIO::loadIPv4(std::shared_ptr<INetwork>& netv4, const QString& path)
    {
        info.clear();
        std::ifstream i(path.toStdString());
        i>>info;

        std::shared_ptr<INetwork> temp_network = std::make_shared<Networkv4>(
            QString{std::string(info["IPv4IP"]).c_str()},
            QString{std::string(info["IPv4NetMask"]).c_str()});

        for(int i=0; i<int(info["IPv4SubnetNames"].size()) ; i++)
        {
            temp_network->addSubnet(cpp_int{std::string{info["IPv4SubnetHostNumbers"][i]}},
                                   std::string(info["IPv4SubnetNames"][i]).c_str());
        }

        netv4 = temp_network;
    }

    void FileIO::saveIPv6(const INetwork& netv6, const QString& path)
    {
        std::ofstream o(path.toStdString());

        info["IPv6IP"] = netv6.Ip().asStringDec().toStdString();
        info["IPv6NetMask"] = netv6.Mask().asStringDec().toStdString();

        info["IPv6SubnetNames"].clear();
        info["IPv6SubnetHostNumbers"].clear();

        for(const auto& i : netv6.Subnets())
        {
            info["IPv6SubnetNames"].push_back(i->SubName().toStdString());
            info["IPv6SubnetHostNumbers"].push_back(i->HostNumber().str());
        }

        o<<info;
    }


    void FileIO::loadIPv6(std::shared_ptr<INetwork>& netv6, const QString& path)
    {
        info.clear();
        std::ifstream i(path.toStdString());
        i>>info;

        std::shared_ptr<INetwork> temp_network = std::make_shared<Networkv6>(
            QString{std::string(info["IPv6IP"]).c_str()},
            QString{std::string(info["IPv6NetMask"]).c_str()});

        for(int i = 0; i < static_cast<int>((info["IPv6SubnetNames"].size())); i++)
        {
            temp_network->addSubnet(cpp_int{std::string{info["IPv6SubnetHostNumbers"][i]}},
                    std::string(info["IPv6SubnetNames"][i]).c_str());
        }

        netv6 = temp_network;
    }
}
