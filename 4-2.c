#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

double string_to_double(char string[]) {

    int index;

    for (index = 0; isspace(string[index]); index++);

    int sign = (string[index] == '-') ? -1 : 1;

    if (string[index] == '+' || string[index] == '-')
        index++;

    double value = 0;

    while (isdigit(string[index])) {
        value = 10.0 * value + (string[index] - '0');
        index++;
    }

    if (string[index] == '.')
        index++;

    double fractional_part = 1;

    for (fractional_part = 1.0; isdigit(string[index]); index++) {
        value = 10 * value + (string[index] - '0');
        fractional_part *= 10;
    }

    double e_power = 0;

    if (string[index] == 'e' || string[index] == 'E') {
        for (int after_e_index = index + 2; after_e_index < strlen(string); after_e_index++)
            e_power = e_power * 10 + (string[after_e_index] - '0');

        e_power *= (string[index + 1] == '-') ? -1 : 1;
    }

    return sign * value / fractional_part * pow(10, e_power);
}

int main() {

    char string[100];

    printf("Your string : \n\n");
    scanf("%s", string);
    printf("Your double : %g\n\n", string_to_double(string));

    return 0;
}
