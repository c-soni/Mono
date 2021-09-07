#ifndef INTERPRETER_8085_SYSTEM_MEMORY_HPP
#define INTERPRETER_8085_SYSTEM_MEMORY_HPP

#include <array>

#include "spdlog/spdlog.h"

#include "byte.hpp"

namespace intel_8085 {

class SystemMemory {

public:
    [[nodiscard]] constexpr auto GetSize() const noexcept -> std::size_t {
        return memory_.size();
    }

private:
    [[maybe_unused]] std::array<Byte, 0x10000> memory_;
};

} // namespace intel_8085

#endif
