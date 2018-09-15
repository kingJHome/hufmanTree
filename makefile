files = testhufman.c hufmanTree.c

testhufman: $(files)
	gcc -o $@ $^

testhufmandebugger: $(files)
	gcc -g $@ $^
