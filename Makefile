#
#
#

test:	Makefile plist.c plist.h test_plist.c
	gcc -o test_plist -lcunit plist.c test_plist.c

clean:
	rm -f *.o
