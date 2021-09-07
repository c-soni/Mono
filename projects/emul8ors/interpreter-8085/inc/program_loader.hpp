#ifndef INTERPRETER_8085_PROGRAM_LOADER_HPP
#define INTERPRETER_8085_PROGRAM_LOADER_HPP

#include <filesystem>
#include <string>

#include "spdlog/spdlog.h"

#include "system_memory.hpp"

namespace intel_8085 {

class ProgramLoader {

public:
    [[nodiscard]] static auto Load(
        const std::string &filename, SystemMemory &memory) noexcept -> bool {
        if (ValidateFileType(filename)) {
            spdlog::info("Loading program from file: {}", filename);
            spdlog::debug("Available memory size: {} Bytes", memory.GetSize());
            return true;
        }
        return false;
    }

private:
    [[nodiscard]] static auto ValidateFileType(
        const std::string &filename) noexcept -> bool {
        return std::filesystem::exists(filename)
            && filename.ends_with(".program");
    }
};

} // namespace intel_8085

#endif
