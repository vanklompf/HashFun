#include <hash/CityHash.h>
#include <hash/MurmurHash1.h>
#include <hash/MurmurHash2.h>
#include <hash/MurmurHash3.h>
#include <hash/SuperFastHash.h>
#include <hash/xxHash.h>
#include <stddef.h>
#include <iostream>
#include <string>

#include "CommandlineParser.h"
#include "DataSet.h"
#include "HashBenchmark.h"
#include "HashFunctionEntry.h"


static const size_t MEGABYTE = 1024*1024;

int main(int argc, char** argv)
{
    CommandlineParser parser(argc, argv);
    const auto options = parser.Parse();


    std::cout << "Size was set to " << options.dataSize << std::endl;
    std::cout << "Min was set to " << options.minPacketSize << std::endl;
    std::cout << "Max was set to " << options.maxPacketSize << std::endl;

    HashFunctionsSet hashFunctionsSet =
    {
    { "XXH32", XXH32 },
    { "SuperFastHash", SuperFastHash },
    { "MurmurHash1", MurmurHash1 },
    { "MurmurHash1Aligned", MurmurHash1Aligned },
    { "MurmurHash2", MurmurHash2 },
    { "MurmurHash3_x86_32", MurmurHash3_x86_32 },
    { "CityHash32", CityHash32 } };

    DataSet dataSet(options.dataSize * MEGABYTE, options.minPacketSize, options.maxPacketSize);
    dataSet.PrepareData();

    HashBenchmark benchmark(hashFunctionsSet, dataSet);
    benchmark.Run();

    std::cout << "------------------------------------" << std::endl;
    for (const auto& r : hashFunctionsSet)
    {
        std::cout << r.name << ":\t " << r.result << std::endl;
    }
}
