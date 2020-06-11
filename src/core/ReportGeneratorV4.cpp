#include "ReportGeneratorV4.h"

#include <fstream>

#include "Subnetv4.h"
#include "coreUtils.h"

namespace core {
    void ReportGeneratorV4::generate(const INetwork& network, DetaiLevel level) noexcept
    {
////////////////////////////////////////////////////////////NETWORK///////////
        _Report = QString{"Network - IP protocol v4:\n"}
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

            _Report += "\tBroadcast: " + dynamic_cast<Subnetv4&>(*sub).getBroadcast()->asStringDec()
                    + " minHost: " + sub->getMinHost()->asStringDec()
                    + " maxHost: " + sub->getMaxHost()->asStringDec() + '\n';

            if(level == DetaiLevel::SuperDetailed)
            {
                _Report += "\tBroadcast(binary): " + dynamic_cast<Subnetv4&>(*sub).getBroadcast()->asStringBin()
                        + " minHost(binary): " + sub->getMinHost()->asStringBin()
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

    QString ReportGeneratorV4::getReport() const noexcept
    {
        return _Report;
    }

    void ReportGeneratorV4::save(const QString& path) const
    {
        auto file = std::ofstream{path.toStdString(), std::ios::out | std::ios::trunc}; //TODO: error handling
        file << _Report;
    }
}
