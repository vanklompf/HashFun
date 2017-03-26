#ifndef HASHBENCHMARK_H_
#define HASHBENCHMARK_H_

#include <cstdint>
#include <functional>
#include <vector>

#include "DataSet.h"
#include "HashFunctionEntry.h"

class DataSet;
class HashBenchmark
{
public:
    HashBenchmark(HashFunctionsSet& functions, const DataSet& dataSet);
    void Run();

private:
    HashFunctionsSet& m_functions;
    const DataSet& m_dataSet;

    uint32_t Measure(std::function<void()> x);
    void RunForDataSet(HashFunc func);
};

#endif /* HASHBENCHMARK_H_ */
