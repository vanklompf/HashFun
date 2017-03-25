#include "HashBenchmark.h"

#include <chrono>
#include <iostream>


HashBenchmark::HashBenchmark(HashFunctionsSet& functions, const DataSet& dataSet) : m_functions(functions), m_dataSet(dataSet)
{
}

uint32_t HashBenchmark::Measure(std::function<uint32_t()> f)
{
    auto antiOptimizer = 0;
    std::chrono::steady_clock::time_point start, end;
    start = std::chrono::steady_clock::now();

    antiOptimizer += f();

    end = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsed_seconds = end - start;

    std::cout << "Ignore this: " << antiOptimizer << std::endl;
    return (uint32_t) std::chrono::duration_cast<std::chrono::milliseconds>(elapsed_seconds).count();
}

void HashBenchmark::Run()
{
  for(auto& f : m_functions)
  {
      f.result = Measure(std::bind(&HashBenchmark::RunForDataSet, this, f.func));
  }
}


uint32_t HashBenchmark::RunForDataSet(HashFunc func)
{
  uint32_t antiOptimizer = 0;
  const uint8_t* pos = m_dataSet.m_buffer;

  for(auto packetSize : m_dataSet.m_packetLenghts)
  {
      antiOptimizer += func(pos, packetSize);
      pos+=packetSize;
  }

  return antiOptimizer;
}


