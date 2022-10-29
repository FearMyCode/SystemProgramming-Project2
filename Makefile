all:
	gcc trove.c hashtable.c list.c directory.c -std=c11 -Wall -Werror -o trove

clean:
	del trove.exe

