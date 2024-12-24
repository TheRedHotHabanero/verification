#include <klee/klee.h>
#include <stdio.h>

int main() {
    int choice;
    klee_make_symbolic(&choice, sizeof(choice), "choice");

    if (choice == 1) {
        printf("🎉 You won a free vacation! Pack your bags!\n");
    } else if (choice == 2) {
        printf("🍕 Free pizza for a year! Better start exercising!\n");
    } else if (choice == 3) {
        printf("🚗 A new car! But you'll need to pay for the gas...\n");
    } else {
        printf("🙃 No prize this time. Try again!\n");
    }

    return 0;
}