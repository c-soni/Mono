#ifndef INTERPRETER_8085_PROGRAM_HPP
#define INTERPRETER_8085_PROGRAM_HPP

#include <cstdint>
#include <vector>

namespace intel_8085 {

enum class SectionType : std::uint8_t { DataSection = 0x01, CodeSection = 0x02 };

struct DataSection {
    std::uint16_t             startingAddress = 0x0000;
    std::vector<std::uint8_t> data            = {};
};

struct Instruction {
    // 9th bit is set to 1 if field contains a valid value
    // e.g. opcode = 0x0106, operand1 = 0x017F, operand2 = 0x0000
    // .................^..................^..................^..
    // denotes MVI_B, 0x7F.
    std::uint16_t opcode   = 0x0000;
    std::uint16_t operand1 = 0x0000;
    std::uint16_t operand2 = 0x0000;

    Instruction(std::uint16_t opcode, std::uint16_t operand1, std::uint16_t operand2)
        : opcode(opcode), operand1(operand1), operand2(operand2)
    {
    }
};

struct CodeSection {
    std::uint16_t            startingAddress = 0x0000;
    std::vector<Instruction> instructions    = {};
};

// The Program struct can be made simpler, but for demo/debugging
// purposes we have added some more complexity.
struct Program {
    DataSection dataSection;
    CodeSection codeSection;
};

} // namespace intel_8085

#endif
