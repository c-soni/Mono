#ifndef INTERPRETER_8085_REGISTER_HPP
#define INTERPRETER_8085_REGISTER_HPP

#include "spdlog/spdlog.h"

#include "status_register.hpp"
#include "system_memory.hpp"

namespace intel_8085 {

template <typename Data>
class Register {
public: // Functions/Methods
    Register(Data data) { data_ = data; }

    auto SetContext(const SystemMemory &memory, const StatusRegister &status) -> void
    {
        memory_ = memory;
        status_ = status;
    }

private: // Functions/Methods
public:  // Data Members
private: // Data Members
    Data           data_;
    SystemMemory   memory_;
    StatusRegister status_;
};

} // namespace intel_8085

#endif
