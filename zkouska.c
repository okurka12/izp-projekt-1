#include <stdio.h>

int main() {
    while (1) {
        int c = getchar();
        printf("%d - %c\n", c, c);
        if (c == EOF) {
            int cc = getchar();
            printf("%d - %c\n", cc, cc);
            cc = getchar();
            printf("%d - %c\n", cc, cc);
            cc = getchar();
            printf("%d - %c\n", cc, cc);
            break;
        }
    }   
}