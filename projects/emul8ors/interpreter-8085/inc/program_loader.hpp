#ifndef INTERPRETER_8085_PROGRAM_LOADER_HPP
#define INTERPRETER_8085_PROGRAM_LOADER_HPP

#include <filesystem>
#include <queue>
#include <sstream>
#include <string>

#include "spdlog/spdlog.h"

#include "system_memory.hpp"

namespace intel_8085 {

class ProgramLoader {

public:
    [[nodiscard]] static auto Load(const std::string &filename, SystemMemory &memory) noexcept -> bool {
        if (ValidateFileType(filename)) {
            spdlog::info("Loading program from file: {}", filename);
            spdlog::info("Available memory size: {} Bytes", memory.GetSize());

            std::fstream            programStream(filename, std::fstream::in);
            std::string             line;
            std::queue<std::string> tokens;

            while (std::getline(programStream, line) && TokenizeLine(line, tokens, ", \t\n")) {
                spdlog::debug("Line: {}", line);
            }

            return true;
        }
        return false;
    }

private:
    [[nodiscard]] static auto ValidateFileType(const std::string &filename) noexcept -> bool {
        return std::filesystem::exists(filename) && filename.ends_with(".program");
    }

    [[nodiscard]] static auto TokenizeLine(const std::string &line, std::queue<std::string> &tokens,
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
};

} // namespace intel_8085

#endif
