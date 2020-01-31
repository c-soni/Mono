#ifndef INTERPRETER_8085_REGISTER_H
#define INTERPRETER_8085_REGISTER_H

#include "Byte.h"

namespace intel_8085
{

class Register
{
    Byte _content;

public:
    Register();
    Register(const Byte&);
    Register(const Register&);
    ~Register();

    const Byte& Content() const;
    void Content(const Byte&);
};

}

#endif