#pragma once
#ifndef REPORTGENERATORV6_H
#define REPORTGENERATORV6_H

#include "IReportGenerator.h"

namespace core {
    class ReportGeneratorV6 final: public IReportGenerator
    {
    public:
        void generate(const INetwork &network, DetaiLevel level = DetaiLevel::NoDetails) noexcept override;
        QString getReport() const noexcept override;
        void save(const QString &path) const override;
    private:
        QString _Report;
    };
}

#endif // REPORTGENERATORV6_H
