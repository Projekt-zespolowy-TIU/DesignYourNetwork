#pragma once
#ifndef IIPADDRESS_H
#define IIPADDRESS_H

#include <string>
#include <iostream>

namespace core{
    class IIPaddress
    {
    public:
        virtual std::string asStringDec() const = 0;

        friend std::ostream& operator<< (std::ostream& out, const IIPaddress& c)
        {
            out << c.asStringDec() << std::endl;
            return out;
        };

    protected:
        IIPaddress& operator=(const IIPaddress&) = default;
        virtual ~IIPaddress() = default;
    };
};
#endif // IIPADDRESS_H
