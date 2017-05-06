#include "HashBenchmark.h"

#include <chrono>
#include <iostream>


HashBenchmark::HashBenchmark(HashFunctionsSet& functions, const DataSet& dataSet) : m_functions(functions), m_dataSet(dataSet)
{
}

uint32_t HashBenchmark::Measure(std::function<void()> f)
{
    std::chrono::steady_clock::time_point start, end;
    start = std::chrono::steady_clock::now();

    f();

    end = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsed_seconds = end - start;

    return (uint32_t) std::chrono::duration_cast<std::chrono::milliseconds>(elapsed_seconds).count();
}

void HashBenchmark::Run()
{
  for(auto& f : m_functions)
  {
      f.result = Measure(std::bind(&HashBenchmark::RunForDataSet, this, f.func));
  }
}


void HashBenchmark::RunForDataSet(HashFunc func)
{
  const uint8_t* pos = m_dataSet.m_buffer;

  for(auto packetSize : m_dataSet.m_packetLenghts)
  {
      func(pos, packetSize);
      pos+=packetSize;
  }
}
