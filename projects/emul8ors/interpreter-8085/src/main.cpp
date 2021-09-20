#include "spdlog/spdlog.h"

#include "instruction_set.hpp"
#include "processor.hpp"

auto main(int argc, char **argv) -> int
{
    intel_8085::Processor processor;
    if (argc == 2) {
        bool success = processor.LoadProgram(argv[1]);
        spdlog::info("Success parsing program {}: {}", argv[1], success);
        processor.DumpInfo(0x1000, 0x100F);
        processor.DumpInfo(0x8000, 0x800F);
    } else {
        spdlog::error("Expected exactly 2 arguments and received {:d}", argc);
    }
    return 0;
}
