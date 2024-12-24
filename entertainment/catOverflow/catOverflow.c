#include <klee/klee.h>
#include <stdio.h>
#include <limits.h>

int main() {
    int a, b;
    klee_make_symbolic(&a, sizeof(a), "a");
    klee_make_symbolic(&b, sizeof(b), "b");

    int cat_choice;
    klee_make_symbolic(&cat_choice, sizeof(cat_choice), "cat_choice");

    char *cat_name;
    int cat_mood;
    char *cat_emoji;

    if (cat_choice == 0) {
        cat_name = "Grumpy Cat";
        cat_mood = -10;
        cat_emoji = "😾";
    } else if (cat_choice == 1) {
        cat_name = "Happy Cat";
        cat_mood = 100;
        cat_emoji = "😸";
    } else if (cat_choice == 2) {
        cat_name = "Sassy Cat";
        cat_mood = 50;
        cat_emoji = "😼";
    } else if (cat_choice == 3) {
        cat_name = "Scaredy Cat";
        cat_mood = 0;
        cat_emoji = "🙀";
    } else {
        printf("Invalid choice! Choose a number between 0 and 3.\n");
        return 0;
    }

    printf("You chose: %s %s\n", cat_name, cat_emoji);
    printf("Mood of %s: %d\n", cat_name, cat_mood);

    int result = 0;

    if (a > 0 && b > 0) {
        result = a + b;
        if (result < 0) {
            printf("Overflow occurred! a = %d, b = %d, result = %d\n", a, b, result);
            printf("Here comes the sad cat: 😿 'Oh no, the numbers are too big for me!'\n");
        } else {
            printf("No overflow: a = %d, b = %d, result = %d\n", a, b, result);
        }
    } else {
        result = a * b;
        if (result < 0) {
            printf("Overflow occurred in multiplication! a = %d, b = %d, result = %d\n", a, b, result);
            printf("Here comes the sad cat: 😿 'Oh no, the numbers are too big for me!'\n");
        } else {
            printf("No overflow in multiplication: a = %d, b = %d, result = %d\n", a, b, result);
        }
    }

    if (b != 0) {
        int div_result = a / b;
        printf("Division result: %d / %d = %d\n", a, b, div_result);
    } else {
        printf("Error: division by zero! a = %d, b = %d\n", a, b);
    }

    return 0;
}