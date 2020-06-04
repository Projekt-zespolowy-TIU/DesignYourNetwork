#pragma once
#ifndef COREUTILS_H
#define COREUTILS_H

#include <stdexcept>
#include <string>
#include <iostream>
#include <QString>
#include <boost/multiprecision/cpp_int.hpp>

namespace core {
    using boost::multiprecision::cpp_int;

    class IIPaddrPrintable; //forward declaration

    std::string toBinary(cpp_int n);

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

    class CoreException : public std::exception
    {
    public:
        CoreException(const char* message): _text{message} {};

        const char* what() const noexcept override;
    private:
        std::string _text;
    };

    class IPFormatExcept : public CoreException
    {
    public:
        IPFormatExcept(const char* message) : CoreException{message} {};
    };

    class NetworkExcept : public CoreException
    {
    public:
        NetworkExcept(const char* message) : CoreException{message} {};
    };

    class NetworkFullExcept : public NetworkExcept
    {
    public:
        NetworkFullExcept(const char* message) : NetworkExcept{message} {};
    };

    class SubnetExcept : public CoreException
    {
    public:
        SubnetExcept(const char* message) : CoreException{message} {};
    };

    class SubnetInvalidExcept : public SubnetExcept
    {
    public:
        SubnetInvalidExcept(const char* message) : SubnetExcept{message} {};
    };

    std::ostream& operator<< (std::ostream& out, const IIPaddrPrintable& c);
    std::ostream& operator<< (std::ostream& out, const QString& c);
    std::istream& operator>> (std::istream& in, QString& c);
};

#endif // COREUTILS_H
