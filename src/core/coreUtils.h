#pragma once
#ifndef COREUTILS_H
#define COREUTILS_H

#include <stdexcept>
#include <string>
#include <iostream>
#include <QString>

namespace core {
    class IIPaddress; //forward declaration

    class NotImplemented : public std::logic_error
    {
    public:
        NotImplemented(): NotImplemented("Not Implememented", __FUNCTION__) {};
        NotImplemented(const char* message): NotImplemented(message, __FUNCTION__) {};

        virtual const char* what() const throw();
    private:
        std::string _text;

        NotImplemented(const char* message, const char* function);
    };

    class IPexception : public std::exception
    {
    public:
        IPexception(const char* message): _text{message} {};

        virtual const char* what() const throw();
    private:
        std::string _text;
    };

    class IPinvalidFormat : public IPexception
    {
    public:
        IPinvalidFormat(const char* message) : IPexception{message} {};
    };

    std::ostream& operator<< (std::ostream& out, const IIPaddress& c);
    std::ostream& operator<< (std::ostream& out, const QString& c);
    std::istream& operator>> (std::istream& in, QString& c);
};

#endif // COREUTILS_H
