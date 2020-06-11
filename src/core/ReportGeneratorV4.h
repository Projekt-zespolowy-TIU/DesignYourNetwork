#pragma once
#ifndef REPORTGENERATORV4_H
#define REPORTGENERATORV4_H

#include "IReportGenerator.h"

namespace core {
    class ReportGeneratorV4 final: public IReportGenerator
    {
    public:
        void generate(const INetwork &network, DetaiLevel level = DetaiLevel::NoDetails) noexcept override;
        QString getReport() const noexcept override;
        void save(const QString &path) const override;
    private:
        QString _Report;
    };
}

#endif // REPORTGENERATORV4_H
