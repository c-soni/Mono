#include <iostream>
#include "instruction_set.h"

namespace intel_8085
{
    auto inst = static_cast<std::uint8_t>(intel_8085::opcodes::DAD_SP);
}

int main()
{
    std::cout << "Instruction: " << intel_8085::inst << std::endl;
    std::cout << "Done" <<  std::endl;
}