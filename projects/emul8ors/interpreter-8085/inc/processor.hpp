#ifndef INTERPRETER_8085_PROCESSOR_HPP
#define INTERPRETER_8085_PROCESSOR_HPP

#include "spdlog/spdlog.h"

#include "byte.hpp"
#include "execution_unit.hpp"
#include "program_loader.hpp"
#include "register.hpp"
#include "system_memory.hpp"
#include "word.hpp"

namespace intel_8085 {

class Processor {

public:
    // Processor()

    // ~Processor()

    // LoadProgram()
    [[nodiscard]] auto LoadProgram(const std::string &filename) noexcept -> bool {
        return ProgramLoader::Load(systemMemory_, filename);
    }

    // Run()

    // DumpInfo()
    [[maybe_unused]] auto DumpInfo(std::ostream &outStream = std::cout) const noexcept -> bool {
        return systemMemory_.DumpContent(outStream);
    }

    // Shutdown()

private:
    // ExecutionUnit
    [[maybe_unused]] ExecutionUnit executionUnit_;

    // Memory
    SystemMemory systemMemory_;

    // Registers
    Register<Byte> a_;
    Register<Byte> b_;
    Register<Byte> c_;
    Register<Byte> d_;
    Register<Byte> e_;
    Register<Byte> h_;
    Register<Byte> l_;

    Register<Word> pc_;
    Register<Word> sp_;

    // Status Register
    // Register<Status> status_;

    // Clock?
};

} // namespace intel_8085

#endif
