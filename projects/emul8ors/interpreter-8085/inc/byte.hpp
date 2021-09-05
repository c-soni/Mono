#ifndef INTERPRETER_8085_BYTE_HPP
#define INTERPRETER_8085_BYTE_HPP

#include <cstdint>

namespace intel_8085 {

struct Byte {

    Byte() = default;

    Byte(Byte &other) = default;

    Byte(std::uint8_t data) : data_(data) {}

    auto operator=(std::uint8_t value) noexcept -> Byte {
        data_ = value;
        return *this;
    }

    auto operator=(Byte &other) noexcept -> Byte {
        data_ = other.data_;
        return *this;
    }

    [[nodiscard]] auto operator()() noexcept -> std::uint8_t { return data_; }

private:
    std::uint8_t data_ {};
};

} // namespace intel_8085

#endif
