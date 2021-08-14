// clang -framework CoreGraphics
#include <dlfcn.h>
#include <stdio.h>
#include <stdlib.h>

#include <CoreGraphics/CGContext.h>
#include <CoreFoundation/CFData.h>

typedef struct NSObject CGSVGDocument;

int main(int argc, char *argv[]) {
    CGSVGDocument *(*CGSVGDocumentCreateFromData)(CFDataRef, CFDictionaryRef);

    void *handle = dlopen("/System/Library/PrivateFrameworks/CoreSVG.framework/CoreSVG", RTLD_NOW);

    if (!handle) {
        fprintf(stderr, "Error: %s\n", dlerror());
        return EXIT_FAILURE;
    }
   
    *(void**)(&CGSVGDocumentCreateFromData) = dlsym(handle, "CGSVGDocumentCreateFromData");

    if (!CGSVGDocumentCreateFromData) {
        fprintf(stderr, "Error: %s\n", dlerror());
        dlclose(handle);
        return EXIT_FAILURE;
    }

    /*
	void *data = calloc(height, bytesPerLine);
	CGContextRef offscreen = CGBitmapContextCreate(void *data, size_t width, size_t height, size_t bitsPerComponent, size_t bytesPerRow, CGColorSpaceRef space, uint32_t bitmapInfo);*/
    dlclose(handle);

    return EXIT_SUCCESS;
}
