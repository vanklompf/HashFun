#include "CvsPrinter.h"

#include <cmath>
#include <cstdint>
#include <iostream>
#include <numeric>
#include <vector>

#include "CommandlineParser.h"

static const char CVS_SEPARATOR = ',';

CvsPrinter::CvsPrinter(std::ostream& dst) : m_dst(dst)
{
}

void CvsPrinter::PrintConfig(const CommandlineOptions& config) const
{
    m_dst << config.dataSize << CVS_SEPARATOR;
    m_dst << config.numOfRuns << CVS_SEPARATOR;
    m_dst << config.minPacketSize << CVS_SEPARATOR;
    m_dst << config.maxPacketSize << CVS_SEPARATOR;
}

void CvsPrinter::PrintResults(const HashFunctionsSet& results) const
{
    for (const auto& hashFunction : results)
    {
        auto average = CalculateAverage(hashFunction);
        m_dst << average << CVS_SEPARATOR;
        m_dst << CalculateStdDev(hashFunction, average) << CVS_SEPARATOR;
    }
}

uint32_t CvsPrinter::CalculateAverage(const HashFunctionEntry& results)
{
    return std::accumulate(results.results.begin(), results.results.end(), 0) / results.results.size();
}

uint32_t CvsPrinter::CalculateStdDev(const HashFunctionEntry& results, uint32_t average)
{
    auto& r = results.results;
    auto sq_sum = std::inner_product(r.begin(), r.end(), r.begin(), 0);
    return std::sqrt(sq_sum / r.size() - average * average);
}

