Two-Pass Assembler
How to execute in the command line: 

<sicxe opcodeFile programFile hashSize>      (ex. sicxe opcodefile.txt programfile.txt 8) 

Where sicxe is the name of the execution file, opcodeFile is a string containing the name of the opcode file, programFile is 
a string containing the name of the program file, and hashSize is an integer containing the size of the hash table you want to
choose.

This program accepts two files as input. The first is an opcode file, which is a file containing the opcode number
and size in bytes, of all instructions used in the program file. Each entry is formatted as follows: 

<instruction opcode byte-size\n>       (ex. mul 201 2)

Where instruction is a string containing the name of the instruction, opcode is an integer containing the opcode of the
instruction, and byte-size is an integer containing the size of the instruction in bytes. In this program we exclude 4-byte
instructions. This program will only assemble 1, 2 and 3 byte instructions. Each entry in the ocpode file is separated by a
newline character. Each instruction from the opcode file is stored in a binary tree.

Opcode file example:

compr 201 2
divf 4 3
divr 202 2
fix 5 1
j 13 3
jsub 11 3
ldb 17 3
ldx 14 3

The second file is a program file which is a file that contains the assembly language. In this file, if a line starts with a tab
character then the first token after the tab character (using space as a token delimiter) is the instruction to be carried out.
If a line starts without a tab character, then the first token is a symbol being defined. Each defined symbol from the program
is stored in a hash table along with the opcode of the instruction directly after the symbol. For example, the first symbol defined
in the following example is foo. So the key "foo" will be hashed into the table along with the value 14 which represents the opcode
value of ldx.

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

The hash table size is entirely up to the user, it can be any number greater than zero. After execution, the program will parse
through the program file twice. The first time, it will create the symbol table (using a hash table). The first token of all
instructions that don't start with a tab character is stored in the symbol table. The second time parsing, the program will
assemble each line of instructions as a binary string. a file called mycode.obj will be created in the current working
directory. This file will contain all the assembled binary code of each line in the program file.

This program will also take into account the '@' character which can be used in 3 byte instructions to signal indirect
addressing and the '#' character which can be used in 3 byte instructions to signal an immediate number.

In addition, this program will also assemble instructions that define a symbol using 'word', 'resw', 'resb'
'word x' reserves one 24 bit word with value x. 
'resw x' reserves x 24 bit words.
'resb x' reserves x bytes.

Assembling Format:
1 Byte Instruction ex: fix
1 Byte Assembling: 8BitOpcode

2 Byte Instruction ex: div R1 R2
2 Byte Assembling: 8BitOpcode 4BitRegister1 4BitRegister2

3 Byte Instruction ex: fix val
3 Byte Assembling: 6BitOpcode nixbpeBits 12BitDisplacment

'word 12' assembled: 000000000000000000001100

'resw 2' assembled: 000000000000000000000000000000000000000000000000

'resb 3' assembled: 000000000000000000000000
