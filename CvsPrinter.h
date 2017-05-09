#ifndef CVS_PRINTER_H_
#define CVS_PRINTER_H_

#include "IPrinter.h"
#include "HashFunctionEntry.h"

struct CommandlineOptions;

class CvsPrinter : IPrinter
{
public:
    CvsPrinter(std::ostream& dst);
    void PrintConfig(const CommandlineOptions& config) const;
    void PrintResults(const HashFunctionsSet& results) const;
private:
    static uint32_t CalculateAverage(const HashFunctionEntry& results);
    static uint32_t CalculateStdDev(const HashFunctionEntry& results, uint32_t average);
    std::ostream& m_dst;
};

#endif /* CVS_PRINTER_H_ */
