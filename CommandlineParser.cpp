#include <boost/program_options.hpp>
#include "CommandlineParser.h"
#include <iostream>
#include <stddef.h>

namespace po = boost::program_options;

static const size_t DEFAULT_DATA_SIZE = 1000;
static const size_t DEFAULT_MIN_PACKET_SIZE = 64;
static const size_t DEFAULT_MAX_PACKET_SIZE = 512;

CommandlineParser::CommandlineParser(int argc, char** argv) : m_argc(argc), m_argv(argv)
{
}

CommandlineOptions CommandlineParser::Parse()
{
    CommandlineOptions options;

    po::options_description desc("Usage");
    desc.add_options()
        ("help", "produce help message")
        ("size,s", po::value<size_t>(&options.dataSize)->default_value(DEFAULT_DATA_SIZE), "data size in Megabytes (Mb)")
        ("min-packet-size,i", po::value<size_t>(&options.minPacketSize)->default_value(DEFAULT_MIN_PACKET_SIZE), "minimal packet size")
        ("max-packet-size,a", po::value<size_t>(&options.maxPacketSize)->default_value(DEFAULT_MAX_PACKET_SIZE), "minimal packet size");

    po::variables_map vm;
    po::store(po::parse_command_line(m_argc, m_argv, desc), vm);
    po::notify(vm);

    if (vm.count("help")) {
        std::cout << desc << "\n";
        exit(0);
    }

    return options;
}
