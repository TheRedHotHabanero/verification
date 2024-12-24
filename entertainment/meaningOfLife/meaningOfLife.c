#include <klee/klee.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    int number = 42;
    klee_make_symbolic(&number, sizeof(number), "number");

    if (number == 42) {
        printf("Congratulations! You've discovered the meaning of life!\n");
    } else if (number > 100) {
        printf("Whoa, that's a big number! Try something smaller.\n");
    } else {
        printf("Nope, %d is not the answer.\n", number);
    }

    return 0;
}