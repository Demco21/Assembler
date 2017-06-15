sicxe: main.o opcodeTree.o symbolTable.o buildOpcodeTree.o buildSymbolTable.o hashFunction.o utils.o input.o assembler.o
	gcc main.o opcodeTree.o symbolTable.o buildOpcodeTree.o buildSymbolTable.o hashFunction.o utils.o input.o assembler.o -o sicxe

main.o: main.c libraries.h hashNode.h bstNode.h symbolTable.h opcodeTree.h buildTables.h
	gcc -c main.c

opcodeTree.o: opcodeTree.c libraries.h bstNode.h
	gcc -c opcodeTree.c

symbolTable.o: symbolTable.c libraries.h hashNode.h hashFunction.h
	gcc -c symbolTable.c

buildOpcodeTree.o: buildOpcodeTree.c libraries.h bstNode.h
	gcc -c buildOpcodeTree.c

buildSymbolTable.o: buildSymbolTable.c libraries.h bstNode.h hashNode.h
	gcc -c buildSymbolTable.c

hashFunction.o: hashFunction.c
	gcc -c hashFunction.c

utils.o: utils.c
	gcc -c utils.c
 
input.o: input.c
	gcc -c input.c
 
assembler.o: assembler.c
	gcc -c assembler.c

clean:
	rm -f *.o core sicxe
