#
# Build and test the plist code.
#

test:	Makefile plist.o plist.h test_plist.c
	gcc -o test_plist -lcunit plist.c test_plist.c
	./test_plist

plist.o:	plist.c plist.h
	gcc -c -o plist.o plist.c

clean:
	rm -f *.o
