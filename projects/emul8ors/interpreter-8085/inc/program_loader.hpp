#ifndef INTERPRETER_8085_PROGRAM_LOADER_HPP
#define INTERPRETER_8085_PROGRAM_LOADER_HPP

#include <filesystem>
#include <queue>
#include <sstream>
#include <string>

#include "spdlog/spdlog.h"

#include "instruction_set.hpp"
#include "program.hpp"
#include "system_memory.hpp"

namespace intel_8085 {

class ProgramLoader {

public:
    [[nodiscard]] static auto Load(SystemMemory &memory, const std::string &filename) noexcept -> bool {
        if (ValidateFileType(filename)) {
            spdlog::info("Loading program from file: {}", filename);
            spdlog::info("Available memory size: {} Bytes", memory.GetSize());

            std::fstream            programStream(filename, std::fstream::in);
            std::string             line;
            std::queue<std::string> tokens;

            while (std::getline(programStream, line) && TokenizeLine(line, tokens, " \t\n")) {
                spdlog::debug("Line: {}", line);
            }

            if (tokens.empty()) {
                spdlog::error("No valid tokens found in program file");
                return false;
            }

            Program program;
            if (CreateProgram(program, tokens) && LoadProgramIntoMemory(memory, program)) {
                spdlog::info("Loaded a valid program into memory");
                spdlog::debug("Any tokens remaining to be processed: {}", !tokens.empty());

                // Data section
                spdlog::debug("Data Section Starting Address: {:#x}", program.dataSection.startingAddress);
                for (const auto val : program.dataSection.data) {
                    spdlog::debug("Data: {:#x}", val);
                }

                // Code section
                spdlog::debug("Code Section Starting Address: {:#x}", program.codeSection.startingAddress);
                for (const auto &val : program.codeSection.instructions) {
                    spdlog::debug("Instruction: {:#x}, {:#x}, {:#x}", val.opcode, val.operand1, val.operand2);
                }
                return true;
            } else {
                spdlog::error("Invalid program, could not load into memory");
                return false;
            }
            return true;
        }
        return false;
    }

    [[nodiscard]] static auto LoadProgramIntoMemory(SystemMemory &, const Program &) noexcept -> bool { return true; }

private:
    // Owns the token queue passed in, will empty the queue before returning
    // Fills the program struct from the tokens passed in
    [[nodiscard]] static auto CreateProgram(Program &program, std::queue<std::string> &tokens) noexcept -> bool {
        return PopulateDataSection(program, tokens) && PopulateCodeSection(program, tokens);
    }

    [[nodiscard]] static auto PopulateDataSection(Program &program, std::queue<std::string> &tokens) noexcept -> bool {
        bool success = true;
        if (tokens.front() == "data_begin") {
            spdlog::debug("Found a data section, populating program struct");
            tokens.pop();
            success = PopulateSectionStartingAddress(program, tokens, SectionType::DataSection)
                   && PopulateDataSectionBlock(program, tokens);
            if (tokens.front() == "data_end") {
                tokens.pop();
            } else {
                spdlog::error("Expected a data_end token");
                success = false;
            }
        } else {
            spdlog::debug("Did not find a data section, skipping ahead to code section");
        }
        return success;
    }

    [[nodiscard]] static auto PopulateCodeSection(Program &program, std::queue<std::string> &tokens) noexcept -> bool {
        bool success = true;
        if (tokens.front() == "code_begin") {
            spdlog::debug("Found a code section, populating program struct");
            tokens.pop();
            success = PopulateSectionStartingAddress(program, tokens, SectionType::CodeSection)
                   && PopulateCodeSectionBlock(program, tokens);
            if (tokens.front() == "code_end") {
                tokens.pop();
            } else {
                spdlog::error("Expected a code_end token");
                success = false;
            }
        } else {
            spdlog::error("Code section not found, no program to execute");
            success = false;
        }
        return success;
    }

    [[nodiscard]] static auto PopulateSectionStartingAddress(
        Program &program, std::queue<std::string> &tokens, SectionType sectionType) noexcept -> bool {
        auto [success, val] = ConsumeWord(tokens);
        if (success) {
            if (sectionType == SectionType::DataSection) {
                program.dataSection.startingAddress = val;
            } else if (sectionType == SectionType::CodeSection) {
                program.codeSection.startingAddress = val;
            }
            spdlog::info("Successfully parsed section starting address");
            return true;
        } else {
            return false;
        }
    }

    [[nodiscard]] static auto PopulateDataSectionBlock(Program &program, std::queue<std::string> &tokens) noexcept
        -> bool {
        auto [result, length] = ConsumeWord(tokens);
        if (result) {
            bool retVal = true;
            for (std::uint16_t i = 0; i < length; i++) {
                auto [res, val] = ConsumeByte(tokens);
                if (res) {
                    program.dataSection.data.push_back(val);
                } else {
                    retVal = false;
                    break;
                }
            }
            return retVal;
        } else {
            return false;
        }
    }

    [[nodiscard]] static auto PopulateCodeSectionBlock(Program &program, std::queue<std::string> &tokens) noexcept
        -> bool {
        auto isHalt = [](const std::string &instruction) -> bool {
            return stringToInstruction.contains(instruction) && stringToInstruction.at(instruction) == opcodes::HLT;
        };
        auto [result, instruction] = ParseInstruction(tokens);
        if (result) {
            program.codeSection.instructions.push_back(instruction);
            while (!tokens.empty() && !isHalt(tokens.front())) {
                auto [success, instruction] = ParseInstruction(tokens);
                if (!success) {
                    return false;
                } else {
                    program.codeSection.instructions.push_back(instruction);
                }
            }
            if (!tokens.empty() && isHalt(tokens.front())) {
                if (auto [res, hlt] = ParseInstruction(tokens); res) {
                    program.codeSection.instructions.push_back(hlt);
                } else {
                    spdlog::error("Failure parsing HLT instruction: {}", tokens.front());
                    return false;
                }
            } else {
                spdlog::error("Expected HLT instruction at the end of program");
                return false;
            }
            return true;
        } else {
            spdlog::error("Failure processing instructions");
        }
        return true;
    }

    [[nodiscard]] static auto ParseInstruction(std::queue<std::string> &tokens) noexcept
        -> std::tuple<bool, Instruction> {
        if (!tokens.empty()) {
            std::string_view instruction = tokens.front();
            std::string_view opcode      = instruction;
            std::string_view operand1;
            std::string_view operand2;

            auto comma1 = instruction.find_first_of(",");
            auto comma2 = instruction.find_last_of(",");
            if (comma1 != instruction.npos) {
                opcode.remove_suffix(instruction.size() - comma1);
                instruction.remove_prefix(std::min(instruction.find_first_of(",") + 1, instruction.size()));
                operand1 = instruction;
            }
            if (comma2 != instruction.npos && comma2 != comma1) {
                operand1.remove_suffix(instruction.size() - comma2);
                instruction.remove_prefix(std::min(instruction.find_first_of(",") + 1, instruction.size()));
                operand2 = instruction;
            }
            const std::string opcodeString = { opcode.begin(), opcode.end() };
            if (stringToInstruction.contains(opcodeString)) {
                std::uint16_t opcodeData   = static_cast<std::uint16_t>(stringToInstruction.at(opcodeString)) | 0x0100;
                std::uint16_t operand1Data = 0;
                std::uint16_t operand2Data = 0;
                if (operand1.length() > 0) {
                    if (auto [success, val] = ParseByte({ operand1.begin(), operand1.end() }); success) {
                        operand1Data = static_cast<std::uint16_t>(val) | 0x0100;
                    } else {
                        return { false, { 0, 0, 0 } };
                    }
                }
                if (operand2.length() > 0) {
                    if (auto [success, val] = ParseByte({ operand2.begin(), operand2.end() }); success) {
                        operand2Data = static_cast<std::uint16_t>(val) | 0x0100;
                    } else {
                        return { false, { 0, 0, 0 } };
                    }
                }
                tokens.pop();
                return { true, { opcodeData, operand1Data, operand2Data } };
            } else {
                spdlog::error("Invalid instruction: {}", opcodeString);
            }
        }
        return { false, { 0, 0, 0 } };
    }

    [[nodiscard]] static auto ConsumeByte(std::queue<std::string> &tokens) noexcept -> std::tuple<bool, std::uint8_t> {
        auto [res, val] = ParseByte(tokens.front());
        if (res) {
            tokens.pop();
        }
        return { res, val };
    }

    [[nodiscard]] static auto ConsumeWord(std::queue<std::string> &tokens) noexcept -> std::tuple<bool, std::uint16_t> {
        auto [res, val] = ParseWord(tokens.front());
        if (res) {
            tokens.pop();
        }
        return { res, val };
    }

    [[nodiscard]] static auto ParseByte(const std::string &data) noexcept -> std::tuple<bool, std::uint8_t> {
        try {
            const unsigned long val = std::stoul(data, nullptr, 0);
            if (val < 0x100) {
                return { true, static_cast<std::uint8_t>(val) };
            } else {
                spdlog::error("Parsed Value {} (hex: {:#x}) cannot be fit into 8 bits", val, val);
                return { false, 0x00 };
            }
        } catch (...) {
            spdlog::error("Error parsing byte from string {}", data);
            return { false, 0x00 };
        }
    }

    [[nodiscard]] static auto ParseWord(const std::string &data) noexcept -> std::tuple<bool, std::uint16_t> {
        try {
            const unsigned long val = std::stoul(data, nullptr, 0);
            if (val < 0x10000) {
                return { true, static_cast<std::uint16_t>(val) };
            } else {
                spdlog::error("Parsed Value {} (hex: {:#x}) cannot be fit into 16-bits", val, val);
                return { false, 0x00 };
            }
        } catch (...) {
            spdlog::error("Error parsing word from string {}", data);
            return { false, 0x00 };
        }
    }

    [[maybe_unused]] static auto TokenizeLine(const std::string &line, std::queue<std::string> &tokens,
        const std::string_view delims = " \t", const std::string_view skipLineToken = "//") noexcept -> bool {
        auto temp    = DropComment(line, skipLineToken);
        auto lineEnd = temp.end();
        auto tempIt  = temp.begin();
        while (tempIt < lineEnd) {
            temp = TrimLine(temp, delims);
            if (temp.length() > 0) {
                tokens.emplace(temp);
            }
            tempIt = temp.end();
            temp   = std::string_view(tempIt, static_cast<std::size_t>(lineEnd - tempIt));
        }
        return true;
    }

    [[nodiscard]] static auto DropComment(std::string_view line, const std::string_view skipLineToken) noexcept
        -> std::string_view {
        const auto commentStart = line.find(skipLineToken);
        if (commentStart != line.npos) {
            line.remove_suffix(line.size() - commentStart);
        }
        return line;
    }

    [[nodiscard]] static auto TrimLine(std::string_view line, const std::string_view delims) noexcept
        -> std::string_view {
        line.remove_prefix(std::min(line.find_first_not_of(delims), line.size()));
        const auto trimPos = line.find_first_of(delims);
        if (trimPos != line.npos) {
            line.remove_suffix(line.size() - trimPos);
        }
        return line;
    }

    [[nodiscard]] static auto ValidateFileType(const std::string &filename) noexcept -> bool {
        return std::filesystem::exists(filename) && filename.ends_with(".program");
    }
};

} // namespace intel_8085

#endif
