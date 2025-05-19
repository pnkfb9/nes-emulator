#include "core/utils/RomLoader.h"

#include <fstream>

#include "core/log/Logger.h"

RomLoader::RomLoader()
{
    reset();
}

bool RomLoader::load_from_file(const std::string& path, ROM& rom, PictureProcessingUnit& ppu)
{
    std::ifstream file(path, std::ios::binary);
    prg_rom.clear();
    chr_rom.clear();
    if (!file.is_open())
    {
        LOG(ERROR, "Failed to open ROM file.");
        return false;
    }

    file.read(reinterpret_cast<char*>(&header), sizeof(header));

    // Check the "NES" magic number
    if (header.magic[0] != 'N' || header.magic[1] != 'E' || header.magic[2] != 'S'
        || header.magic[3] != 0x1A)
    {
        LOG(ERROR, "Invalid NES ROM: Missing iNES header.");
        return false;
    }

    // Check for a trainer (512 bytes, rarely used)
    bool has_trainer = (header.flags6 & 0x04) != 0;
    if (has_trainer)
    {
        file.seekg(512, std::ios::cur); // Skip trainer
    }

    // Load PRG-ROM (program code)
    size_t prg_size = header.prg_rom_size * 16384; // 16KB units
    prg_rom.resize(prg_size);
    file.read(reinterpret_cast<char*>(prg_rom.data()), prg_size);

    // Load CHR-ROM (graphics data)
    size_t chr_size = header.chr_rom_size * 8192; // 8KB units
    chr_rom.resize(chr_size);
    if (chr_size > 0)
    {
        file.read(reinterpret_cast<char*>(chr_rom.data()), chr_size);
    }
    // load to the correct locations
    rom.load(prg_rom);
    ppu.load(chr_rom);
    return true;
}

INesHeader RomLoader::getINesHeader()
{
    return header;
}

void RomLoader::reset()
{
    header = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    chr_rom.clear();
    prg_rom.clear();
}