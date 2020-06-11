#pragma once
#ifndef IREPORTGENERATOR_H
#define IREPORTGENERATOR_H

#include <QString>

#include "INetwork.h"

namespace core {
    enum class DetaiLevel{
        NoDetails,
        Detailed,
        SuperDetailed
    };

    class IReportGenerator
    {
    public:
        virtual void generate(const INetwork& network, DetaiLevel level = DetaiLevel::NoDetails) noexcept = 0;
        virtual QString getReport() const noexcept = 0;
        virtual void save(const QString& path) const = 0;

        //~~~~~~~~~~~~~~~~INTERFACE OVERHEAD~~~~~~~~~~~~~~~~//
    public:
        virtual ~IReportGenerator() = default;
    protected:
        IReportGenerator() = default;
        IReportGenerator(const IReportGenerator&) = default;
        IReportGenerator& operator=(const IReportGenerator&) = default;
        IReportGenerator(IReportGenerator&&) noexcept = default;
        IReportGenerator& operator=(IReportGenerator&&) noexcept = default;
    };
    //~~~~~~~~~~~~~~~~INTERFACE OVERHEAD~~~~~~~~~~~~~~~~//
}

#endif // IREPORTGENERATOR_H
