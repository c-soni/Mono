#ifndef INTERPRETER_8085_REGISTER_H
#define INTERPRETER_8085_REGISTER_H

#include "Byte.h"

class Register
{
    Byte _content;
public:
    Register();
    Register(const Byte &);
    Register(const Register &);
    ~Register();
};

#endif