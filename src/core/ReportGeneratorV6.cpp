#include "ReportGeneratorV6.h"

#include <fstream>

#include "Subnetv6.h"
#include "coreUtils.h"

namespace core {
    void ReportGeneratorV6::generate(const INetwork& network, DetaiLevel level)
    {
////////////////////////////////////////////////////////////NETWORK///////////
        _Report += QString{"Network - IP protocol v6:\n"}
                + "\tIP: " + network.Ip().asStringDec()
                + " Mask: " + network.Mask().asStringDec() + '\n';

        if(level == DetaiLevel::SuperDetailed)
        {
            _Report += QString{"\tIP(binary): "} + network.Ip().asStringBin()
                    + " Mask(binary): " + network.Mask().asStringBin() + '\n';
        }
////////////////////////////////////////////////////////////~NETWORK//////////

////////////////////////////////////////////////////////SUBNETWORKS///////////
        for(const auto& sub : network.Subnets())
        {
            _Report += QString{"Subnet's name: "} + sub->SubName() + '\n'
                      + "\tIP: " + sub->Ip().asStringDec()
                      + " Mask: " + sub->Mask().asStringDec() + '\n';

            if(level == DetaiLevel::SuperDetailed)
            {
                _Report += "\tIP(binary): " + sub->Ip().asStringBin()
                          + " Mask(binary): " + sub->Mask().asStringBin() + '\n';
            }

            _Report += "\tminHost: " + sub->getMinHost()->asStringDec()
                    + " maxHost: " + sub->getMaxHost()->asStringDec() + '\n';

            if(level == DetaiLevel::SuperDetailed)
            {
                _Report += "\tminHost(binary): " + sub->getMinHost()->asStringBin()
                        + " maxHost(binary): " + sub->getMaxHost()->asStringBin() + '\n';
            }

            _Report += QString{"\tHost capacity: "} + sub->HostNumber().str().c_str() + '\n';
////////////////////////////////////////////////////////~SUBNETWORKS//////////

///////////////////////////////////////////////////////////////HOSTS//////////
            if(level >= DetaiLevel::Detailed)
            {
                for(const auto& host : sub->HostsList())
                {
                    _Report += "\t\t" + host->Name();
                    _Report += " " + host->Ip().asStringDec() + '\n';

                    if(level == DetaiLevel::SuperDetailed)
                    {
                         _Report += "\t\t\t" + host->Ip().asStringBin() + '\n';
                    }
                }
            }
///////////////////////////////////////////////////////////////~HOSTS/////////
        }
    }

    QString ReportGeneratorV6::getReport() const
    {
        return _Report;
    }

    void ReportGeneratorV6::save(const QString& path) const
    {
        auto file = std::ofstream{path.toStdString(), std::ios::out | std::ios::trunc}; //TODO: error handling
        file << _Report;
    }
}
