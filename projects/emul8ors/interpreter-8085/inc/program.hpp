#ifndef INTERPRETER_8085_PROGRAM_HPP
#define INTERPRETER_8085_PROGRAM_HPP

#include <cstdint>
#include <vector>

namespace intel_8085 {

struct DataBlock {
    std::uint16_t             startingAddress = 0x0000;
    std::vector<std::uint8_t> data            = {};
};

struct DataSection {
    std::vector<DataBlock> dataBlocks = {};
};

struct Instruction {
    // 9th bit is set to 1 if field contains a valid value
    // e.g. opcode = 0x0106, operand1 = 0x017F, operand2 = 0x0000
    // .................^..................^..................^..
    // denotes MVI_B, 0x7F.
    std::uint16_t opcode   = 0x0000;
    std::uint16_t operand1 = 0x0000;
    std::uint16_t operand2 = 0x0000;
};

struct InstructionBlock {
    std::uint16_t            startingAddress = 0x0000;
    std::vector<Instruction> instructions    = {};
};

struct CodeSection {
    std::vector<InstructionBlock> instructionBlocks = {};
};

// The Program struct can be made simpler, but for demo/debugging
// purposes we have added some more complexity.
struct Program {
    DataSection dataSection;
    CodeSection codeSection;
};

} // namespace intel_8085

#endif