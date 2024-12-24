#include <klee/klee.h>
#include <stdio.h>
#include <stdbool.h>

bool is_prime(int num) {
    if (num <= 1) {
        return false;
    }
    for (int i = 2; i * i <= num; i++) {
        if (num % i == 0) {
            return false;
        }
    }
    return true;
}

int main() {
    int num = 2;
    klee_make_symbolic(&num, sizeof(num), "num");
    if (num < 0 || num > 1000) {
        printf("Number out of range\n");
        return 0;
    }

    if (is_prime(num)) {
        printf("🎉 It's a prime number! Cat says: 'I'm impressed! Such a special number! 😺'\n");
    } else {
        printf("😿 It's not a prime number. Cat says: 'Oh no... This number is too boring for me!'\n");

        if (num % 2 == 0) {
            printf("Bonus: This number is even. Cat says: 'Well, at least it's divisible by 2! 🐾'\n");
        } else {
            printf("Bonus: This number is odd. Cat says: 'Hmm, odd numbers are mysterious... 🐾'\n");
        }
    }

    int result = num + 2;
    if (result < num) {
        printf("⚠️ Overflow detected when doubling the number! Cat says: 'Math is hard, even for me... 😿'\n");
    } else {
        printf("Doubling the number is fine. Result: %d\n", result);
    }

    return 0;
}