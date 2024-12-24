#include <klee/klee.h>
#include <stdio.h>
#include <stdlib.h>

void free_memory(int* ptr, int should_free) {
    if (should_free) {
        printf("🐾 Freeing memory at %p...\n", (void*)ptr);
        free(ptr);
    } else {
        printf("😺 Skipping free for memory at %p...\n", (void*)ptr);
    }
}

int main() {
    int* data = malloc(sizeof(int));
    if (!data) {
        printf("😿 Memory allocation failed!\n");
        return -1;
    }

    *data = 42;
    printf("🐾 Allocated memory at %p with value %d\n", (void*)data, *data);

    int should_free_first, should_free_second;
    klee_make_symbolic(&should_free_first, sizeof(should_free_first), "should_free_first");
    klee_make_symbolic(&should_free_second, sizeof(should_free_second), "should_free_second");

    free_memory(data, should_free_first); // Первый вызов free
    free_memory(data, should_free_second); // Второй вызов free

    return 0;
}