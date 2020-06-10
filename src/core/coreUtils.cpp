#include "coreUtils.h"

#include "IIPaddrPrintable.h"

namespace core {
    std::string toBinary(cpp_int n) noexcept
    {
        std::string r;
        while(n != 0)
        {
            r = ( n % 2 == 0 ? "0" : "1" ) + r;
            n /= 2;
        }
        return r;
    }

    const char* NotImplemented::what() const noexcept
    {
        return _text.c_str();
    };

    NotImplemented::NotImplemented(const char *message, const char *function):
        std::logic_error("Not Implemented")
    {
        _text = message;
        _text += " : ";
        _text += function;
    };

    std::ostream& operator<< (std::ostream& out, const IIPaddrPrintable& c) noexcept
    {
        out << c.asStringDec().toStdString() << std::flush;
        return out;
    };

    const char *CoreException::what() const noexcept
    {
        return _text.c_str();
    }

    std::ostream& operator<<(std::ostream& out, const QString& c) noexcept
    {
        return out << c.toStdString();
    }

    std::istream& operator>>(std::istream& in, QString& c) noexcept
    {
        std::string temp;
        in >> temp;
        c = QString{temp.c_str()};
        return in;
    }
};
