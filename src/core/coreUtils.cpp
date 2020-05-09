#include "coreUtils.h"

#include "IIPaddress.h"

namespace core {
    const char* NotImplemented::what() const throw()
    {
        return _text.c_str();
    };

    NotImplemented::NotImplemented(const char *message, const char *function) : std::logic_error("Not Implemented")
    {
        _text = message;
        _text += " : ";
        _text += function;
    };

    std::ostream& operator<< (std::ostream& out, const IIPaddress& c)
    {
        out << c.asStringDec().toStdString() << std::flush;
        return out;
    };

    std::ostream& operator<<(std::ostream& out, const QString& c)
    {
        return out << c.toStdString();
    }

    std::istream& operator>>(std::istream& in, QString& c)
    {
        std::string temp;
        in >> temp;
        c = QString{temp.c_str()};
        return in;
    }

    const char* IPexception::what() const throw()
    {
        return _text.c_str();
    };
};
