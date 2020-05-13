#include "IPaddressBase.h"

#include <memory>
#include <istream>
#include <string>

#include "coreUtils.h"
#include "IPv4address.h"
#include "IPv4parser.h"
#include "IPmaskBase.h"


namespace core {
    std::shared_ptr<IPaddressBase> operator&(const std::shared_ptr<IPaddressBase>& ip, const std::shared_ptr<IPmaskBase>& mask)
    {
        return ip->_applyMask(mask->_IpAddress);
    };

    std::istream& operator>>(std::istream& in, std::shared_ptr<IPaddressBase>& b)
    {
        std::string tempS;
        in >> tempS;

        if(dynamic_cast<IPv4address*>(&*b))
        {
            b = IPv4parser{}.ipFromString(tempS.c_str());
        }
        //else if(dynamic_cast<IPv6address*>(&b))
        else throw NotImplemented{}; //TODO: error handling

        return  in;
    };

    bool IPaddressBase::operator==(const IPaddressBase& x) const
    {
        return this->_IpAddress == x._IpAddress;
    };

    bool IPaddressBase::operator!=(const IPaddressBase& x) const
    {
        return this->_IpAddress != x._IpAddress;
    };
};
