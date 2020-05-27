#pragma once
#ifndef IIPPARSER_H
#define IIPPARSER_H

#include <QString>
#include <boost/dynamic_bitset.hpp>

namespace core{
    class IIPparser
    {
    public:
        virtual boost::dynamic_bitset<> ipFromString(const QString&) const = 0;

    //~~~~~~~~~~~~~~~~INTERFACE OVERHEAD~~~~~~~~~~~~~~~~//
    public:
        virtual ~IIPparser() = default;
    protected:
        IIPparser() = default;
        IIPparser(const IIPparser&) = default;
        IIPparser& operator=(const IIPparser&) = default;
        IIPparser(IIPparser&&) noexcept = default;
        IIPparser& operator=(IIPparser&&) noexcept = default;
    //~~~~~~~~~~~~~~~~INTERFACE OVERHEAD~~~~~~~~~~~~~~~~//
    };
};

#endif // IIPPARSER_H
