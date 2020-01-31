#ifndef INTERPRETER_8085_BYTE_H
#define INTERPRETER_8085_BYTE_H

namespace intel_8085
{

class Byte
{
    std::uint8_t _data;

public:
    Byte();
    Byte(const std::uint8_t);
    Byte(const Byte&);
    ~Byte();
};

}

#endif