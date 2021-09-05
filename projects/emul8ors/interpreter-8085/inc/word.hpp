#ifndef INTERPRETER_8085_WORD_HPP
#define INTERPRETER_8085_WORD_HPP

#include <cstdint>

namespace intel_8085 {

struct Word {

    Word() = default;

    Word(Word &other) = default;

    Word(std::uint16_t data) : data_(data) {}

    auto operator=(std::uint16_t value) noexcept -> Word {
        data_ = value;
        return *this;
    }

    auto operator=(Word &other) noexcept -> Word {
        data_ = other.data_;
        return *this;
    }

    [[nodiscard]] auto operator()() noexcept -> std::uint16_t { return data_; }

private:
    std::uint16_t data_ {};
};

} // namespace intel_8085

#endif
