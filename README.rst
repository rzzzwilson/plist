plist
=====

A 'property list' structure to save and restore name/value pairs.

The Lisp language(s) have the idea of a property list to store name/value
pairs.  This C code does much the same sort of thing.  The code here handles
strings for the name and value.

PS: I named this 'plist' after a weak memory from learning LISP a *long* time
ago.  After some research, I probably meant 'assoc list' or alist, but I don't
care to rename the repository now.

Usage
-----

To create your *PLIST*, do:

::

    #include "plist.h"

    PLIST my_plist = PlistCreate();

Now when you want to add a name/value pair to *my_plist*, do:

::
    
    PListInsert(my_plist, "abc", "abc-value");

This adds the value "abc-value" under the key "abc" to the *PLIST*.

To retrieve a value from a *PLIST* just use the key on the *PLIST*:

::

    char *value = PlistFind(my_plist, "abc");

This should return the value "abc-value".  If the key is not found the
returned value is *NULL*.

If you place two values in a plist with the same key, PlistFind() will 
return only the latest added.

::

    #include "plist.h"

    PLIST my_plist = PlistCreate();
    char *value;

    PListInsert(my_plist, "abc", "abc-value");
    PListInsert(my_plist, "abc", "abc2-value");

    value = PlistFind(my_plist, "abc");

In the above example the returned value will be "abc2-value".
