// clang -framework CoreGraphics
#include <dlfcn.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

#include <CoreGraphics/CGContext.h>
#include <CoreGraphics/CGBitmapContext.h>
#include <CoreFoundation/CFData.h>

typedef struct NSObject CGSVGDocument;

int main(int argc, char *argv[]) {
    char *result = setlocale(LC_NUMERIC, "sv_SE.UTF-8");

    if (result == NULL) {
        fprintf(stderr, "Error: Failed to set LC_NUMERIC to sv_SE.UTF-8\n");
        return EXIT_FAILURE;
    }

    CGSVGDocument *(*CGSVGDocumentCreateFromData)(CFDataRef, CFDictionaryRef);
    void (*CGContextDrawSVGDocument)(CGContextRef, CGSVGDocument*);

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

    *(void**)(&CGContextDrawSVGDocument) = dlsym(handle, "CGContextDrawSVGDocument");

    if (!CGContextDrawSVGDocument) {
        fprintf(stderr, "Error: %s\n", dlerror());
        dlclose(handle);
        return EXIT_FAILURE;
    }

    const char *svg = "<svg version=\"1.1\" xmlns=\"http://www.w3.org/2000/svg\" viewBox=\"0 0 10 10\"><path fill=\"white\" d=\"M 4 2 L 6.195312 2 L 6.195312 8.996094 L 4 8.996094 Z\"/><path fill=\"rgb(246, 187, 14)\" d=\"M 9.851562 9.453125 C 9.574219 9.859375 9.007812 9.996094 8.632812 9.996094 C 8.398438 9.996094 1.59375 9.996094 1.367188 9.996094 C 0.992188 9.996094 0.425781 9.859375 0.148438 9.453125 C -0.109375 9.074219 0.03125 8.410156 0.230469 8.046875 C 1.351562 6.027344 2.4375 3.722656 4.023438 0.707031 C 4.535156 -0.265625 5.542969 -0.195312 6.003906 0.695312 C 7.105469 2.832031 8.648438 6.027344 9.769531 8.046875 C 9.96875 8.410156 10.109375 9.074219 9.851562 9.453125 Z M 6 3 C 6 2.449219 5.550781 2 5 2 C 4.449219 2 4 2.449219 4 3 L 4 5 C 4 5.550781 4.449219 6 5 6 C 5.550781 6 6 5.550781 6 5 Z M 5 7 C 4.449219 7 4 7.449219 4 8 C 4 8.550781 4.449219 9 5 9 C 5.550781 9 6 8.550781 6 8 C 6 7.449219 5.550781 7 5 7 Z\"/></svg>";

    CFDataRef data = CFDataCreateWithBytesNoCopy(NULL, (const unsigned char *)svg, strlen(svg), kCFAllocatorNull);

    if (data == NULL) {
        fprintf(stderr, "Error: Failed to create CFData\n");
        dlclose(handle);
        return EXIT_FAILURE;
    }

    CGSVGDocument *document = CGSVGDocumentCreateFromData(data, NULL);

    if (document == NULL) {
        fprintf(stderr, "Error: Failed to create CGSVGDocument\n");
        dlclose(handle);
        return EXIT_FAILURE;
    }

    CGColorSpaceRef colorSpace = CGColorSpaceCreateWithName(kCGColorSpaceGenericRGB);
    CGContextRef context = CGBitmapContextCreate(NULL, 10, 10, 8, 0, colorSpace, kCGImageAlphaPremultipliedLast);

    CGContextDrawSVGDocument(context, document);

    dlclose(handle);

    return EXIT_SUCCESS;
}
