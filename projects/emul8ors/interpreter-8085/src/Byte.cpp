#include "Byte.h"

namespace intel_8085
{

Byte::Byte()
{
    _data = 0;
}

Byte::Byte(const std::uint8_t data)
{
    _data = data;
}

Byte::Byte(const Byte& other)
{
    _data = other._data;
}

Byte::~Byte()
{
    _data = 0;
}

}