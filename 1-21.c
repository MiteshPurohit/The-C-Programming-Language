#include <stdio.h>
#define TABSTOP 8

int main ()
{
    int blanksRow = 0;
    char character;
    int charsBehindTabStop = 0;
    while ((character = getchar()) != EOF) {
        if (character == " ") {
            blanksRow = 1;
        } else {
            printf("%c",character);
            blanksRow = 0;
        }
        if (charsBehindTabStop == TABSTOP) {
            charsBehindTabStop = 0;
            if (blanksRow == 1) {
                printf("\t");
            } else {
                charsBehindTabStop++;
            }
        }
    }
    return 0;
}
