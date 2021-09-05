#include "spdlog/spdlog.h"

#include "instruction_set.hpp"
#include "processor.hpp"

auto main() -> int {
    intel_8085::Processor processor;
    bool success = processor.LoadProgram("path/to/some/program/file.program");
    spdlog::info("Success parsing program: {}", success);
    return 0;
}
