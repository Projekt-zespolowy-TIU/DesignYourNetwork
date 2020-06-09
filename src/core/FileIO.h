#ifndef FILEIO_H
#define FILEIO_H

#include <memory>
#include <nlohmann/json.hpp>
#include "Networkv4.h"
#include "Networkv6.h"
#include "Subnetv4.h"
#include "Subnetv6.h"
#include "IPv4parser.h"
#include "IPv6parser.h"


using json = nlohmann::json;

namespace core {
    class FileIO
    {
    public:
        void saveIPv4(Networkv4 netv4, QString path);
        void loadIPv4(Networkv4& netv4, QString path);
        void saveIPv6(Networkv6 netv6, QString path);
        void loadIPv6(Networkv6& netv6, QString path);

    private:
        json info;
    };
};



#endif // FILEIO_H
