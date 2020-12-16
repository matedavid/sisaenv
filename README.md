SISAenv
---

Environment to run SISA programs, on both Harvard and Von Neumann machines / architecture. 

TODO: 
- [x] Parse inputs => separate mnemonic from registers, constants...
- [x] Create register system
- [ ] Create conversion to bytes for the three types of instructions
- [ ] Create RAM system (add already-parsed instructions to RAM, basically)
- [ ] Create unparsing functionality (2 byte parsed instruction -> something understandable for execution)
- [ ] Lay down functionality for each mnemonic
  - [ ] A/L + ADDI
  - [ ] CMP
  - [ ] Memory-Access instructions
  - [ ] Jump instructions (BNZ, BZ, JALR)
  - [ ] MOVI / MOVHI instructions
  - [ ] IN / OUT instructions

PIPELINE:
1. Create MEMORY (RAM) and enviroment 
2. Read file and parse instructions, convert them to binary 
3. Separate binary into low and high, convert each to decimal and save to memory
4. Execute instructions (de-parse them first) using PC counter 
