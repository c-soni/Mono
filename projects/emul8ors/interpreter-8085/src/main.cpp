#include "spdlog/spdlog.h"

#include "instruction_set.hpp"
#include "processor.hpp"

auto main(int argc, char **argv) -> int {
    spdlog::set_level(spdlog::level::debug);
    intel_8085::Processor processor;
    if (argc == 2) {
        bool success = processor.LoadProgram(argv[1]);
        spdlog::info("Success parsing program {}: {}", argv[1], success);
    } else {
        spdlog::error("Expected exactly two arguments and received {:d}", argc);
    }
    return 0;
}
