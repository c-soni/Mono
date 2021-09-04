#include "spdlog/spdlog.h"

#include "instruction_set.h"

auto main() -> int {

    spdlog::info("Hello World {}", intel_8085::opcodes::DAD_SP);

    return 0;

}
