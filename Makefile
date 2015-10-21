#
#
#

test:	Makefile plist.c plist.h test_plist.c
	gcc -o test_plist plist.c test_plist.c

clean:
	rm -f *.o
