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

#include "byte.hpp"

namespace intel_8085 {

class SystemMemory {

public:
    [[nodiscard]] constexpr auto GetSize() const noexcept -> std::size_t { return memory_.size(); }

    auto DumpContent(std::ostream &outStream = std::cout) const noexcept -> bool {
        outStream << "Dumping the file content:\n";

        constexpr const char *tableHeader
            = "Addr:   00 01 02 03 04 05 06 07 08 09 0A 0B 0C 0D 0E 0F  ..ASCII Content.\n";

        outStream << tableHeader;
        for (std::size_t rowCount = 0; rowCount < GetSize() / 0x10; rowCount++) {
            outStream << FormatTableRow(rowCount * 0x10);
        }

        return true;
    }

private:
    [[maybe_unused]] std::array<std::uint8_t, 0x10000> memory_ { 0 };

    [[nodiscard]] inline auto GetPrintableChar(const char c) const noexcept -> char {
        return std::isprint(c) ? c : '.';
    }

    [[nodiscard]] auto FormatTableRow(std::size_t rowStartingAddress) const noexcept -> std::string {
        constexpr const char *tableFormat = "{:#06x}: {:02X} {:02X} {:02X} {:02X} {:02X} {:02X} {:02X} {:02X} {:02X} "
                                            "{:02X} {:02X} {:02X} {:02X} {:02X} {:02X} {:02X}  {:8}\n";

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
};

} // namespace intel_8085

#endif
