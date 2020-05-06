#pragma once
#ifndef COREUTILS_H
#define COREUTILS_H

#include <stdexcept>
#include <string>

namespace core {
    class IIPaddress; //forward declaration

    class NotImplemented : public std::logic_error
    {
    public:
        NotImplemented(): NotImplemented("Not Implememented", __FUNCTION__) {};
        NotImplemented(const char* message): NotImplemented(message, __FUNCTION__) {};

        virtual const char *what() const throw();

    private:
        std::string _text;

        NotImplemented(const char* message, const char* function);
    };

    std::ostream& operator<< (std::ostream& out, const IIPaddress& c);
};

#endif // COREUTILS_H
