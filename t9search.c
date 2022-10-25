/*****************
**  Vit Pavlik  **
**   xpavli0a   **
**    251301    **
*****************/

#define DEBUG 0
#if DEBUG

/* logs plain string */
#define log(msg) fprintf(stderr, __FILE__ ":%03d: " msg "\n", __LINE__)
/* logs variable(s) */
#define logv(msg, ...) fprintf(stderr, __FILE__ ":%03d: " msg "\n", \
                               __LINE__, __VA_ARGS__)

#else

#define log(msg) {}
#define logv(msg, ...) {}

#endif

#include <stdio.h>

#define LINE_LENGTH 100
#define CONTACT_COUNT 42

const char *aliases[] = {
    "+",     // 0
    "",      // 1
    "abc",   // 2
    "def",   // 3
    "ghi",   // 4
    "jkl",   // 5
    "mno",   // 6
    "pqrs",  // 7
    "tuv",   // 8
    "wxyz"   // 9
};

/* LINE_LENGTH + 1 for the last null character */
char lines[CONTACT_COUNT * 2][LINE_LENGTH + 1];



//todo: at znak 0 reprezentuje znak +

char lowercase(char letter) {
    /* makes a letter lowercase or returns as is */
    return letter + (letter >= 'A' && letter <= 'Z') * ('a' - 'A');
}


int is_white(char character) {
    /* checks if a character is white */
    char whites[] = {
        ' ',
        '\n',  // line-feed
        '\t',  // horizontal tab
        '\v',  // vertical tab
        '\r',  // carriage return
        '\f'   // page-break
    };
    for (int i = 0; i < 6; i++) {  // there are 6 whites
        if (character == whites[i]) {
            return 1;
        }
    }
    return 0;
}


int is_all_whitespace(char str[]) {
    /* checks if a string consists of only whitespace characters */
    char c; 
    for (int i = 0; str[i] != '\0'; i++) {
        c = str[i];
        if (!is_white(c)) {
            return 0;
        }
    }
    return 1;
} 


void annul_lines() {
    /* makes first character of each line null */
    for (int i = 0; i < CONTACT_COUNT * 2; i++) {
        lines[i][0] = '\0';
    }
}


int load_line(int index) {
    /* loads one line to the specified position in "lines" array, 
       returns 0 on succes, returns EOF on EOF */

    int i = 0;
    int done = 0;
    int line_too_long = 0;
    char c;
    while (!done) {
        if ((c = getchar()) == EOF) {
            lines[index][i + 1] = '\0';
            return EOF;
        }
        if (c == '\n') {
            lines[index][i] = '\0';
            done = 1;
        }
        else {
            lines[index][i] = c;
        }

        if ((i = i + 1) == LINE_LENGTH) {  // i increments here
            lines[index][i] = '\0';
            line_too_long = 1;
            done = 1;
        }

    }

    if (line_too_long) {
        done = 0;
        while (!done) {
            if ((c = getchar()) == EOF) {
                return EOF;
            }
            if (c == '\n') {
                done = 1;
            }

        }
    }

    return 0;
}


void load_lines() {
    /* repeatedly calls load_line() 
       until CONTACT_COUNT limit or EOF is reached */
    int i = 0;
    while (i < CONTACT_COUNT * 2) {
        if (load_line(i) == EOF) {
            return;
        }
        if (!(is_all_whitespace(lines[i]))) {
            i++;
        }
    }
}


void print_line(int index) {
    if (lines[index][0] != '\0') {
        printf("line %d - \"%s\"\n", index, lines[index]);
    }

}


void print_lines() {
    for (int i = 0; i < CONTACT_COUNT * 2; i++) {
        print_line(i);
    }
}


int check_input(char input[]) {
    /* checks if input string is only digits, 
    if thats the case, returns 0, else 1  */
    for (int i = 0; input[i] != '\0'; i++) {
        if (!(input[i] >= '0' && input[i] <= '9')) {
            return 1;
        }
    }
    return 0;
}


int string_length(char string[]) {
    /* returns the number of characters not counting null at the end */
    int i;
    for (i = 0; string[i] != '\0'; i++) {}
    return i;
}


char digit_to_number(char digit) {
    /* converts ascii digit to a number, 
       which it returns in the form of signed char */
    return digit - '0';
}


void convert_argument(char argument[], int length) {
    /* in-place converts digit array to number array */
    for (int i = 0; i < length; i++) {
        argument[i] = digit_to_number(argument[i]);
    }
}


int search(char argument[], int matching_contacts) {
    /* returns index of a line */
}


int main(int argc, char *argv[]) {

    if (argc > 2) {
        fprintf(stderr, "Too many arguments: %d\n", argc);
        return 1;
    } 
    if (argc == 2 && check_input(argv[1])) {
        fprintf(stderr, "Argument contains non-digit characters: %s", argv[1]);
        return 1;
    }

    annul_lines();
    load_lines();
    print_lines();

    return 0;
}
