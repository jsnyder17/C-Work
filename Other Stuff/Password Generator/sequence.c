//*______Joshua Snyder______*//

#include <stdio.h>
#include <stdlib.h>

int main() {
    time_t t;
    int i, type;
    char c;

    srand((unsigned) time(&t));
    
    for (i = 0; i < 20; ++i) {
        type = rand() % 2;
        if (type == 0) {
            c = 97 + (rand() % 26);
            putchar(c);
        }
        else {
            printf("%i", rand() % 10);
        }
    }
    printf("\n");

    return 0;
}