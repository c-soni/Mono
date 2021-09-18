#ifndef INTERPRETER_8085_SYSTEM_MEMORY_HPP
#define INTERPRETER_8085_SYSTEM_MEMORY_HPP

#include <array>
#include <cctype>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

#include "fmt/format.h"
#include "spdlog/spdlog.h"

namespace intel_8085 {

class SystemMemory {

public: // Functions/Methods
    [[nodiscard]] auto operator[](const std::uint16_t index) noexcept -> std::uint8_t & { return memory_[index]; }

    [[nodiscard]] auto GetIterator(const std::uint16_t index = 0) noexcept
        -> std::array<std::uint8_t, 0x10000>::iterator {
        return index < memory_.size() ? memory_.begin() + index : nullptr;
    }

    auto DumpMemoryContent(std::uint16_t startAddress, std::uint16_t endAddress, std::ostream &outStream) const noexcept
        -> void {
        outStream << "\nDumping the memory content:\n\n";

        constexpr const char *tableHeader
            = "Addr:   00 01 02 03 04 05 06 07 08 09 0A 0B 0C 0D 0E 0F  ..ASCII Content.\n";

        outStream << tableHeader;
        for (std::size_t rowIndex = startAddress / 0x10; rowIndex < (endAddress + 0x10) / 0x10; rowIndex++) {
            outStream << FormatTableRow(rowIndex * 0x10);
        }
        outStream << "\nEnd of memory content:\n";
    }

private: // Functions/Methods
    [[nodiscard]] inline auto GetPrintableChar(const char c) const noexcept -> char {
        return std::isprint(c) ? c : '.';
    }

    [[nodiscard]] auto FormatTableRow(std::size_t rowStartingAddress) const noexcept -> std::string {
        constexpr const char *tableFormat = "{:#06x}: {:02X} {:02X} {:02X} {:02X} {:02X} {:02X} {:02X} {:02X} {:02X} "
                                            "{:02X} {:02X} {:02X} {:02X} {:02X} {:02X} {:02X}  {:16}\n";

        std::stringstream ss;
        for (std::size_t iter = 0; iter < 0x10; iter++) {
            ss << GetPrintableChar(static_cast<char>(memory_[rowStartingAddress + iter]));
        }

        return fmt::format(tableFormat, rowStartingAddress, memory_[rowStartingAddress + 0x00],
            memory_[rowStartingAddress + 0x01], memory_[rowStartingAddress + 0x02], memory_[rowStartingAddress + 0x03],
            memory_[rowStartingAddress + 0x04], memory_[rowStartingAddress + 0x05], memory_[rowStartingAddress + 0x06],
            memory_[rowStartingAddress + 0x07], memory_[rowStartingAddress + 0x08], memory_[rowStartingAddress + 0x09],
            memory_[rowStartingAddress + 0x0A], memory_[rowStartingAddress + 0x0B], memory_[rowStartingAddress + 0x0C],
            memory_[rowStartingAddress + 0x0D], memory_[rowStartingAddress + 0x0E], memory_[rowStartingAddress + 0x0F],
            ss.str());
    }

public:  // Data Members
private: // Data Members
    std::array<std::uint8_t, 0x10000> memory_ { 0 };
};

} // namespace intel_8085

#endif
