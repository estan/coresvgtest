#include <dlfcn.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

#include <CoreFoundation/CFData.h>
#include <CoreGraphics/CGContext.h>
#include <CoreGraphics/CGBitmapContext.h>

typedef struct NSObject CGSVGDocument;

int main(int argc, char *argv[]) {
    setlocale(LC_NUMERIC, "sv_SE.UTF-8");
    putenv("CORESVG_VERBOSE=1");

    CGSVGDocument *(*CGSVGDocumentCreateFromData)(CFDataRef, CFDictionaryRef);
    void (*CGContextDrawSVGDocument)(CGContextRef, CGSVGDocument*);

    void *handle = dlopen("/System/Library/PrivateFrameworks/CoreSVG.framework/CoreSVG", RTLD_NOW);

    *(void**)(&CGSVGDocumentCreateFromData) = dlsym(handle, "CGSVGDocumentCreateFromData");
    *(void**)(&CGContextDrawSVGDocument) = dlsym(handle, "CGContextDrawSVGDocument");

    const char *svg = "<svg version=\"1.1\" xmlns=\"http://www.w3.org/2000/svg\" viewBox=\"0 0 10 10\"><path fill=\"white\" d=\"M 4 2 L 6.195312 2 L 6.195312 8.996094 L 4 8.996094 Z\"/></svg>";

    CFDataRef data = CFDataCreateWithBytesNoCopy(NULL, (const unsigned char *)svg, strlen(svg), kCFAllocatorNull);
    CGSVGDocument *document = CGSVGDocumentCreateFromData(data, NULL);
    CGColorSpaceRef colorSpace = CGColorSpaceCreateWithName(kCGColorSpaceGenericRGB);
    CGContextRef context = CGBitmapContextCreate(NULL, 10, 10, 8, 0, colorSpace, kCGImageAlphaPremultipliedLast);
    CGContextDrawSVGDocument(context, document);

    dlclose(handle);

    return EXIT_SUCCESS;
}
