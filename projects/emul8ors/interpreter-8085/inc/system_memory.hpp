#ifndef INTERPRETER_8085_SYSTEM_MEMORY_HPP
#define INTERPRETER_8085_SYSTEM_MEMORY_HPP

#include <array>

#include "spdlog/spdlog.h"

#include "byte.hpp"

namespace intel_8085 {

class SystemMemory {

public:
private:
    [[maybe_unused]] std::array<Byte, 0x10000> memory_;
};

} // namespace intel_8085

#endif
