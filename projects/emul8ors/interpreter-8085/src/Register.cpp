#include "Register.h"

namespace intel_8085
{

Register::Register()
{
    _content = Byte();
}

Register::Register(const Byte& byte)
{
    _content = byte;
}

Register::Register(const Register& other)
{
    _content = other._content;
}

Register::~Register()
{
    _content = Byte();
}

const Byte& Register::Content() const
{
    return _content;
}

void Register::Content(const Byte& other)
{
    _content = other;
}

}