#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define ASCII_LOWER 32
#define ALLOC_SIZE 10000
#define MAXLINES 5000
#define MAXLEN 1000

char *lines[MAXLINES];
int field_number;

char *alloc(int size) {
    static char alloc_buffer[ALLOC_SIZE];
    static char *alloc_ptr = alloc_buffer;

    if (alloc_buffer + ALLOC_SIZE - alloc_ptr >= size) {
        alloc_ptr += size;
        return alloc_ptr - size;
    } else
        return 0;
}

int get_number(char string[MAXLEN], int index) {
    for ( ; string[index] != '\0' && !isdigit(string[index]); index++);

    int number = 0;

    while (isdigit(string[index]))
        number = 10 * number + (string[index++] - '0');

    return number;
}

int get_line(char line[MAXLEN]) {
    int character = getchar();
    int index;

    for (index = 0; index < MAXLEN - 1 && character != EOF && character != '\n'; index++) {
        line[index] = character;
        character = getchar();
    }
    
    if (character == '\n')
        line[index++] = character;

    line[index] = '\0';

    return index;
}

int read_lines(char *lines_ptr[MAXLINES]) {
    char *position_ptr; 
    char line[MAXLEN];
    int length = get_line(line);
    int lines_number = 0;

    while (length > 0) {
        if (lines_number >= MAXLINES || (position_ptr = alloc(length)) == NULL)
            return -1;
        else {
            line[length - 1] = '\0';
            strcpy(position_ptr, line);
            lines_ptr[lines_number++] = position_ptr;
        }

        length = get_line(line);
    }

    return lines_number;
}

void write_lines(char *lines_ptr[MAXLINES], int lines_number) {
    printf("\n");

    for (int index = 0; index < lines_number; index++)
        printf("%s\n", lines_ptr[index]);
}

void swap(void *lines[MAXLINES], int line_1, int line_2) {
    void *temp;

    temp = lines[line_1];
    lines[line_1] = lines[line_2];
    lines[line_2] = temp;
}

void get_field(char field[MAXLEN], char line[MAXLEN], int field_number) {
        int field_number_index = 0;
        int index = 0;
        int field_index = 0;

        while (field_number_index < field_number && line[index] != '\0' && line[index] != '\n' && line[index] != EOF) { 
            if (isspace(line[index])) {
                field_number_index++;

                for ( ; isspace(line[index]); index++);
            } else
                index++;
        }
 
        if (field_number_index != field_number) {
            field[0] = '\0'; 
        } else { 
            field[field_index++] = line[index++];
       
            while (line[index] != ' ' && line[index] != '\t' && line[index] != '\0') 
                field[field_index++] = line[index++];

            field[field_index] = '\0';
        }
}

void create_lower(char lower[MAXLEN], char string[MAXLEN]) {
    int index = 0; 

    for ( ; index < strlen(string); index++) {
        if (isupper(string[index]))
            lower[index] = string[index] + ASCII_LOWER;
        else
            lower[index] = string[index];
    }
    
    lower[++index] = '\0';
}
     
void create_dir(char directory[MAXLEN], char string[MAXLEN]) {
    int directory_index = 0;

    for (int index = 0; string[index] != '\0'; index++)
        if (isspace(string[index]) || isdigit(string[index]) || isalpha(string[index]))
            directory[directory_index++] = string[index];

    directory[directory_index] = '\0';
}

int numcmp(char string_1[MAXLEN], char string_2[MAXLEN]) { 
    if (atoi(string_1) < atoi(string_2))
        return -1;
    else if (atoi(string_1) > atoi(string_2))
        return 1;
    else
        return 0;
}

int foldcmp(char string_1[MAXLEN], char string_2[MAXLEN]) {
    char fold_1[MAXLEN];
    char fold_2[MAXLEN];

    create_lower(fold_1, string_1);
    create_lower(fold_2, string_2);

    if (strcmp(fold_1, fold_2) < 0)
        return -1;
    else if (strcmp(fold_1, fold_2) > 0)
        return 1;
    else
        return 0;
}

int dircmp(char string_1[MAXLEN], char string_2[MAXLEN]) {
    char dir_1[MAXLEN];
    char dir_2[MAXLEN];

    create_dir(dir_1, string_1);
    create_dir(dir_2, string_2); 

    if (strcmp(dir_1, dir_2) < 0)
        return -1;
    else if (strcmp(dir_1, dir_2) > 0)
        return 1;
    else
        return 0;
} 

int field_strcmp(char line_1[MAXLEN], char line_2[MAXLEN]) {
    char field_1[MAXLEN];
    char field_2[MAXLEN];

    get_field(field_1, line_1, field_number);
    get_field(field_2, line_2, field_number);

    if (strcmp(field_1, field_2) < 0)
        return -1;
    else if (strcmp(field_1, field_2) > 0)
        return 1;
    else
        return 0;
}

int field_numcmp(char line_1[MAXLEN], char line_2[MAXLEN]) {
    char field_1[MAXLEN];
    char field_2[MAXLEN];

    get_field(field_1, line_1, field_number);
    get_field(field_2, line_2, field_number);

    if (atoi(field_1) < atoi(field_2))
        return -1;
    else if (atoi(field_1) > atoi(field_2))
        return 1;
    else
        return 0;
}

int field_foldcmp(char line_1[MAXLEN], char line_2[MAXLEN]) {
    char field_1[MAXLEN];
    char field_2[MAXLEN];

    get_field(field_1, line_1, field_number);
    get_field(field_2, line_2, field_number);

    char fold_1[MAXLEN];
    char fold_2[MAXLEN];

    create_lower(fold_1, field_1);
    create_lower(fold_2, field_2);

    if (strcmp(fold_1, fold_2) < 0)
        return -1;
    else if (strcmp(fold_1, fold_2) > 0)
        return 0;
    else
        return 0;
}  

int field_dircmp(char line_1[MAXLEN], char line_2[MAXLEN]) {
    char field_1[MAXLEN];
    char field_2[MAXLEN];

    get_field(field_1, line_1, field_number);
    get_field(field_2, line_2, field_number);
        
    char dir_1[MAXLEN];
    char dir_2[MAXLEN];

    create_dir(dir_1, field_1);
    create_dir(dir_2, field_2);

    if (strcmp(dir_1, dir_2) < 0)
        return -1;
    else if (strcmp(dir_1, dir_2) > 0)
        return 1;
    else
        return 0;
}

void sort_lines(void *lines[MAXLINES], int lines_number, int (*comp)(void *, void *)) {
    for (int bubble_index_1 = 0; bubble_index_1 < lines_number - 1; bubble_index_1++)
        for (int bubble_index_2 = 0; bubble_index_2 < lines_number - bubble_index_1 - 1; bubble_index_2++) {
            if ((*comp)(lines[bubble_index_2 + 1], lines[bubble_index_2]) < 0)
                swap(lines, bubble_index_2, bubble_index_2 + 1);
        }
}

int main(int argc, char *argv[]) {
    int lines_number = read_lines(lines);

    if (argc == 1)
        sort_lines((void **) lines, lines_number, (int (*)(void *, void *))(strcmp)); 
    else {
        int reverse = 0;

        for (int arg_index = 1; arg_index < argc; arg_index++) {
            if (*argv[arg_index] == '-') {
                switch(*(argv[arg_index] + 1)) {
                    case 'n':
                        sort_lines((void **) lines, lines_number, (int (*)(void *, void *))(numcmp));
                        break;
                    case 'f':
                        sort_lines((void **) lines, lines_number, (int (*)(void *, void *))(foldcmp));
                        break; 
                    case 'd':
                        sort_lines((void **) lines, lines_number, (int (*)(void *, void *))(dircmp));
                        break;
                    case 'r':
                        reverse = 1;
                        break;
                    case 'D':
                        field_number = get_number(argv[arg_index], 0);

                        if (isdigit(*(argv[arg_index] + 2)))
                            sort_lines((void **) lines, lines_number, (int (*)(void *, void *))(field_strcmp));
                        else {
                            switch(*(argv[arg_index] + 2)) {
                                case 'N':
                                    sort_lines((void **) lines, lines_number, (int (*)(void *, void *))(field_numcmp));
                                    break;
                                case 'F':
                                    sort_lines((void **) lines, lines_number, (int (*)(void *, void *))(field_foldcmp));
                                    break; 
                                case 'D':
                                    sort_lines((void **) lines, lines_number, (int (*)(void *, void *))(field_dircmp));
                                    break;
                                case 'R':
                                    sort_lines((void **) lines, lines_number, (int (*)(void *, void *))(field_strcmp));

                                    reverse = 1;
                                    break;
                                default:
                                    printf("INVALID ARGUMENT %s", argv[arg_index]);
                            }
                        }
                        break;
                    default: 
                        printf("INVALID ARGUMENT : %s", argv[arg_index]);
                }
            }
        }

        if (reverse)
            for (int reverse_index = 0; reverse_index < lines_number / 2; reverse_index++)
                swap((void **) lines, reverse_index, lines_number - reverse_index - 1);
    }

    write_lines(lines, lines_number);

    return 0;
}
