SISAenv
---

Environment to execute SISA programs.

### Build project
1. Create ```build/``` folder
2. Run ```cmake ..``` inside the ```build``` folder
3. Run ```make``` inside the same folder, and a ```sisaenv``` executable will appear

### How to use
To use the environment, you just need to run ```./sisaenv path_to_sisa_file.sisa```, being ```path_to_sisa_file.sisa``` the file that contains the code to execute.

The supported instructions and their format are the following:
* **Arithmetic logic instructions (A/L):** AND, OR, XOR, NOT, ADD, SUB, SHA, SHL
  * OP Rd,Ra,Rb
* **Comparison instructions:** CMPLT, CMPLE, CMPEQ, CMPLTU, CMPLEU
  * CMP Rd,Ra,Rb
* **ADDI:** ADDI Rd,Ra,N6
* **Memory-access instructions:**
  * LD, LDB: LD/LDB Rd,N6(Ra)
  * ST, STB: ST/STB N6(Rd),Ra
* **JALR:** JALR Rd,Ra
* **BZ, BNZ:** BZ/BNZ Ra,N8
* **MOVI/MOVHI:** MOVI/MOVHI Rd,N8
* **IN/OUT:**
  * IN Rd,N8
  * OUT N8,Ra

![Instructions Image](https://github.com/matedavid/sisaenv/blob/master/sisa_instructions.jpg?raw=true)


### Thinks to take into account
* The N8 in IN and OUT instructions, technically refers to the direction of external devices (keyboards, printers). As this program is a virtual environment, these numbers don't actually mean nothing at the moment.
* Passing constant numbers as hexadecimal is not currently supported.
