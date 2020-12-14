SISAenv
---

Environment to run SISA programs, on both Harvard and Von Neumann machines / architecture. 

TODO: 
- [x] Parse inputs => separate mnemonic from registers, constants...
- [ ] Recognize mnemonics with enum or something similar
- [ ] Create register system
- [ ] Create RAM system
- [ ] Lay down functionality for each mnemonic

PIPELINE:
1. Create MEMORY (RAM) and enviroment 
2. Read file and convert instructions into hexadecimal format
3. Save conversion into 8 bit (1 byte) memory chunks
