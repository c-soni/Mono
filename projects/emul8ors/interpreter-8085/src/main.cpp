#include "spdlog/spdlog.h"

#include "instruction_set.hpp"
#include "processor.hpp"

auto main() -> int {
    intel_8085::Processor processor;
    processor.LoadProgram("path/to/some/program/file.program");
    return 0;
}
