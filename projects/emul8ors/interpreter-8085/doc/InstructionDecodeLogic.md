## Decoding Logic:

### Instruction:
Intel 8085 instruction set consists of `246` 8-bit instructions (opcodes). These may be followed by `0`, `1` or `2` 8-bit operands depending on the type of instruction.

`| opcode (8 bits) | operand1 (8 bits) | operand2 (8 bits) |`

### Opcode:
`| 7 | 6 | 5 | 4 | 3 | 2 | 1 | 0 | --> individual bits of opcode`

Bits `7` and `6` decide the opcode group.

1. `00` group - Multiple instructions, miscellaneous.
2. `01` group - `MOV` instructions (register and memory, no indirect).
3. `10` group - ALU based instructions.
4. `11` group - Control flow and processor instructions.

### 00 Group:
`| 7 | 6 | 5 | 4 | 3 | 2 | 1 | 0 | --> bits`

`| 0 | 0 | _ | _ | _ | _ | _ | _ |`

##### If bit `2` is `1`:

`| 7 | 6 | 5 | 4 | 3 | 2 | 1 | 0 | --> bits`

`| 0 | 0 | _ | _ | _ | 1 | _ | _ |`

`|_______|__operand__|__operation|`

Operation:
1. `00` - `INR`.
2. `01` - `DCR`.
3. `10` - `MVI`.
4. `11` - `RLC, RRC, RAL, RAR, DAA, CMA, STC, CMC (no operands, implicit Accumulator)`.

Operand:
1. `000` - Register `B`.
2. `001` - Register `C`.
3. `010` - Register `D`.
4. `011` - Register `E`.
5. `100` - Register `H`.
6. `101` - Register `L`.
7. `110` - Memory location pointed by `HL` pair (`M`).
8. `111` - Register `A`.

##### If bit `2` is `0`:

`| 7 | 6 | 5 | 4 | 3 | 2 | 1 | 0 | --> bits`

`| 0 | 0 | _ | _ | _ | 0 | _ | _ |`

`|_______|operand|__operation____|`

Operation (bits `3`, `1` and `0`):
1. `000` - `NOP, reserved, RIM, SIM`.
2. `001` - `LXI`.
3. `010` - `STAX`.
4. `011` - `INX`.
5. `100` - `reserved`.
6. `101` - `DAD`.
7. `110` - `LDAX`.
8. `111` - `DCX`.

Operand:
1. `00` - Register pair `BC`.
2. `01` - Register pair `DE`.
3. `10` - Register pair `HL`.
4. `11` - Register `SP` (Stack Pointer).

### 01 Group:
`| 7 | 6 | 5 | 4 | 3 | 2 | 1 | 0 | --> bits`

`| 0 | 1 | _ | _ | _ | _ | _ | _ |`

`|__MOV__|destination|___source__|`

Destiation, Source operands:
1. `000` - Register `B`.
2. `001` - Register `C`.
3. `010` - Register `D`.
4. `011` - Register `E`.
5. `100` - Register `H`.
6. `101` - Register `L`.
7. `110` - Memory location pointed by `HL` pair (`M`).
8. `111` - Register `A`.

Special case: Opcode `0x76`.

`| 7 | 6 | 5 | 4 | 3 | 2 | 1 | 0 | --> bits`

`| 0 | 1 | 1 | 1 | 0 | 1 | 1 | 0 |`

`|__MOV__|___memory__|___memory__|`

Memory - Memory data movement is prohibited, so this opcode is used to halt (`HLT`) the processor execution.

### 10 Group:
`| 7 | 6 | 5 | 4 | 3 | 2 | 1 | 0 | --> bits`

`| 1 | 0 | _ | _ | _ | _ | _ | _ |`

`|_______|_operation_|__operand__|`

Destination operand is implicit and always the Accumulator (`A`).

Operation:
1. `000` - `ADD`.
2. `001` - `ADC`.
3. `010` - `SUB`.
4. `011` - `SBB`.
5. `100` - `ANA`.
6. `101` - `XRA`.
7. `110` - `ORA`.
8. `111` - `CMP`.

Operand:
1. `000` - Register `B`.
2. `001` - Register `C`.
3. `010` - Register `D`.
4. `011` - Register `E`.
5. `100` - Register `H`.
6. `101` - Register `L`.
7. `110` - Memory location pointed by `HL` pair (`M`).
8. `111` - Register `A`.

### 11 Group:
`| 7 | 6 | 5 | 4 | 3 | 2 | 1 | 0 | --> bits`

`| 1 | 0 | _ | _ | _ | _ | _ | _ |`

`|_______|__operand__|_operation_|`

Operation:
1. `000` - Conditional `RET` (`RNZ`, `RZ`, etc).
2. `001` - `POP`, `RET`, `PCHL`, `SPHL`.
3. `010` - Conditional `JMP` (`JNZ`, `JZ`, etc).
4. `011` - `JMP`, `OUT`, `IN`, `XTHL`, `XCHG`, `DI`, `EI`.
5. `100` - Conditional `CALL` (`CNZ`, `CZ`, etc).
6. `101` - `PUSH`, `CALL`.
7. `110` - Arithmetic and Logic Immediate (`ADI`, `XRI`, etc).
8. `111` - `RST`.

Operand (`2`/`3` bits):
1. `00` - Register pair `BC`.
2. `01` - Register pair `DE`.
3. `10` - Register pair `HL`.
4. `11` - Register `SP` (Stack Pointer).
5. 3 bits are used to vector address the `RST` instruction (`RST_0` - `RST_7`)
