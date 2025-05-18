#ifndef BASE_MEMORY_H
#define BASE_MEMORY_H

#include <vector>
class BaseMemory
{
public:
    BaseMemory(size_t size);
    ~BaseMemory();
    uint8_t  read(uint16_t addr);
    void     write(uint16_t addr, uint8_t data);
    void     clear();
    unsigned size();

protected:
    std::vector<uint8_t> m_memory;
    unsigned             m_size;
};

#endif