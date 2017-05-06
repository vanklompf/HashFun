#ifndef COMMANDLINE_PARSER_H_
#define COMMANDLINE_PARSER_H_

struct CommandlineOptions
{
    size_t dataSize;
    size_t minPacketSize;
    size_t maxPacketSize;
};

class CommandlineParser
{
public:
    CommandlineParser(int argc, char** argv);
    CommandlineOptions Parse();

private:
    int m_argc;
    char** m_argv;
};
#endif /* COMMANDLINE_PARSER_H_ */
