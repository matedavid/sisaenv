SISAenv
---

Environment to run SISA programs, on both Harvard and Von Neumann machines / architecture. 

TODO: 
- [x] Parse inputs => separate mnemonic from registers, constants...
- [x] Create register system
- [x] Create conversion to bytes for the three types of instructions
- [x] Create RAM system (add already-parsed instructions to RAM, basically)
- [x] Create unparsing functionality (2 byte parsed instruction -> something understandable for execution)
- [ ] Lay down functionality for each mnemonic
  - [x] A/L + ADDI
  - [x] CMP
  - [x] Memory-Access instructions
  - [x] Jump instructions (BNZ, BZ, JALR)
  - [ ] MOVI / MOVHI instructions (Still have to implement MOVHI)
  - [x] IN / OUT instructions

