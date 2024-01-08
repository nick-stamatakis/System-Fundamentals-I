#include "../include/hw5.h"

bool isValidWildcard(char *search) {
    printf(search);

    if (search == NULL || search[0] == '\0') {
        return false;  // Null pointer or empty string is not valid
    }

    int len = strlen(search);

    if (search[0] == '*' && search[len - 1] == '*') {
        return false;
    }

    if (search[0] == '*' || search[len - 1] == '*') {
        for (int i = 1; i < len - 1; i++) {
            if (search[i] == '*') {
                return false;  // Middle characters cannot be "*"
            }
        }
        return true;
    }

    return false;  // "*" should be at the beginning or end
}

void replaceText(FILE *input, FILE *output, const char *search, const char *replace, bool wildcard, int start_line, int end_line) {
    char line[MAX_LINE];
    int current_line = 0;
    int search_len = strlen(search);

    while (fgets(line, sizeof(line), input) != NULL) {
        current_line++;

        if (current_line >= start_line && (end_line == 0 || current_line <= end_line)) {
            char *match = line;
            char *temp = line;
            bool replaced = false;

            while ((match = strstr(match, search))) {
                if (!wildcard || ((match == line || !isalnum(match[-1])) &&
                                  (!isalnum(match[search_len]) || match[search_len] == '\0'))) {
                    int before_len = match - temp;
                    fwrite(temp, 1, before_len, output);
                    fputs(replace, output);

                    match += search_len;
                    temp = match;
                    replaced = true;
                } else {
                    match++;
                }
            }

            if (replaced) {
                // Write the rest of the line
                fputs(temp, output);
            } else {
                // Copy the line as is
                fputs(line, output);
            }
        } else {
            // Copy lines outside the specified range unmodified
            fputs(line, output);
        }
    }
}
// Function to check if a character is a word character (alphanumeric or punctuation)
bool NotWordChar(char c) {
    return isspace(c)||ispunct(c);
}

// Function to find the end of a word given a starting position
char* findWordEnd(char* text) {
    while (*text != '\0' && !NotWordChar(*text)) {
        text++;
    }
    return text;
}

// Function to check if a word ends with a specified pattern
bool wordEndsWithPattern(const char *word, const char *pattern) {
    int wordLength = strlen(word);
    int patternLength = strlen(pattern);

    if (patternLength > wordLength) {
        // The pattern is longer than the word, so it cannot match.
        return false;
    }

    // Check if the word ends with the characters specified by the pattern
    return (strcmp(word + (wordLength - patternLength), pattern) == 0);
}

// Function to check if a word starts with a specified pattern
bool wordStartsWithPattern(const char *word, const char *pattern) {
    int wordLength = strlen(word);
    int patternLength = strlen(pattern);

    if (patternLength > wordLength) {
        // The pattern is longer than the word, so it cannot match.
        return false;
    }

    // Check if the word starts with the characters specified by the pattern
    return (strncmp(word, pattern, patternLength) == 0);
}

void replaceWildCardText(FILE *input, FILE *output, const char *search, const char *replace, int start_line, int end_line) {

    // Check if the wildcard is at the start
    bool isWildcardAtStart = (search[0] == '*');
    bool isWildcardAtEnd = (search[strlen(search) - 1] == '*');
    const char *startWildCard = search + 1;
    char endWildCard[MAX_SEARCH_LEN];

    if (strlen(search) > 0) {
        strncpy(endWildCard, search, strlen(search) - 1);
        endWildCard[strlen(search) - 1] = '\0';
    } else {
        endWildCard[0] = '\0'; // Handle the case where the original string is empty
    }

    char word[256]; // Assuming a maximum word length of 255 characters
    char c;
    int wordIndex = 0;
    bool isInsideWord = false; // Flag to track if we are inside a word
    int currentLine = 1;

    while ((c = fgetc(input)) != EOF) {
        if (isalnum(c) && !NotWordChar(c)) {
            word[wordIndex++] = c;
            isInsideWord = true;
        } else {
            if (isInsideWord) {
                word[wordIndex] = '\0'; // Null-terminate the word

                if (isWildcardAtStart) {
                    if (wordEndsWithPattern(word, startWildCard) && (start_line <= currentLine) && (end_line >= currentLine)) {
                        fprintf(output, "%s", replace); // Print the word
                    } else {
                        fprintf(output, "%s", word); // Print the word
                    }
                } else {
                    if (wordStartsWithPattern(word, endWildCard) && (start_line <= currentLine) && (end_line >= currentLine)) {
                        fprintf(output, "%s", replace); // Print the word
                    } else {
                        fprintf(output, "%s", word); // Print the word
                    }
                }
                wordIndex = 0; // Reset wordIndex for the next word
                isInsideWord = false;
            }
            fputc(c, output); // Print the non-word character
        }

        if (c == '\n') {
            currentLine++; // Increment currentLine after processing each line
        }
    }

    // Check if the last word is not followed by any non-word characters
    if (wordIndex > 0) {
        word[wordIndex] = '\0'; // Null-terminate the last word
        if (isWildcardAtStart) {
            if (wordEndsWithPattern(word, startWildCard) && (start_line <= currentLine) && (end_line >= currentLine)) {
                fprintf(output, "%s", replace); // Print the word
            } else {
                fprintf(output, "%s", word); // Print the word
            }
        } else {
            if (wordStartsWithPattern(word, endWildCard) && (start_line <= currentLine) && (end_line >= currentLine)) {
                fprintf(output, "%s", replace); // Print the word
            } else {
                fprintf(output, "%s", word); // Print the word
            }
        }
    }
}

int main(int argc, char *argv[]) {
    if (argc < 7) {
        printf("MISSING_ARGUMENT.\n");
        exit(MISSING_ARGUMENT);
    }

    char *input_file = NULL;
    char *output_file = NULL;
    char *search;
    char *replace = NULL;

    if (argc >= 2) {
        output_file = argv[argc - 1];
        input_file = argv[argc - 2];
    } else {
        printf("MISSING_ARGUMENT.\n");
        exit(MISSING_ARGUMENT);
    }

    extern char *optarg;
    extern int optind;
    int opt;
    int start_line = 0;
    int end_line = MAX_LINE; // Initialize end_line
    bool seenSearch = false;
    bool seenReplace = false;
    bool seenL = false;
    bool seenWildCard = false;
    bool s_option_found = false;
    bool r_option_found = false;
    bool l_option_invalid = false;
    bool w_option_invalid = false;

    while ((opt = getopt(argc, argv, "s:r:l:w")) != -1) {
        switch (opt) {
            case 's':
                if (seenSearch) {
                    printf("DUPLICATE_ARGUMENT.\n");
                    exit(DUPLICATE_ARGUMENT);
                }
                seenSearch = true;
                search = optarg;
                printf(search);
                if (search != NULL && *search != '-') {
                    s_option_found = true;
                }
                printf(search);
                break;
            case 'r':
                if (seenReplace) {
                    printf("DUPLICATE_ARGUMENT.\n");
                    exit(DUPLICATE_ARGUMENT);
                }
                seenReplace = true;
                replace = optarg;
                if (replace != NULL && *replace != '-') {
                    r_option_found = true;
                }
                break;
            case 'l':
                if (seenL) {
                    printf("DUPLICATE_ARGUMENT.\n");
                    exit(DUPLICATE_ARGUMENT);
                }
                seenL = true;
                if (optarg != NULL) {
                    char *range = optarg;
                    int start, end;
                    if (sscanf(range, "%d,%d", &start, &end) != 2 || start < 0 || end < 0 || start > end) {
                        l_option_invalid = true;
                    }
                    else {
                        start_line = start;
                        end_line = end;
                    }
                } else {
                    l_option_invalid = true;
                }
                break;
            case 'w':
                if (seenWildCard) {
                    printf("DUPLICATE_ARGUMENT.\n");
                    exit(DUPLICATE_ARGUMENT);
                }
                seenWildCard = true;

                break;
            default:
                break;
        }
    }

    FILE *input = fopen(input_file, "r");
    FILE *output = fopen(output_file, "w");

    if (input == NULL) {
        printf("INPUT_FILE_MISSING.\n");
        exit(INPUT_FILE_MISSING);
    }

    if (output == NULL) {
        printf("OUTPUT_FILE_UNWRITABLE.\n");
        exit(OUTPUT_FILE_UNWRITABLE);
    }

    if (!s_option_found) {
        printf("S_ARGUMENT_MISSING.\n");
        exit(S_ARGUMENT_MISSING);
    } else if (!r_option_found) {
        printf("R_ARGUMENT_MISSING.\n");
        exit(R_ARGUMENT_MISSING);
    } else if (l_option_invalid) {
        printf("L_ARGUMENT_INVALID.\n");
        exit(L_ARGUMENT_INVALID);
    } else if (seenWildCard) {
        if (!isValidWildcard(search)) {
            w_option_invalid = true;
        }
        if(w_option_invalid){
            printf("WILDCARD_INVALID.\n");
            exit(WILDCARD_INVALID);
        }
    }

    // Call the function to replace text in the input file and write to the output file
    if(!seenWildCard) {
        replaceText(input, output, search, replace, seenWildCard,start_line,end_line);
    }
    else {
        replaceWildCardText(input,output,search, replace,start_line, end_line);
    }

    fclose(input);
    fclose(output);

    return 0;
}