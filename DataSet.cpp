#include "DataSet.h"

#include <cstdint>
#include <algorithm>
#include <cstdlib>
#include <random>
#include <cstdlib>

const size_t PAGE_SIZE = 1024*1024*2;

DataSet::DataSet(size_t size) : m_size(size)
{
    m_buffer = (uint8_t*)(aligned_alloc(PAGE_SIZE, m_size));
    m_packetLenghts.reserve(m_size / 512);
}

void DataSet::PrepareData()
{
    std::generate(m_buffer, m_buffer + m_size, ::rand);

    uint64_t currentSize = 0;
    std::mt19937 gen(42);
    std::uniform_int_distribution<uint32_t> dis(64, 512);

    uint64_t packetSize = dis(gen);
    do
    {
        currentSize += packetSize;
        m_packetLenghts.push_back(packetSize);
        packetSize = dis(gen);
    } while (currentSize + packetSize < m_size);
    m_packetLenghts.push_back(m_size - currentSize);
}

DataSet::~DataSet()
{
    free(m_buffer);
}
