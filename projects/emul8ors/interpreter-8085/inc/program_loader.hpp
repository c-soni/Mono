#ifndef INTERPRETER_8085_PROGRAM_LOADER_HPP
#define INTERPRETER_8085_PROGRAM_LOADER_HPP

#include <string>

#include "spdlog/spdlog.h"

namespace intel_8085 {

class ProgramLoader {

public:
    static auto Load(const std::string &filename) noexcept -> void {
        spdlog::info("Loading program from file: {}", filename);
    }

private:
};

} // namespace intel_8085

#endif
