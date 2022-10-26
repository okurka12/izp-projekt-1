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

/* program constants (note, aliases can be redefined in "does_match" fn) */
#define LINE_LENGTH 100
#define CONTACT_COUNT 42


/* makes a letter lowercase or returns as is */
char lowercase(char letter) {
    return letter + (letter >= 'A' && letter <= 'Z') * ('a' - 'A');
}


/* checks if a character is white */
int is_white(char character) {
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


/* checks if a string consists of only whitespace characters */
int is_all_whitespace(char str[]) {
    char c; 
    for (int i = 0; str[i] != '\0'; i++) {
        c = str[i];
        if (!is_white(c)) {
            return 0;
        }
    }
    return 1;
} 


/* makes first character of each line null */
void annul_lines(char lines[CONTACT_COUNT * 2][LINE_LENGTH + 1]) {
    for (int i = 0; i < CONTACT_COUNT * 2; i++) {
        lines[i][0] = '\0';
    }
}


/* loads one line to the specified position in "lines" array, 
returns 0 on succes, returns EOF on EOF */
int load_line(int index, char lines[CONTACT_COUNT * 2][LINE_LENGTH + 1]) {

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


/* repeatedly calls load_line()
until CONTACT_COUNT limit or EOF is reached */
void load_lines(char lines[CONTACT_COUNT * 2][LINE_LENGTH + 1]) {
    int i = 0;
    while (i < CONTACT_COUNT * 2) {
        if (load_line(i, lines) == EOF) {
            return;
        }
        if (!(is_all_whitespace(lines[i]))) {
            i++;
        }
    }
}


void print_line(int index, char lines[CONTACT_COUNT * 2][LINE_LENGTH + 1]) {
    if (lines[index][0] != '\0') {
        printf("line %d - \"%s\"\n", index, lines[index]);
    }

}


void print_lines(char lines[CONTACT_COUNT * 2][LINE_LENGTH + 1]) {
    for (int i = 0; i < CONTACT_COUNT * 2; i++) {
        print_line(i, lines);
    }
}


/* checks if input string is only digits, 
if thats the case, returns 0, else 1  */
int check_input(char input[]) {
    for (int i = 0; input[i] != '\0'; i++) {
        if (!(input[i] >= '0' && input[i] <= '9')) {
            return 1;
        }
    }
    return 0;
}


/* returns the number of characters not counting null at the end */
int string_length(char string[]) {
    int i;
    for (i = 0; string[i] != '\0'; i++) {}
    return i;
}


/* converts ascii digit to a number, 
which it returns in the form of signed char */
char digit_to_number(char digit) {
    return digit - '0';
}


/* in-place converts digit string to -1 terminated number array */
void convert_argument(char argument[]) {
    int i;
    for (i = 0; argument[i] != '\0'; i++) {
        argument[i] = digit_to_number(argument[i]);
    }
    argument[i] = -1;
}


/* returns 1 if character is an alias for given number, 0 if it's not, 
case-insensitive */
int does_match(int number, char character) {
    const char *aliases[] = {
        "0+",     // 0
        "1",      // 1
        "2abc",   // 2
        "3def",   // 3
        "4ghi",   // 4
        "5jkl",   // 5
        "6mno",   // 6
        "7pqrs",  // 7
        "8tuv",   // 8
        "9wxyz"   // 9
    };

    logv("does_match called witch n=%d, ch=%c", number, character);
    for (int i = 0; aliases[number][i] != '\0'; i++)
        if (aliases[number][i] == lowercase(character)) {
            return 1;
        }
    return 0;
}


/* returns 1 if given string matches pattern (-1 terminated signed char 
numbers, NOT ASCII digits), ignores whitespaces, 
string must not be shorter than pattern */
int matches_pattern(char pattern[], char string[]) {
    int offset = 0;
    for (int i = 0; pattern[i] != -1; i++) {
        while (is_white(string[i + offset])) {
            offset++;
        }
        if (!does_match(pattern[i], string[i + offset])) {
            return 0;
        }
    }
    return 1;

}



/* returns length of a pattern (-1 terminated array of chars) */
int pattern_length(char pattern[]) {
    int i;
    for (i = 0; pattern[i] != -1; i++) {}
    return i;
}


/* checks if given pattern (-1 terminated signed char numbers) is anywhere 
in the string */
int pattern_in(char pattern[], char string[]) {
    int str_len = string_length(string);
    int pat_len = pattern_length(pattern);
    for (int i = 0; i < str_len - pat_len; i++) {
        if (matches_pattern(pattern, string + i)) {
            return 1;
        }
    }
    return 0;
}


/* loads indices of matching lines */
int search(char pattern[], int matches[]) {
    // to be done later
}


void demo() {
    char pattern1[] = {7, 3, 7, 2, -1};
    printf("xxx1 matches pattern %d\n", 
           matches_pattern(pattern1, "pepa"));
    char pattern2[] = {6, 4, 5, 2, 6, -1};
    printf("xxx2 matches pattern %d\n", 
           matches_pattern(pattern2, "mi \n  lan"));
    char pattern3[] = {7, 8, 3, 7, 2, 6, -1};
    printf("xxx3 matches pattern %d\n", 
           matches_pattern(pattern3, "StepAn"));

    printf("xxx4 pattern in %d\n", 
           pattern_in(pattern1, "Sel Pepa zalit kytky"));
    printf("xxx5 pattern in %d\n", 
           pattern_in(pattern2, "usporadej mi lan party"));
    printf("xxx6 pattern in %d\n", 
           pattern_in(pattern3, "to je krasny den, rekl stepan, kdyz to zrel"));
           
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

    /* LINE_LENGTH + 1 for the last null character */
    char lines[CONTACT_COUNT * 2][LINE_LENGTH + 1];
    annul_lines(lines);
    load_lines(lines);
    print_lines(lines);

    convert_argument(argv[1]);
    int matches[CONTACT_COUNT * 2];

    if (DEBUG) {
        demo();
    }

    return 0;
}
