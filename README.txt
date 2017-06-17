Two-pass assembler that converts assembly language to binary machine language

How to execute in the command line: sicxe <opcode file name> <program file name> <hash table size>
(ex. sicxe opcodefile.txt programfile.txt 8)

This program accepts two files as input.

1. An opcode file which is a file containing the opcode number of all the instructions used in the program file.
This file is formatted as follows: instruction opcode byte-size 
(ex. compr 201 2)
Where instruction is the name of the instruction, opcode is the opcode of the instruction and byte-size is the size of the instruction
in bytes. In this program we exclude 4-byte instructions. This program will only assemble 1, 2 and 3 byte instructions. Each instruction 
in the ocpode file is separated by a newline character.

Opcode file example:
compr 201 2
divf 4 3
divr 202 2
fix 5 1
j 13 3
jsub 11 3
ldb 17 3
ldx 14 3

2. A program file which is a file that contains the assembly language. In this file, if a line starts with a tab character then the 
first token after the tab character (using space as a token delimiter) is the instruction to be carried out. If a line starts without a 
tab character, then the first token is a symbol being defined.

Program file example:

	ldb val
	fix
	divr X T
foo ldx blah
label divf @blah
blah compr B A
var fix
val ldb #10
bar ldx foo
xyz fix

The hash table size is entirely up to the user, it can be any number greater than zero.
After execution, a file called mycode.obj will be created in the current working directory.
This file will containt all the assembled binary code of each line in the program file.
