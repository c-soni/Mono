#ifndef INTERPRETER_8085_PROCESSOR_HPP
#define INTERPRETER_8085_PROCESSOR_HPP

#include "spdlog/spdlog.h"

#include "execution_unit.hpp"
#include "program_loader.hpp"
#include "register.hpp"
#include "status_register.hpp"
#include "system_memory.hpp"

namespace intel_8085 {

class Processor {

public: // Functions/Methods
    // Processor()
    Processor() {
        a_.SetContext(systemMemory_, status_);
        b_.SetContext(systemMemory_, status_);
        c_.SetContext(systemMemory_, status_);
        d_.SetContext(systemMemory_, status_);
        e_.SetContext(systemMemory_, status_);
        h_.SetContext(systemMemory_, status_);
        l_.SetContext(systemMemory_, status_);
        pc_.SetContext(systemMemory_, status_);
        sp_.SetContext(systemMemory_, status_);
    }

    // ~Processor()

    // LoadProgram()
    [[nodiscard]] auto LoadProgram(const std::string &filename) noexcept -> bool {
        return ProgramLoader::Load(systemMemory_, filename);
    }

    // Run()

    // DumpInfo()
    auto DumpInfo(std::uint16_t startAddress = 0x0000, std::uint16_t endAddress = 0xFFFF,
        std::ostream &outStream = std::clog) const noexcept -> void {
        systemMemory_.DumpMemoryContent(startAddress, endAddress, outStream);
    }

    // Shutdown()

private: // Functions/Methods
public:  // Data Members
private: // Data Members
    // ExecutionUnit
    [[maybe_unused]] ExecutionUnit executionUnit_;

    // Memory
    SystemMemory systemMemory_;

    // Status Register
    StatusRegister status_;

    // Registers
    Register<std::uint8_t> a_ = { 0 };
    Register<std::uint8_t> b_ = { 0 };
    Register<std::uint8_t> c_ = { 0 };
    Register<std::uint8_t> d_ = { 0 };
    Register<std::uint8_t> e_ = { 0 };
    Register<std::uint8_t> h_ = { 0 };
    Register<std::uint8_t> l_ = { 0 };

    Register<std::uint16_t> pc_ = { 0 };
    Register<std::uint16_t> sp_ = { 0 };

    // Clock?
};

} // namespace intel_8085

#endif
