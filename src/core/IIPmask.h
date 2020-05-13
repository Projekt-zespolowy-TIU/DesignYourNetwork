#pragma once
#ifndef IIPMASK_H
#define IIPMASK_H

namespace core {
    class IIPmask
    {
    public:
        virtual short getPrefix() const = 0;

    protected:
        IIPmask& operator=(const IIPmask&) = default;
        virtual ~IIPmask() = default;
    };
};

#endif // IIPMASK_H
