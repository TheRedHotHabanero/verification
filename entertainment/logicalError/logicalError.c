#include <klee/klee.h>
#include <stdio.h>

int main() {
    int x, y;
    klee_make_symbolic(&x, sizeof(x), "x");
    klee_make_symbolic(&y, sizeof(y), "y");

    if (x > 0 && y < 0) {
        printf("😺 Valid case: x > 0 and y < 0.\n");
    } else if (x > 0 || y > 0) {  // Здесь логическая ошибка
        printf("🐾 Potentially valid case: x > 0 or y > 0.\n");
    } else if (x == 0 && y == 0) {
        printf("🙀 Unexpected edge case: x == 0 and y == 0.\n");
        klee_assert(0 && "Logical error detected!");
    } else {
        printf("😿 Something unexpected happened!\n");
    }

    return 0;
}