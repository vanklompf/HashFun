#include "DataSet.h"
#include "CompilerDefs.h"

#include <cstdint>
#include <algorithm>
#include <cstdlib>
#include <random>
#include <cstdlib>
#include <iostream>

const size_t PAGE_SIZE = 1024*1024*2;

DataSet::DataSet(size_t size) : m_size(size)
{
    m_buffer = (uint8_t*)(ALLIGNED_ALLOC(PAGE_SIZE, m_size));
    m_packetLenghts.reserve(m_size / 512);
}

void DataSet::PrepareData()
{
    std::mt19937 gen(42);
    std::generate(m_buffer, m_buffer + m_size, gen);

    std::uniform_int_distribution<uint32_t> packetSizeDistribution(64, 512);
    uint32_t packetSize = packetSizeDistribution(gen);
    uint64_t currentSize = 0;
    do
    {
        currentSize += packetSize;
        m_packetLenghts.push_back(packetSize);
        packetSize = packetSizeDistribution(gen);
    } while (currentSize + packetSize < m_size);
    m_packetLenghts.push_back((uint32_t)(m_size - currentSize));
}

DataSet::~DataSet()
{
    ALLIGNED_FREE(m_buffer);
}
