#ifndef INTERPRETER_8085_MEMORY_H
#define INTERPRETER_8085_MEMORY_H

#include "Byte.h"

#include <array>

class Memory
{
    std::array<Byte, 0x100> _memory;

public:
    Memory();
    ~Memory();
};

#endif