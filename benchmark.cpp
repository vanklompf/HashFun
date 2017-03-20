/*
 * benchmark.cpp
 *
 *  Created on: Mar 5, 2017
 *      Author: fkorta
 */
#include "benchmark.h"

#include <cstdlib>
#include <cstdint>
#include <algorithm>
#include <vector>
#include <random>

static const uint32_t PAGE_SIZE = 2 * 1024 * 1024;

const Packets* prepareData(size_t size)
{
    auto packets = new Packets();
    auto buffer = (uint8_t*) aligned_alloc(PAGE_SIZE, size);
    packets->lenghts.reserve(size / 512);

    std::generate(buffer, buffer + size, ::rand);

    uint64_t currentSize = 0;
    std::mt19937 gen(42);
    std::uniform_int_distribution<uint32_t> dis(64, 512);

    uint64_t packetSize = dis(gen);
    do
    {
        currentSize += packetSize;
        packets->lenghts.push_back(size - currentSize);
        packetSize = dis(gen);
    } while (currentSize + packetSize < size);
    packets->lenghts.push_back(size - currentSize);

    packets->buffer = buffer;
    return packets;
}


