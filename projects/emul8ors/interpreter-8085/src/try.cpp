#include <iostream>
#include "InstructionSet.h"
#include "Memory.h"
#include "Register.h"
#include "Program.h"

namespace intel_8085
{
    auto inst = static_cast<std::uint8_t>(intel_8085::opcodes::DAD_SP);
}

int main()
{
    std::cout << "Done: " << intel_8085::inst << std::endl;
    std::cout << "Size of the class is: " << sizeof(intel_8085::Register) << std::endl;

    auto x = intel_8085::Register(intel_8085::Byte(5));

    auto& y = x.Content();

    std::cout << "Done" <<  std::endl;
}