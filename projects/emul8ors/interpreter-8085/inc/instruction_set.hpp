#ifndef INTERPRETER_8085_INSTRUCTION_SET_HPP
#define INTERPRETER_8085_INSTRUCTION_SET_HPP

#include <cstdint>
#include <map>

namespace intel_8085 {

enum class opcodes : std::uint8_t {
    NOP      = 0x00,
    LXI_B    = 0x01,
    STAX_B   = 0x02,
    INX_B    = 0x03,
    INR_B    = 0x04,
    DCR_B    = 0x05,
    MVI_B    = 0x06,
    RLC      = 0x07,
    DAD_B    = 0x09,
    LDAX_B   = 0x0A,
    DCX_B    = 0x0B,
    INR_C    = 0x0C,
    DCR_C    = 0x0D,
    MVI_C    = 0x0E,
    RRC      = 0x0F,
    LXI_D    = 0x11,
    STAX_D   = 0x12,
    INX_D    = 0x13,
    INR_D    = 0x14,
    DCR_D    = 0x15,
    MVI_D    = 0x16,
    RAL      = 0x17,
    DAD_D    = 0x19,
    LDAX_D   = 0x1A,
    DCX_D    = 0x1B,
    INR_E    = 0x1C,
    DCR_E    = 0x1D,
    MVI_E    = 0x1E,
    RAR      = 0x1F,
    RIM      = 0x20,
    LXI_H    = 0x21,
    SHLD     = 0x22,
    INX_H    = 0x23,
    INR_H    = 0x24,
    DCR_H    = 0x25,
    MVI_H    = 0x26,
    DAA      = 0x27,
    DAD_H    = 0x29,
    LHLD     = 0x2A,
    DCX_H    = 0x2B,
    INR_L    = 0x2C,
    DCR_L    = 0x2D,
    MVI_L    = 0x2E,
    CMA      = 0x2F,
    SIM      = 0x30,
    LXI_SP   = 0x31,
    STA      = 0x32,
    INX_SP   = 0x33,
    INR_M    = 0x34,
    DCR_M    = 0x35,
    MVI_M    = 0x36,
    STC      = 0x37,
    DAD_SP   = 0x39,
    LDA      = 0x3A,
    DCX_SP   = 0x3B,
    INR_A    = 0x3C,
    DCR_A    = 0x3D,
    MVI_A    = 0x3E,
    CMC      = 0x3F,
    MOV_B_B  = 0x40,
    MOV_B_C  = 0x41,
    MOV_B_D  = 0x42,
    MOV_B_E  = 0x43,
    MOV_B_H  = 0x44,
    MOV_B_L  = 0x45,
    MOV_B_M  = 0x46,
    MOV_B_A  = 0x47,
    MOV_C_B  = 0x48,
    MOV_C_C  = 0x49,
    MOV_C_D  = 0x4A,
    MOV_C_E  = 0x4B,
    MOV_C_H  = 0x4C,
    MOV_C_L  = 0x4D,
    MOV_C_M  = 0x4E,
    MOV_C_A  = 0x4F,
    MOV_D_B  = 0x50,
    MOV_D_C  = 0x51,
    MOV_D_D  = 0x52,
    MOV_D_E  = 0x53,
    MOV_D_H  = 0x54,
    MOV_D_L  = 0x55,
    MOV_D_M  = 0x56,
    MOV_D_A  = 0x57,
    MOV_E_B  = 0x58,
    MOV_E_C  = 0x59,
    MOV_E_D  = 0x5A,
    MOV_E_E  = 0x5B,
    MOV_E_H  = 0x5C,
    MOV_E_L  = 0x5D,
    MOV_E_M  = 0x5E,
    MOV_E_A  = 0x5F,
    MOV_H_B  = 0x60,
    MOV_H_C  = 0x61,
    MOV_H_D  = 0x62,
    MOV_H_E  = 0x63,
    MOV_H_H  = 0x64,
    MOV_H_L  = 0x65,
    MOV_H_M  = 0x66,
    MOV_H_A  = 0x67,
    MOV_L_B  = 0x68,
    MOV_L_C  = 0x69,
    MOV_L_D  = 0x6A,
    MOV_L_E  = 0x6B,
    MOV_L_H  = 0x6C,
    MOV_L_L  = 0x6D,
    MOV_L_M  = 0x6E,
    MOV_L_A  = 0x6F,
    MOV_M_B  = 0x70,
    MOV_M_C  = 0x71,
    MOV_M_D  = 0x72,
    MOV_M_E  = 0x73,
    MOV_M_H  = 0x74,
    MOV_M_L  = 0x75,
    HLT      = 0x76,
    MOV_M_A  = 0x77,
    MOV_A_B  = 0x78,
    MOV_A_C  = 0x79,
    MOV_A_D  = 0x7A,
    MOV_A_E  = 0x7B,
    MOV_A_H  = 0x7C,
    MOV_A_L  = 0x7D,
    MOV_A_M  = 0x7E,
    MOV_A_A  = 0x7F,
    ADD_B    = 0x80,
    ADD_C    = 0x81,
    ADD_D    = 0x82,
    ADD_E    = 0x83,
    ADD_H    = 0x84,
    ADD_L    = 0x85,
    ADD_M    = 0x86,
    ADD_A    = 0x87,
    ADC_B    = 0x88,
    ADC_C    = 0x89,
    ADC_D    = 0x8A,
    ADC_E    = 0x8B,
    ADC_H    = 0x8C,
    ADC_L    = 0x8D,
    ADC_M    = 0x8E,
    ADC_A    = 0x8F,
    SUB_B    = 0x90,
    SUB_C    = 0x91,
    SUB_D    = 0x92,
    SUB_E    = 0x93,
    SUB_H    = 0x94,
    SUB_L    = 0x95,
    SUB_M    = 0x96,
    SUB_A    = 0x97,
    SBB_B    = 0x98,
    SBB_C    = 0x99,
    SBB_D    = 0x9A,
    SBB_E    = 0x9B,
    SBB_H    = 0x9C,
    SBB_L    = 0x9D,
    SBB_M    = 0x9E,
    SBB_A    = 0x9F,
    ANA_B    = 0xA0,
    ANA_C    = 0xA1,
    ANA_D    = 0xA2,
    ANA_E    = 0xA3,
    ANA_H    = 0xA4,
    ANA_L    = 0xA5,
    ANA_M    = 0xA6,
    ANA_A    = 0xA7,
    XRA_B    = 0xA8,
    XRA_C    = 0xA9,
    XRA_D    = 0xAA,
    XRA_E    = 0xAB,
    XRA_H    = 0xAC,
    XRA_L    = 0xAD,
    XRA_M    = 0xAE,
    XRA_A    = 0xAF,
    ORA_B    = 0xB0,
    ORA_C    = 0xB1,
    ORA_D    = 0xB2,
    ORA_E    = 0xB3,
    ORA_H    = 0xB4,
    ORA_L    = 0xB5,
    ORA_M    = 0xB6,
    ORA_A    = 0xB7,
    CMP_B    = 0xB8,
    CMP_C    = 0xB9,
    CMP_D    = 0xBA,
    CMP_E    = 0xBB,
    CMP_H    = 0xBC,
    CMP_L    = 0xBD,
    CMP_M    = 0xBE,
    CMP_A    = 0xBF,
    RNZ      = 0xC0,
    POP_B    = 0xC1,
    JNZ      = 0xC2,
    JMP      = 0xC3,
    CNZ      = 0xC4,
    PUSH_B   = 0xC5,
    ADI      = 0xC6,
    RST_0    = 0xC7,
    RZ       = 0xC8,
    RET      = 0xC9,
    JZ       = 0xCA,
    CZ       = 0xCC,
    CALL     = 0xCD,
    ACI      = 0xCE,
    RST_1    = 0xCF,
    RNC      = 0xD0,
    POP_D    = 0xD1,
    JNC      = 0xD2,
    OUT      = 0xD3,
    CNC      = 0xD4,
    PUSH_D   = 0xD5,
    SUI      = 0xD6,
    RST_2    = 0xD7,
    RC       = 0xD8,
    JC       = 0xDA,
    IN       = 0xDB,
    CC       = 0xDC,
    SBI      = 0xDE,
    RST_3    = 0xDF,
    RPO      = 0xE0,
    POP_H    = 0xE1,
    JPO      = 0xE2,
    XTHL     = 0xE3,
    CPO      = 0xE4,
    PUSH_H   = 0xE5,
    ANI      = 0xE6,
    RST_4    = 0xE7,
    RPE      = 0xE8,
    PCHL     = 0xE9,
    JPE      = 0xEA,
    XCHG     = 0xEB,
    CPE      = 0xEC,
    XRI      = 0xEE,
    RST_5    = 0xEF,
    RP       = 0xF0,
    POP_PSW  = 0xF1,
    JP       = 0xF2,
    DI       = 0xF3,
    CP       = 0xF4,
    PUSH_PSW = 0xF5,
    ORI      = 0xF6,
    RST_6    = 0xF7,
    RM       = 0xF8,
    SPHL     = 0xF9,
    JM       = 0xFA,
    EI       = 0xFB,
    CM       = 0xFC,
    CPI      = 0xFE,
    RST_7    = 0xFF
};

const std::map<std::string, opcodes> stringToInstruction { { "NOP", opcodes::NOP }, { "LXI_B", opcodes::LXI_B },
    { "STAX_B", opcodes::STAX_B }, { "INX_B", opcodes::INX_B }, { "INR_B", opcodes::INR_B },
    { "DCR_B", opcodes::DCR_B }, { "MVI_B", opcodes::MVI_B }, { "RLC", opcodes::RLC }, { "DAD_B", opcodes::DAD_B },
    { "LDAX_B", opcodes::LDAX_B }, { "DCX_B", opcodes::DCX_B }, { "INR_C", opcodes::INR_C },
    { "DCR_C", opcodes::DCR_C }, { "MVI_C", opcodes::MVI_C }, { "RRC", opcodes::RRC }, { "LXI_D", opcodes::LXI_D },
    { "STAX_D", opcodes::STAX_D }, { "INX_D", opcodes::INX_D }, { "INR_D", opcodes::INR_D },
    { "DCR_D", opcodes::DCR_D }, { "MVI_D", opcodes::MVI_D }, { "RAL", opcodes::RAL }, { "DAD_D", opcodes::DAD_D },
    { "LDAX_D", opcodes::LDAX_D }, { "DCX_D", opcodes::DCX_D }, { "INR_E", opcodes::INR_E },
    { "DCR_E", opcodes::DCR_E }, { "MVI_E", opcodes::MVI_E }, { "RAR", opcodes::RAR }, { "RIM", opcodes::RIM },
    { "LXI_H", opcodes::LXI_H }, { "SHLD", opcodes::SHLD }, { "INX_H", opcodes::INX_H }, { "INR_H", opcodes::INR_H },
    { "DCR_H", opcodes::DCR_H }, { "MVI_H", opcodes::MVI_H }, { "DAA", opcodes::DAA }, { "DAD_H", opcodes::DAD_H },
    { "LHLD", opcodes::LHLD }, { "DCX_H", opcodes::DCX_H }, { "INR_L", opcodes::INR_L }, { "DCR_L", opcodes::DCR_L },
    { "MVI_L", opcodes::MVI_L }, { "CMA", opcodes::CMA }, { "SIM", opcodes::SIM }, { "LXI_SP", opcodes::LXI_SP },
    { "STA", opcodes::STA }, { "INX_SP", opcodes::INX_SP }, { "INR_M", opcodes::INR_M }, { "DCR_M", opcodes::DCR_M },
    { "MVI_M", opcodes::MVI_M }, { "STC", opcodes::STC }, { "DAD_SP", opcodes::DAD_SP }, { "LDA", opcodes::LDA },
    { "DCX_SP", opcodes::DCX_SP }, { "INR_A", opcodes::INR_A }, { "DCR_A", opcodes::DCR_A },
    { "MVI_A", opcodes::MVI_A }, { "CMC", opcodes::CMC }, { "MOV_B_B", opcodes::MOV_B_B },
    { "MOV_B_C", opcodes::MOV_B_C }, { "MOV_B_D", opcodes::MOV_B_D }, { "MOV_B_E", opcodes::MOV_B_E },
    { "MOV_B_H", opcodes::MOV_B_H }, { "MOV_B_L", opcodes::MOV_B_L }, { "MOV_B_M", opcodes::MOV_B_M },
    { "MOV_B_A", opcodes::MOV_B_A }, { "MOV_C_B", opcodes::MOV_C_B }, { "MOV_C_C", opcodes::MOV_C_C },
    { "MOV_C_D", opcodes::MOV_C_D }, { "MOV_C_E", opcodes::MOV_C_E }, { "MOV_C_H", opcodes::MOV_C_H },
    { "MOV_C_L", opcodes::MOV_C_L }, { "MOV_C_M", opcodes::MOV_C_M }, { "MOV_C_A", opcodes::MOV_C_A },
    { "MOV_D_B", opcodes::MOV_D_B }, { "MOV_D_C", opcodes::MOV_D_C }, { "MOV_D_D", opcodes::MOV_D_D },
    { "MOV_D_E", opcodes::MOV_D_E }, { "MOV_D_H", opcodes::MOV_D_H }, { "MOV_D_L", opcodes::MOV_D_L },
    { "MOV_D_M", opcodes::MOV_D_M }, { "MOV_D_A", opcodes::MOV_D_A }, { "MOV_E_B", opcodes::MOV_E_B },
    { "MOV_E_C", opcodes::MOV_E_C }, { "MOV_E_D", opcodes::MOV_E_D }, { "MOV_E_E", opcodes::MOV_E_E },
    { "MOV_E_H", opcodes::MOV_E_H }, { "MOV_E_L", opcodes::MOV_E_L }, { "MOV_E_M", opcodes::MOV_E_M },
    { "MOV_E_A", opcodes::MOV_E_A }, { "MOV_H_B", opcodes::MOV_H_B }, { "MOV_H_C", opcodes::MOV_H_C },
    { "MOV_H_D", opcodes::MOV_H_D }, { "MOV_H_E", opcodes::MOV_H_E }, { "MOV_H_H", opcodes::MOV_H_H },
    { "MOV_H_L", opcodes::MOV_H_L }, { "MOV_H_M", opcodes::MOV_H_M }, { "MOV_H_A", opcodes::MOV_H_A },
    { "MOV_L_B", opcodes::MOV_L_B }, { "MOV_L_C", opcodes::MOV_L_C }, { "MOV_L_D", opcodes::MOV_L_D },
    { "MOV_L_E", opcodes::MOV_L_E }, { "MOV_L_H", opcodes::MOV_L_H }, { "MOV_L_L", opcodes::MOV_L_L },
    { "MOV_L_M", opcodes::MOV_L_M }, { "MOV_L_A", opcodes::MOV_L_A }, { "MOV_M_B", opcodes::MOV_M_B },
    { "MOV_M_C", opcodes::MOV_M_C }, { "MOV_M_D", opcodes::MOV_M_D }, { "MOV_M_E", opcodes::MOV_M_E },
    { "MOV_M_H", opcodes::MOV_M_H }, { "MOV_M_L", opcodes::MOV_M_L }, { "HLT", opcodes::HLT },
    { "MOV_M_A", opcodes::MOV_M_A }, { "MOV_A_B", opcodes::MOV_A_B }, { "MOV_A_C", opcodes::MOV_A_C },
    { "MOV_A_D", opcodes::MOV_A_D }, { "MOV_A_E", opcodes::MOV_A_E }, { "MOV_A_H", opcodes::MOV_A_H },
    { "MOV_A_L", opcodes::MOV_A_L }, { "MOV_A_M", opcodes::MOV_A_M }, { "MOV_A_A", opcodes::MOV_A_A },
    { "ADD_B", opcodes::ADD_B }, { "ADD_C", opcodes::ADD_C }, { "ADD_D", opcodes::ADD_D }, { "ADD_E", opcodes::ADD_E },
    { "ADD_H", opcodes::ADD_H }, { "ADD_L", opcodes::ADD_L }, { "ADD_M", opcodes::ADD_M }, { "ADD_A", opcodes::ADD_A },
    { "ADC_B", opcodes::ADC_B }, { "ADC_C", opcodes::ADC_C }, { "ADC_D", opcodes::ADC_D }, { "ADC_E", opcodes::ADC_E },
    { "ADC_H", opcodes::ADC_H }, { "ADC_L", opcodes::ADC_L }, { "ADC_M", opcodes::ADC_M }, { "ADC_A", opcodes::ADC_A },
    { "SUB_B", opcodes::SUB_B }, { "SUB_C", opcodes::SUB_C }, { "SUB_D", opcodes::SUB_D }, { "SUB_E", opcodes::SUB_E },
    { "SUB_H", opcodes::SUB_H }, { "SUB_L", opcodes::SUB_L }, { "SUB_M", opcodes::SUB_M }, { "SUB_A", opcodes::SUB_A },
    { "SBB_B", opcodes::SBB_B }, { "SBB_C", opcodes::SBB_C }, { "SBB_D", opcodes::SBB_D }, { "SBB_E", opcodes::SBB_E },
    { "SBB_H", opcodes::SBB_H }, { "SBB_L", opcodes::SBB_L }, { "SBB_M", opcodes::SBB_M }, { "SBB_A", opcodes::SBB_A },
    { "ANA_B", opcodes::ANA_B }, { "ANA_C", opcodes::ANA_C }, { "ANA_D", opcodes::ANA_D }, { "ANA_E", opcodes::ANA_E },
    { "ANA_H", opcodes::ANA_H }, { "ANA_L", opcodes::ANA_L }, { "ANA_M", opcodes::ANA_M }, { "ANA_A", opcodes::ANA_A },
    { "XRA_B", opcodes::XRA_B }, { "XRA_C", opcodes::XRA_C }, { "XRA_D", opcodes::XRA_D }, { "XRA_E", opcodes::XRA_E },
    { "XRA_H", opcodes::XRA_H }, { "XRA_L", opcodes::XRA_L }, { "XRA_M", opcodes::XRA_M }, { "XRA_A", opcodes::XRA_A },
    { "ORA_B", opcodes::ORA_B }, { "ORA_C", opcodes::ORA_C }, { "ORA_D", opcodes::ORA_D }, { "ORA_E", opcodes::ORA_E },
    { "ORA_H", opcodes::ORA_H }, { "ORA_L", opcodes::ORA_L }, { "ORA_M", opcodes::ORA_M }, { "ORA_A", opcodes::ORA_A },
    { "CMP_B", opcodes::CMP_B }, { "CMP_C", opcodes::CMP_C }, { "CMP_D", opcodes::CMP_D }, { "CMP_E", opcodes::CMP_E },
    { "CMP_H", opcodes::CMP_H }, { "CMP_L", opcodes::CMP_L }, { "CMP_M", opcodes::CMP_M }, { "CMP_A", opcodes::CMP_A },
    { "RNZ", opcodes::RNZ }, { "POP_B", opcodes::POP_B }, { "JNZ", opcodes::JNZ }, { "JMP", opcodes::JMP },
    { "CNZ", opcodes::CNZ }, { "PUSH_B", opcodes::PUSH_B }, { "ADI", opcodes::ADI }, { "RST_0", opcodes::RST_0 },
    { "RZ", opcodes::RZ }, { "RET", opcodes::RET }, { "JZ", opcodes::JZ }, { "CZ", opcodes::CZ },
    { "CALL", opcodes::CALL }, { "ACI", opcodes::ACI }, { "RST_1", opcodes::RST_1 }, { "RNC", opcodes::RNC },
    { "POP_D", opcodes::POP_D }, { "JNC", opcodes::JNC }, { "OUT", opcodes::OUT }, { "CNC", opcodes::CNC },
    { "PUSH_D", opcodes::PUSH_D }, { "SUI", opcodes::SUI }, { "RST_2", opcodes::RST_2 }, { "RC", opcodes::RC },
    { "JC", opcodes::JC }, { "IN", opcodes::IN }, { "CC", opcodes::CC }, { "SBI", opcodes::SBI },
    { "RST_3", opcodes::RST_3 }, { "RPO", opcodes::RPO }, { "POP_H", opcodes::POP_H }, { "JPO", opcodes::JPO },
    { "XTHL", opcodes::XTHL }, { "CPO", opcodes::CPO }, { "PUSH_H", opcodes::PUSH_H }, { "ANI", opcodes::ANI },
    { "RST_4", opcodes::RST_4 }, { "RPE", opcodes::RPE }, { "PCHL", opcodes::PCHL }, { "JPE", opcodes::JPE },
    { "XCHG", opcodes::XCHG }, { "CPE", opcodes::CPE }, { "XRI", opcodes::XRI }, { "RST_5", opcodes::RST_5 },
    { "RP", opcodes::RP }, { "POP_PSW", opcodes::POP_PSW }, { "JP", opcodes::JP }, { "DI", opcodes::DI },
    { "CP", opcodes::CP }, { "PUSH_PSW", opcodes::PUSH_PSW }, { "ORI", opcodes::ORI }, { "RST_6", opcodes::RST_6 },
    { "RM", opcodes::RM }, { "SPHL", opcodes::SPHL }, { "JM", opcodes::JM }, { "EI", opcodes::EI },
    { "CM", opcodes::CM }, { "CPI", opcodes::CPI }, { "RST_7", opcodes::RST_7 } };

} // namespace intel_8085

#endif
