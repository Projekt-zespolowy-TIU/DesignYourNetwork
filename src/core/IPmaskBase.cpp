#include "IPmaskBase.h"

namespace core{
    short IPmaskBase::getPrefix() const
    {
        return _IpAddress.count();
    }
}
