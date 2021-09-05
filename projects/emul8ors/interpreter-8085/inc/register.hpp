#ifndef INTERPRETER_8085_REGISTER_HPP
#define INTERPRETER_8085_REGISTER_HPP

#include "spdlog/spdlog.h"

namespace intel_8085 {

template <typename Data>
class Register {

public:
private:
    Data data_;
};

} // namespace intel_8085

#endif
