#include "IPv4mask.h"

#include <boost/dynamic_bitset.hpp>

#include "IPmaskBase.h"

namespace core {
    IPv4mask::IPv4mask(const boost::dynamic_bitset<>& maskAddress): IPmaskBase{maskAddress}
    {}
}
