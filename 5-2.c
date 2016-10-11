#include <ctype.h>
#include <stdio.h>

#define BUFFER_SIZE 100

int buffer_index = 0;
int buffer[100];

void unget_character(int character) {
    if (buffer_index >= BUFFER_SIZE)
        printf("\nUngetch : Too many characters");
    else
        buffer[buffer_index++] = character;
}

int get_character() {
    if (buffer_index > 0)
        return buffer[--buffer_index];
    else
        return getchar();
}

int remove_spaces() {
    char character = get_character();

    while (isspace(character) && character != '\n')
        character = get_character();

    if (character == '\n')
        return 1;

    unget_character(character);

    return 0;
}

int get_float(double *pointer) {
    char character = get_character();

    if (!isdigit(character) && character != EOF && character != '+' && character != '-') {
        unget_character(character);
        return 0;
    }

    int sign = (character == '-') ? -1 : 1;
   
    if (character == '+' || character == '-') {
        int next_character = get_character();

        if (isdigit(next_character)) {
            character = next_character;
        } else {
            unget_character(next_character);
            unget_character(character);
            return 0;
        }
    }

    for (*pointer = 0; isdigit(character); character = get_character())
        *pointer = 10 * *pointer + (character - '0');

    double power = 1;

    if (character == '.') {
        character = get_character();

        for (power = 1.0; isdigit(character); character = get_character()) {
            *pointer = 10.0 * *pointer + (character - '0');
            power *= 10.0;
        }
    }
    *pointer = *pointer / power * sign;

    if (character != EOF)
        unget_character(character);

    return 1;
}

int main() {
    while (!remove_spaces()) {
        double number;

        if (get_float(&number))
            printf("Float : %g\n", number);
    }

    return 0;
}
