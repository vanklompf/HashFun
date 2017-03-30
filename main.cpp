#include <boost/program_options.hpp>
#include <hash/CityHash.h>
#include <hash/MurmurHash1.h>
#include <hash/MurmurHash2.h>
#include <hash/MurmurHash3.h>
#include <hash/SuperFastHash.h>
#include <hash/xxHash.h>
#include <stddef.h>
#include <iostream>
#include <string>

#include "DataSet.h"
#include "HashBenchmark.h"
#include "HashFunctionEntry.h"

namespace po = boost::program_options;
static const size_t MEGABYTE = 1024*1024;

int main()
{
    po::options_description desc("Allowed options");
    desc.add_options()
        ("help", "produce help message")
        ("compression", po::value<double>(), "set compression level");


    HashFunctionsSet hashFunctionsSet =
    {
    { "XXH32", XXH32 },
    { "SuperFastHash", SuperFastHash },
    { "MurmurHash1", MurmurHash1 },
    { "MurmurHash1Aligned", MurmurHash1Aligned },
    { "MurmurHash2", MurmurHash2 },
    { "MurmurHash3_x86_32", MurmurHash3_x86_32 },
    { "CityHash32", CityHash32 } };

    const auto size = 1000;
    std::cout << "Data size: " << size << " Mb" << std::endl;
    DataSet dataSet(size * MEGABYTE);
    dataSet.PrepareData();

    HashBenchmark benchmark(hashFunctionsSet, dataSet);
    benchmark.Run();

    std::cout << "------------------------------------" << std::endl;
    for (const auto& r : hashFunctionsSet)
    {
        std::cout << r.name << ":\t " << r.result << std::endl;
    }
}
