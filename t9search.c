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

/* program constants */
#define LINE_LENGTH 100  // content above line length that will be stripped
#define CONTACT_COUNT 42
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


void log_line(int index, char lines[CONTACT_COUNT * 2][LINE_LENGTH + 1]) {
    if (lines[index][0] != '\0') {
        logv("line %d - \"%s\"\n", index, lines[index]);
    }

}


void log_lines(char lines[CONTACT_COUNT * 2][LINE_LENGTH + 1]) {
    for (int i = 0; i < CONTACT_COUNT * 2; i++) {
        log_line(i, lines);
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
    for (int i = 0; i < str_len - pat_len + 1; i++) {
        if (matches_pattern(pattern, string + i)) {
            return 1;
        }
    }
    return 0;
}


/* loads indices of matching lines, returns match count */
int search(char pattern[], 
           int matching_lines[], 
           char lines[CONTACT_COUNT * 2][LINE_LENGTH + 1]) {
    int match_count = 0;
    for (int i = 0; i < CONTACT_COUNT * 2; i++) {
        if (pattern_in(pattern, lines[i])) {
            logv("pattern in lines[%d] - %s", i, lines[i]);
            matching_lines[match_count] = i;
            match_count++;
        }
    }
    return match_count;
}


/* removes duplicates in int array by setting them to given value */
void remove_duplicates(int array[], int array_length, int value) {
    for (int i = 0; i < array_length; i++) {
        if (array[i] != value) {
            for (int j = i + 1; j < array_length; j++) {
                if (array[j] == array[i]) {
                    array[j] = value;
                }
            }
        }
    }
}


/* prints one contact */
void print_contact(int index, char lines[CONTACT_COUNT * 2][LINE_LENGTH + 1]) {
    logv("print_contact called with index %d", index);
    if (index % 2 != 0) {
        index -= 1;
    }
    if (lines[index][0] != '\0') {
        printf("%s, %s\n", lines[index], lines[index + 1]);
    }
}


/* in-place sets all elements of int array to given value */
void set_int_array(int array[], int value, int array_length) {
    for (int i = 0; i < array_length; i++) {
        array[i] = value;
    }
}


/* outputs discrete matching contacts based on matching line indices */
void output(int matching_lines[], 
            char lines[CONTACT_COUNT * 2][LINE_LENGTH + 1]) {
    int matching_contacts[CONTACT_COUNT * 2];
    set_int_array(matching_contacts, -1, CONTACT_COUNT * 2);
    for (int i = 0; matching_lines[i] != -1; i++) {
        if (matching_lines[i] % 2 == 0) {  // matched line is name
            matching_contacts[i] = matching_lines[i];
        } else {                           // matched line is phone number
            matching_contacts[i] = matching_lines[i] - 1;
        }
    }
    remove_duplicates(matching_contacts, CONTACT_COUNT *2, -1);
    for (int i = 0; i < CONTACT_COUNT * 2; i++) {
        if (matching_contacts[i] != -1) {
            print_contact(matching_contacts[i], lines);
        }
    }
}


/* constants and function calls to test various parts of this code,
development only, DEBUG has to be 1 */
void demo(char lines[CONTACT_COUNT * 2][LINE_LENGTH + 1]) {
    log_lines(lines);

    log("demo convert_argument");
    char arg[] = "1234567890";
    for (int i = 0; i < 10; i++) {
        logv("\t%c", arg[i]);
    }
    log("\t---");
    convert_argument(arg);
    for (int i = 0; i < 10; i++) {
        logv("\t%d", arg[i]);
    }

    char pattern1[] = {7, 3, 7, 2, -1};
    logv("xxx1 matches pattern %d\n", 
           matches_pattern(pattern1, "pepa"));
    char pattern2[] = {6, 4, 5, 2, 6, -1};
    logv("xxx2 matches pattern %d\n", 
           matches_pattern(pattern2, "mi \n  lan"));
    char pattern3[] = {7, 8, 3, 7, 2, 6, -1};
    logv("xxx3 matches pattern %d\n", 
           matches_pattern(pattern3, "StepAn"));

    logv("xxx4 pattern in %d\n", 
           pattern_in(pattern1, "Sel Pepa zalit kytky"));
    logv("xxx5 pattern in %d\n", 
           pattern_in(pattern2, "usporadej mi lan party"));
    logv("xxx6 pattern in %d\n", 
           pattern_in(pattern3, "krasny den, rekl stepan, kdyz to zrel"));
    
    /* so that compiler warnings are omitted */
    if (!DEBUG) {
        int a = pattern1[0] = pattern2[0] = pattern3[0];
        if (a) {}
    }

    int array[] = {4, 4, 6, 3, 5, 1, 8, 8, 3, 7};
    log("xxx7 remove duplicates\n");

    for (int i = 0; i < 10; i++) {
        logv("\t%d", array[i]);
    }
    remove_duplicates(array, 10, -1);
    log("\t---");
    for (int i = 0; i < 10; i++) {
        logv("\t%d", array[i]);
    }
    fprintf(stderr, "\n");
           
}


int main(int argc, char *argv[]) {
    log("starting program");

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
    logv("lines[0] %s", lines[0]);
    
    if (DEBUG) {
        log("calling demo()");
        demo(lines);
    }
    if (argc == 1) {
        for (int i = 0; i < CONTACT_COUNT * 2; i += 2) {
            print_contact(i, lines);
        }
        return 0;
    }
    logv("inputted pattern: %s", argv[1]);

    log("calling convert_argument");
    convert_argument(argv[1]);

    log("declaring matching_lines array");
    int matching_lines[CONTACT_COUNT * 2];
    set_int_array(matching_lines, -1, CONTACT_COUNT * 2);

     if (search(argv[1], matching_lines, lines) == 0) {
        printf("Not found\n");
     }
    output(matching_lines, lines);


    return 0;
}
