#pragma once
#ifndef IPSTRUCTS_H
#define IPSTRUCTS_H

#include <memory>

#include "IPv4address.h"
#include "IPv4mask.h"

namespace core {
    class NetworkBase
    {
    public:
        std::shared_ptr<IPaddressBase> Ip;
        std::shared_ptr<IPmaskBase> NetMask;

        bool isHost(const IPaddressBase& hostIP) const;
        virtual unsigned long long hostsCapacity() const;
        void fix();

        std::shared_ptr<NetworkBase> clone() const
        {
            return std::shared_ptr<NetworkBase>(_cloneImpl());
        }

        virtual ~NetworkBase() = default;
    protected:
        NetworkBase() = default;
        NetworkBase(const NetworkBase&) = default;
        NetworkBase& operator=(const NetworkBase&) = default;
        NetworkBase(NetworkBase&&) noexcept = default;
        NetworkBase& operator=(NetworkBase&&) noexcept = default;
    private:
        virtual NetworkBase* _cloneImpl() const = 0;
    };
//=============================================================================
    class Subnet: public NetworkBase
    {
    public:
        struct Host{
            //explicit Host(long long int number, QString name, std::shared_ptr<IPaddressBase> ip) : Number{number}, Name{name}, Ip{ip} {};
            long long int Number;
            QString Name = "noname";
            std::shared_ptr<IPaddressBase> Ip;
        };

        long long int HostNumber = -10;
        QString SubName = "blank";
        std::vector<Host> HostsList;

        virtual std::unique_ptr<IPaddressBase> getMinHost() = 0;
        virtual std::unique_ptr<IPaddressBase> getMaxHost() = 0;
        virtual std::unique_ptr<IPaddressBase> getBroadcast() = 0;

        std::shared_ptr<Subnet> clone() const
        {
            return std::shared_ptr<Subnet>(_cloneImpl());
        }
    protected:
        Subnet() = default;
        Subnet(const Subnet&) = default;
        Subnet& operator=(const Subnet&) = default;
        Subnet(Subnet&&) noexcept = default;
        Subnet& operator=(Subnet&&) noexcept = default;
    private:
        Subnet* _cloneImpl() const override = 0;
    };
//=============================================================================
    class Networkv4: public NetworkBase
    {
    public:
        Networkv4() { Ip = std::make_shared<IPv4address>(); NetMask = std::make_shared<IPv4mask>(); };
        unsigned long long hostsCapacity() const override;
    private:
        Networkv4* _cloneImpl() const override;
    };
//=============================================================================
    class Subnetv4: public Subnet
    {
    public:
        Subnetv4() { Ip = std::make_shared<IPv4address>(); NetMask = std::make_shared<IPv4mask>(); };
        unsigned long long hostsCapacity() const override;
        std::unique_ptr<IPaddressBase> getMinHost() override;
        std::unique_ptr<IPaddressBase> getMaxHost() override;
        std::unique_ptr<IPaddressBase> getBroadcast() override;
    private:
        Subnetv4* _cloneImpl() const override;
    };
};

#endif // IPSTRUCTS_H
