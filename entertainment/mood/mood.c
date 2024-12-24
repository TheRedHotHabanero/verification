#include <klee/klee.h>
#include <stdio.h>

int main() {
    char mood;
    klee_make_symbolic(&mood, sizeof(mood), "mood");

    switch (mood) {
        case 'h':
            printf("(＾▽＾) You're happy! Keep smiling!\n");
            break;
        case 's':
            printf("(╯︵╰,) Feeling sad? Here's a hug!\n");
            break;
        case 'a':
            printf("(╬ಠ益ಠ) Angry? Take a deep breath!\n");
            break;
        default:
            printf("(・・ )? Hmm, I can't read your mood!\n");
            break;
    }

    return 0;
}