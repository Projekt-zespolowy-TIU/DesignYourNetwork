#pragma once
#ifndef IIPPARSER_H
#define IIPPARSER_H

#include <QString>
#include <memory>

namespace core{
    class IPaddressBase; //forward declaration
    class IPmaskBase; //forward declaration

    class IIPparser
    {
    public:
        virtual std::shared_ptr<IPaddressBase> ipFromString(const QString&) const = 0;
        virtual std::shared_ptr<IPmaskBase> ipMaskFromString(const QString&) const = 0;

        virtual ~IIPparser() = default;
    protected:
        IIPparser() = default;
        IIPparser(const IIPparser&) = default;
        IIPparser& operator=(const IIPparser&) = default;
        IIPparser(IIPparser&&) noexcept = default;
        IIPparser& operator=(IIPparser&&) noexcept = default;
    };
};

#endif // IIPPARSER_H
