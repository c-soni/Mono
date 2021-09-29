#ifndef INTERPRETER_8085_PROGRAM_LOADER_HPP
#define INTERPRETER_8085_PROGRAM_LOADER_HPP

#include <filesystem>
#include <optional>
#include <queue>
#include <sstream>
#include <string>

#include "spdlog/spdlog.h"

#include "instruction_set.hpp"
#include "program.hpp"
#include "system_memory.hpp"

namespace intel_8085 {

class ProgramLoader {
public: // Functions/Methods
    [[nodiscard]] static auto Load(SystemMemory &memory, const std::string &filename) noexcept -> bool
    {
        if (ValidateFileType(filename)) {
            spdlog::info("Loading program from file: {}", filename);

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
            if (CreateProgram(program, tokens) && LoadProgram(memory, program)) {
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

    [[nodiscard]] static auto LoadProgram(SystemMemory &memory, const Program &program) noexcept -> bool
    {
        return VerifyProgram(program) && LoadProgramIntoMemory(memory, program);
    }

private: // Functions/Methods
    [[nodiscard]] static auto LoadProgramIntoMemory(SystemMemory &memory, const Program &program) noexcept -> bool
    {
        std::copy(program.dataSection.data.begin(), program.dataSection.data.end(),
            memory.GetIterator(program.dataSection.startingAddress));
        std::vector<std::uint8_t> codeSectionCondensed;
        for (const auto &instruction : program.codeSection.instructions) {
            if (instruction.opcode & 0x0100) {
                codeSectionCondensed.push_back(static_cast<std::uint8_t>(instruction.opcode & 0xFF));
            }
            if (instruction.operand1 & 0x0100) {
                codeSectionCondensed.push_back(static_cast<std::uint8_t>(instruction.operand1 & 0xFF));
            }
            if (instruction.operand2 & 0x0100) {
                codeSectionCondensed.push_back(static_cast<std::uint8_t>(instruction.operand2 & 0xFF));
            }
        }
        std::copy(codeSectionCondensed.begin(), codeSectionCondensed.end(),
            memory.GetIterator(program.codeSection.startingAddress));
        return true;
    }

    [[nodiscard]] static auto VerifyProgram(const Program &program) noexcept -> bool
    {
        return program.dataSection.startingAddress >= 0x8000 && program.dataSection.startingAddress < 0xF000
            && program.dataSection.data.size() < 0xEFFF - 0x8000 && program.codeSection.startingAddress >= 0x1000
            && program.codeSection.startingAddress < 0x8000
            && program.codeSection.instructions.size() < 0x7FFF - 0x1000;
    }

    // Owns the token queue passed in, will empty the queue before returning
    // Fills the program struct from the tokens passed in
    [[nodiscard]] static auto CreateProgram(Program &program, std::queue<std::string> &tokens) noexcept -> bool
    {
        return PopulateDataSection(program, tokens) && PopulateCodeSection(program, tokens);
    }

    [[nodiscard]] static auto PopulateDataSection(Program &program, std::queue<std::string> &tokens) noexcept -> bool
    {
        if (tokens.front() != "data_begin") {
            spdlog::debug("Did not find a data section, skipping ahead to code section");
            return true;
        }
        spdlog::debug("Found a data section, populating program struct");
        tokens.pop();
        if (PopulateSectionStartingAddress(program, tokens, SectionType::DataSection)
            && PopulateDataSectionBlock(program, tokens) && tokens.front() == "data_end") {
            tokens.pop();
            return true;
        } else {
            spdlog::error("Expected a data_end token");
            return false;
        }
    }

    [[nodiscard]] static auto PopulateCodeSection(Program &program, std::queue<std::string> &tokens) noexcept -> bool
    {
        if (tokens.front() != "code_begin") {
            spdlog::error("Code section not found, no program to execute");
            return false;
        }
        spdlog::debug("Found a code section, populating program struct");
        tokens.pop();
        if (PopulateSectionStartingAddress(program, tokens, SectionType::CodeSection)
            && PopulateCodeSectionBlock(program, tokens) && tokens.front() == "code_end") {
            tokens.pop();
            return true;
        } else {
            spdlog::error("Expected a code_end token");
            return false;
        }
    }

    [[nodiscard]] static auto PopulateSectionStartingAddress(
        Program &program, std::queue<std::string> &tokens, SectionType sectionType) noexcept -> bool
    {
        auto val = Consume<std::uint16_t>(tokens);
        if (!val.has_value()) {
            return false;
        }
        if (sectionType == SectionType::DataSection) {
            program.dataSection.startingAddress = val.value();
        } else if (sectionType == SectionType::CodeSection) {
            program.codeSection.startingAddress = val.value();
        }
        spdlog::info("Successfully parsed section starting address");
        return true;
    }

    [[nodiscard]] static auto PopulateDataSectionBlock(Program &program, std::queue<std::string> &tokens) noexcept
        -> bool
    {
        auto length = Consume<std::uint16_t>(tokens);
        if (!length.has_value()) {
            return false;
        }
        for (std::uint16_t i = 0; i < length.value(); i++) {
            auto val = Consume<std::uint8_t>(tokens);
            if (!val.has_value()) {
                return false;
            }
            program.dataSection.data.push_back(val.value());
        }
        return true;
    }

    [[nodiscard]] static auto PopulateCodeSectionBlock(Program &program, std::queue<std::string> &tokens) noexcept
        -> bool
    {
        auto firstInstruction = ParseInstruction(tokens);
        if (!firstInstruction.has_value()) {
            spdlog::error("Failure processing instructions");
            return false;
        }
        auto isHalt = [](const std::string &instruction) -> bool {
            return stringToInstruction.contains(instruction) && stringToInstruction.at(instruction) == opcodes::HLT;
        };
        program.codeSection.instructions.push_back(firstInstruction.value());
        while (!tokens.empty() && !isHalt(tokens.front())) {
            auto instruction = ParseInstruction(tokens);
            if (!instruction.has_value()) {
                return false;
            }
            program.codeSection.instructions.push_back(instruction.value());
        }
        if (tokens.empty() || !isHalt(tokens.front())) {
            spdlog::error("Expected HLT instruction at the end of program");
            return false;
        }
        auto halt = ParseInstruction(tokens);
        if (!halt.has_value()) {
            spdlog::error("Failure parsing HLT instruction: {}", tokens.front());
            return false;
        }
        program.codeSection.instructions.push_back(halt.value());
        return true;
    }

    [[nodiscard]] static auto ParseInstruction(std::queue<std::string> &tokens) noexcept -> std::optional<Instruction>
    {
        if (tokens.empty()) {
            return std::nullopt;
        }
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
        if (!stringToInstruction.contains(opcodeString)) {
            spdlog::error("Invalid instruction: {}", opcodeString);
        }

        std::uint16_t opcodeData   = static_cast<std::uint16_t>(stringToInstruction.at(opcodeString)) | 0x0100;
        std::uint16_t operand1Data = 0;
        std::uint16_t operand2Data = 0;

        if (operand1.length() > 0) {
            auto val = Parse<std::uint8_t>({ operand1.begin(), operand1.end() });
            if (!val.has_value()) {
                return std::nullopt;
            }
            operand1Data = static_cast<std::uint16_t>(val.value()) | 0x0100;
        }
        if (operand2.length() > 0) {
            auto val = Parse<std::uint8_t>({ operand2.begin(), operand2.end() });
            if (!val.has_value()) {
                return std::nullopt;
            }
            operand2Data = static_cast<std::uint16_t>(val.value()) | 0x0100;
        }

        tokens.pop();
        return { { opcodeData, operand1Data, operand2Data } };
    }

    template <typename Data>
    [[nodiscard]] static auto Consume(std::queue<std::string> &tokens) noexcept -> std::optional<Data>
    {
        auto val = Parse<Data>(tokens.front());
        if (val.has_value()) {
            tokens.pop();
        }
        return val;
    }

    template <typename Data>
    [[nodiscard]] static auto Parse(const std::string &data) noexcept -> std::optional<Data>
    {
        try {
            const unsigned long val = std::stoul(data, nullptr, 0);
            if (val >= 1 << sizeof(Data) * 8) {
                spdlog::error("Parsed Value {} (hex: {:#x}) cannot be fit into {} bytes", val, val, sizeof(Data));
                return std::nullopt;
            }
            return { static_cast<Data>(val) };
        } catch (...) {
            spdlog::error("Error parsing byte from string {}", data);
            return std::nullopt;
        }
    }

    [[maybe_unused]] static auto TokenizeLine(const std::string &line, std::queue<std::string> &tokens,
        const std::string_view delims = " \t", const std::string_view skipLineToken = "//") noexcept -> bool
    {
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
        -> std::string_view
    {
        if (const auto commentStart = line.find(skipLineToken); commentStart != line.npos) {
            line.remove_suffix(line.size() - commentStart);
        }
        return line;
    }

    [[nodiscard]] static auto TrimLine(std::string_view line, const std::string_view delims) noexcept
        -> std::string_view
    {
        line.remove_prefix(std::min(line.find_first_not_of(delims), line.size()));
        if (const auto trimPos = line.find_first_of(delims); trimPos != line.npos) {
            line.remove_suffix(line.size() - trimPos);
        }
        return line;
    }

    [[nodiscard]] static auto ValidateFileType(const std::string &filename) noexcept -> bool
    {
        return std::filesystem::exists(filename) && filename.ends_with(".program");
    }

public:  // Data Members
private: // Data Members
};

} // namespace intel_8085

#endif
