#ifndef INTERPRETER_8085_MEMORY_H
#define INTERPRETER_8085_MEMORY_H

#include <array>
#include "Byte.h"

namespace intel_8085
{

class Memory
{
    std::array<Byte, 0x10000> _memory;

public:
    Memory();
    ~Memory();
};

}

#endif