#pragma once
#ifndef IIPMASK_H
#define IIPMASK_H

namespace core {
    class IIPmask
    {
    public:
        virtual short getPrefix() const = 0;

        virtual ~IIPmask() = default;
    protected:
        IIPmask() = default;
        IIPmask(const IIPmask&) = default;
        IIPmask& operator=(const IIPmask&) = default;
        IIPmask(IIPmask&&) noexcept = default;
        IIPmask& operator=(IIPmask&&) noexcept = default;
    };
};

#endif // IIPMASK_H
