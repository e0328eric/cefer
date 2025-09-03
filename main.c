#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "cefer.h"

static void closeFile(void* f) { 
    if (f && *(FILE**)f) fclose(*(FILE**)f);
    *(FILE**)f = NULL;
    printf("file is closed\n");
}
static void freePtr(void* p) {
    if (p) free(p);
    printf("Pointer %p is freed\n", p);
}

int main(void) {
    bool remain_leak = true;
    int* ptr = NULL;
    ptr = malloc(sizeof(int) * 10);
    if (!ptr) return 1;
    DEFER_IF(!remain_leak, freePtr, ptr);

    FILE* f = NULL;
    f = fopen("main.c", "r");
    printf("%p\n", f);
    if (!f) return 1;
    DEFER(closeFile, &f);
    printf("%p\n", f);

    return 0;
}

