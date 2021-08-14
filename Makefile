all: test.c
	clang -framework CoreGraphics -framework CoreFoundation -o test test.c
