#ifndef INTERPRETER_8085_PROGRAM_H
#define INTERPRETER_8085_PROGRAM_H

namespace intel_8085
{

class Program
{
    const char * _fileName;

public:
    Program() = delete;
    Program(const char*);
    ~Program();
};

}

#endif