This is a minimal reproducer for an issue with CoreSVG in that
it parses floating point numbers with locale-aware functions.

Run with:

    make
    ./test

Output:

    Unhandled operator '.'
    Unhandled operator '1'
    Unhandled operator '9'
    Unhandled operator '5'
    Unhandled operator '3'
    Unhandled operator '1'
    ...

The problem has been encountered e.g. here:

- https://trac.wxwidgets.org/ticket/19023#comment:7
- https://bugs.openjdk.java.net/browse/JDK-8265199
