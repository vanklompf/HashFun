#ifndef IPRINTER_H_
#define IPRINTER_H_

#include "HashFunctionEntry.h"

struct CommandlineOptions;

class IPrinter
{
public:
    void PrintConfig(const CommandlineOptions& config) const;
    void PrintResults(const HashFunctionsSet& results) const;
};

#endif /* IPRINTER_H_ */
