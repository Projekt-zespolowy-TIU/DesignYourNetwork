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

        virtual const char* what() const noexcept;
    private:
        std::string _text;

        NotImplemented(const char* message, const char* function);
    };

    class IPException : public std::exception
    {
    public:
        IPException(const char* message): _text{message} {};

        const char * what() const noexcept override;
    private:
        std::string _text;
    };

    class IPFormatExcept : public IPException
    {
    public:
        IPFormatExcept(const char* message) : IPException{message} {};
    };

    class IPNetworkExcept : public IPException
    {
    public:
        IPNetworkExcept(const char* message) : IPException{message} {};
    };

    class IPSubnetworkExcept : public IPException
    {
    public:
        IPSubnetworkExcept(const char* message) : IPException{message} {};
    };

    std::ostream& operator<< (std::ostream& out, const IIPaddress& c);
    std::ostream& operator<< (std::ostream& out, const QString& c);
    std::istream& operator>> (std::istream& in, QString& c);
};

#endif // COREUTILS_H
