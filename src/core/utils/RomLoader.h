#ifndef ROM_LOADER_H
#define ROM_LOADER_H

#include <string>

#include "core/graphics/PictureProcessingUnit.h"
#include "core/mem/ROM.h"

struct INesHeader
{
    uint8_t magic[4];     // "NES" + 0x1A
    uint8_t prg_rom_size; // Size of PRG-ROM in 16KB units
    uint8_t chr_rom_size; // Size of CHR-ROM in 8KB units (0 = CHR-RAM)
    uint8_t flags6;       // Mapper low nibble, mirroring, battery, trainer
    uint8_t flags7;       // Mapper high nibble, NES 2.0 identifier
    uint8_t prg_ram_size; // PRG-RAM size (rarely used)
    uint8_t flags9;
    uint8_t flags10;
    uint8_t padding[5]; // Unused (should be zero)
};

class RomLoader
{
public:
    RomLoader();
    INesHeader getINesHeader();
    bool       load_from_file(const std::string& file_path, ROM& rom, PictureProcessingUnit& ppu);
    void       reset();

private:
    // Read the 16-byte header
    INesHeader           header;
    std::vector<uint8_t> prg_rom;
    std::vector<uint8_t> chr_rom;
};
#endif