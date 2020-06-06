#include "IPprotocolAlgorithm.h"

#include "IPaddress.h"
#include "ISubnet.h"
#include "coreUtils.h"

namespace core {
    boost::dynamic_bitset<> IPprotocolAlgorithm::chooseMask(const cpp_int& desiredHostsNumber,
                                                                   const unsigned short maskLength) const
    {
        unsigned short numberOfHostBits = 1;
        cpp_int countHosts = 0;

        while( !((countHosts -2) >= desiredHostsNumber) )
        {
            countHosts = (cpp_int{1} << numberOfHostBits);
            numberOfHostBits++;
        };

        cpp_int limitIPversionAddress = (cpp_int{2} << maskLength);
        limitIPversionAddress -= 1;

        auto bitsetString = toBinary(limitIPversionAddress - (countHosts - 1));

        auto bitsetIP = boost::dynamic_bitset<>(bitsetString);
        bitsetIP.resize(maskLength, false);

        return bitsetIP;
    };

    boost::dynamic_bitset<> IPprotocolAlgorithm::chooseIP(const IPaddress& mainNetIP,
                                                                 const IPaddress& Mask,
                                                                 const std::vector<std::shared_ptr<ISubnet>>& usedIPsPool) const
    {
        auto pretenderAddress = mainNetIP.raw();
        auto len = pretenderAddress.size();

        cpp_int netBits{1};

        while(std::any_of(usedIPsPool.begin(), usedIPsPool.end(), [&](const auto& subnet) {
                          return subnet->isHost(pretenderAddress) ||
                          subnet->Ip().raw() == pretenderAddress; }))
        {
            auto binary = toBinary(cpp_int{netBits << (len - Mask.getPrefix())});
            auto create = boost::dynamic_bitset<>(binary);
            create.resize(len, false);

            pretenderAddress = (mainNetIP | create);
            netBits++;
        };
        return pretenderAddress;
    }
}
