#include "CvsPrinter.h"

#include <algorithm>
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
        auto trimmedResults = hashFunction.results;
        if (trimmedResults.size() >= 5)
        {
          std::sort(trimmedResults.begin(), trimmedResults.end());
          trimmedResults.erase(trimmedResults.begin());
          trimmedResults.pop_back();
        }
        auto average = CalculateAverage(trimmedResults);
        m_dst << average << CVS_SEPARATOR;
        m_dst << CalculateStdDev(trimmedResults, average) << CVS_SEPARATOR;
    }
    m_dst << std::endl;
}

uint32_t CvsPrinter::CalculateAverage(const std::vector<uint32_t>& results)
{
    return std::accumulate(results.begin(), results.end(), 0) / (uint32_t)results.size();
}

uint32_t CvsPrinter::CalculateStdDev(const std::vector<uint32_t>& results, uint32_t average)
{
    auto sq_sum = std::inner_product(results.begin(), results.end(), results.begin(), 0);
    return static_cast<uint32_t>(sqrt(sq_sum / results.size() - average * average));
}

