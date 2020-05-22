#include "IPv4mask.h"

#include <boost/dynamic_bitset.hpp>

namespace core {
    IPv4mask::IPv4mask(const boost::dynamic_bitset<>& maskAddress): IPaddressBase{maskAddress}, IPv4address{maskAddress}, IPmaskBase{maskAddress}
        {};
};
