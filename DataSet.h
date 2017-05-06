#ifndef DATASET_H_
#define DATASET_H_

#include <stddef.h>
#include <cstdint>
#include <vector>

class DataSet
{
public:
    DataSet(size_t size, size_t minPacketSize, size_t maxPacketSize);
    ~DataSet();
    void PrepareData();

    size_t m_size;
    uint8_t* m_buffer;
    std::vector<uint32_t> m_packetLenghts;

private:
    const size_t m_minPacketSize;
    const size_t m_maxPacketSize;
};

#endif /* DATASET_H_ */
