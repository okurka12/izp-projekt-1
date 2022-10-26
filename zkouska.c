#include <stdio.h>

char foo(char *characters[]) {  // here i tried characters[][] but nah
    return characters[1][1];
}


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

    int policko[16];
    for (int i = 0; i < 16; i++) {
        printf("i = %d policko[i] = %d\n", i, policko[i]);
    }
}