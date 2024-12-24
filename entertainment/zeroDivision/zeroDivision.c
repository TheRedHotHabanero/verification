#include <klee/klee.h>
#include <stdio.h>

int safe_division(int numerator, int denominator) {
    return numerator / denominator;
}

int main() {
    int a = 0;
    int b = 0;
    klee_make_symbolic(&a, sizeof(a), "a");
    klee_make_symbolic(&b, sizeof(b), "b");

    int result = safe_division(a, b);

    if (result != -1) {
        printf("😺 Division result: %d\n", result);
    } else {
        printf("🙀 Oops! Something went wrong with division.\n");
    }

    return 0;
}