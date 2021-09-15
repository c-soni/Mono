#ifndef INTERPRETER_8085_STATUS_REGISTER_HPP
#define INTERPRETER_8085_STATUS_REGISTER_HPP

#include <cstdint>

namespace intel_8085 {

class StatusRegister {

public: // Functions/Methods
    [[nodiscard]] constexpr auto GetSignBit() const noexcept -> bool { return flags_ & 0x80; }

    constexpr auto SetSignBit() noexcept -> void { flags_ |= 0x80; }

    constexpr auto ResetSignBit() noexcept -> void { flags_ &= 0x7F; }

    [[nodiscard]] constexpr auto GetZeroBit() const noexcept -> bool { return flags_ & 0x40; }

    constexpr auto SetZeroBit() noexcept -> void { flags_ |= 0x40; }

    constexpr auto ResetZeroBit() noexcept -> void { flags_ &= 0xBF; }

    [[nodiscard]] constexpr auto GetACBit() const noexcept -> bool { return flags_ & 0x10; }

    constexpr auto SetACBit() noexcept -> void { flags_ |= 0x10; }

    constexpr auto ResetACBit() noexcept -> void { flags_ &= 0xEF; }

    [[nodiscard]] constexpr auto GetParityBit() const noexcept -> bool { return flags_ & 0x04; }

    constexpr auto SetParityBit() noexcept -> void { flags_ |= 0x04; }

    constexpr auto ResetParityBit() noexcept -> void { flags_ &= 0xFB; }

    [[nodiscard]] constexpr auto GetCarryBit() const noexcept -> bool { return flags_ & 0x01; }

    constexpr auto SetCarryBit() noexcept -> void { flags_ |= 0x01; }

    constexpr auto ResetCarryBit() noexcept -> void { flags_ &= 0xFE; }

private: // Functions/Methods
public:  // Data Members
private: // Data Members
    std::uint8_t flags_ = 0;
    // Bit positions of flags:
    // std::uint8_t s_  = 7; // Sign flag
    // std::uint8_t z_  = 6; // Zero flag
    // std::uint8_t ac_ = 4; // Auxiliary Carry flag
    // std::uint8_t p_  = 2; // Parity flag
    // std::uint8_t cy_ = 0; // Carry flag
};

} // namespace intel_8085

#endif
