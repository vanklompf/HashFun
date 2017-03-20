/*
 * benchmark.h
 *
 *  Created on: Mar 5, 2017
 *      Author: fkorta
 */

#ifndef BENCHMARK_H_
#define BENCHMARK_H_
#include <cstddef>
#include <cstdint>
#include <vector>

struct Packets
{
    const uint8_t* buffer;
    std::vector<uint32_t> lenghts;
};

const Packets* prepareData(size_t size);

#endif /* BENCHMARK_H_ */
