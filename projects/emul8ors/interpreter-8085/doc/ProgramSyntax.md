## Syntax:
The program should contain the following elements in the **specified order**:
1. Data section (reserved addresses - `0x8000` to `0xE000`).
2. Code section (reserved addresses - `0x1000` to `0x7000`).

**NOTE:** Whitespace is significant in this format. Strictly use new lines for separating data elements and spaces after the data **ON THE SAME LINE** for comments.

#### Data section:
1. Data section should begin with the keyword `data_begin`.
2. The next line should contain a valid starting address for the data section, between `0x8000` and `0xEFFF`. Other addresses are to be used for the code section, interrupts, startup routine, etc.
3. The next line should contain the number of bytes `n` containing valid data to be stored in the data section.
4. The next `n` lines should contain the data in 8-bit hexadecimal format.
5. The last line of the data section should always be `data_end`.
6. Comments can be written on the same line as the data element by using a space (or multiple spaces, but not new lines) followed by the syntax `//<comment text>`.

Sample data section:
```
data_begin
0x8000      // Starting address for data section
0x05        // 5 bytes of data
0x31        // ASCII code for '1'
0x32        // ASCII code for '2'
0x33        // ASCII code for '3'
0x34        // ASCII code for '4'
0x35        // ASCII code for '5'
data_end
```

#### Code section:
1. Code section should begin with the keyword `code_begin`.
2. The next line should contain a valid starting address for the code section, between `0x1000` and `0x7FFF`. Other addresses are to be used for the data section, interrupts, startup routine, etc.
3. The next line onwards, write instructions exactly as written out in the `opcodes enum` from `inc/InstructionSet.h`, followed by 0-2 bytes of operands (comma separated, no whitespace).
4. The program should always end with the `HLT` instruction and should not have any operands.
5. The last line of the code section should always be `data_end`.
6. The same rules for comments as above apply to code section as well.

Sample code section:
```
code_begin
0x1000          // Starting address for code section
MVI_A,0x05      // Move data 0x05 to Accumulator
ADI,0x03        // Add data 0x03 to Accumulator (res 0x08)
RAL             // Rotate Accumulator left (res 0x10)
STA,0x00,0x20   // Store Accumulator data at location 0x2000
HLT             // Stop the program
code_end
```