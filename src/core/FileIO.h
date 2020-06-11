#ifndef FILEIO_H
#define FILEIO_H

#include <memory>
#include <QString>
#include <nlohmann/json.hpp>

#include "INetwork.h"


using json = nlohmann::json;

namespace core {
    class FileIO
    {
    public:
        void saveIPv4(const INetwork& netv4, const QString& path);
        void loadIPv4(std::shared_ptr<INetwork>& netv4, const QString& path);
        void saveIPv6(const INetwork& netv6, const QString& path);
        void loadIPv6(std::shared_ptr<INetwork>& netv6, const QString& path);

    private:
        json info;
    };
};



#endif // FILEIO_H
