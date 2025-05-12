#ifndef MEMORY_H
#define MEMORY_H
#include <string_view>
#include <vector>
class Memory
{
public:
    Memory(std::string_view name, size_t size);
    ~Memory();
    uint8_t read(uint16_t addr);
    void    write(uint16_t addr, uint8_t data);
    void    clear();

private:
    std::string_view     name;
    std::vector<uint8_t> m_memory;
    unsigned             m_size;
};

#endif