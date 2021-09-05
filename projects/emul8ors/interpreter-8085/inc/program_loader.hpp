#ifndef INTERPRETER_8085_PROGRAM_LOADER_HPP
#define INTERPRETER_8085_PROGRAM_LOADER_HPP

#include <string>

#include "spdlog/spdlog.h"

namespace intel_8085 {

class ProgramLoader {

public:
    [[nodiscard]] static auto Load(const std::string &filename) noexcept -> bool {
        spdlog::info("Loading program from file: {}", filename);
        return true;
    }

private:
};

} // namespace intel_8085

#endif
