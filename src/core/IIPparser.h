#pragma once
#ifndef IIPPARSER_H
#define IIPPARSER_H

#include <QString>

namespace core{
    template <class C>
    class IIPparser
    {
    public:
        virtual C ipFromString(const QString&) const = 0;
        virtual ~IIPparser() = default;

    protected:
        IIPparser& operator=(const IIPparser&) = default;
    };
}

#endif // IIPPARSER_H
