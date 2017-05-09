#include <hash/CityHash.h>
#include <hash/MurmurHash1.h>
#include <hash/MurmurHash2.h>
#include <hash/MurmurHash3.h>
#include <hash/SuperFastHash.h>
#include <hash/xxHash.h>
#include <stddef.h>
#include <algorithm>
#include <cstdint>
#include <iostream>
#include <string>
#include <vector>

#include "CommandlineParser.h"
#include "CvsPrinter.h"
#include "DataSet.h"
#include "HashBenchmark.h"
#include "HashFunctionEntry.h"


static const size_t MEGABYTE = 1024*1024;

int main(int argc, char** argv)
{
    CommandlineParser parser(argc, argv);
    const auto options = parser.Parse();

    if (!options.cvsPrinter)
    {
        std::cout << "Size was set to " << options.dataSize << std::endl;
        std::cout << "Num of runs was set to " << options.numOfRuns << std::endl;
        std::cout << "Min was set to " << options.minPacketSize << std::endl;
        std::cout << "Max was set to " << options.maxPacketSize << std::endl;
    }

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
    benchmark.Run(options.numOfRuns);


    if (options.cvsPrinter)
    {
        CvsPrinter printer(std::cout);
        printer.PrintConfig(options);
        printer.PrintResults(hashFunctionsSet);
    }
    else
    {
        std::cout << "------------------------------------" << std::endl;
        for (const auto& hashFunction : hashFunctionsSet)
        {
            std::cout << hashFunction.name << ":";
            std::for_each(hashFunction.results.begin(), hashFunction.results.end(),
                    [](uint32_t result) {std::cout << "\t" << result;});
            std:: cout << std::endl;
        }
    }
}
