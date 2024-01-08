#include "../include/global.h"
#include "strPtr.c"

/**
 *  Feel free to use the functions that you made in strPtr.c
 */

int encrypt(const char *plaintext, char *ciphertext, int key) {
    // Check for NULL pointers
    if (ciphertext == NULL || plaintext == NULL) {
        return -2;
    }

    int encoded_chars = 0;
    int numAlphaNumericChars = 0;

    for (int i = 0; plaintext[i] != '\0'; i++) {
        char current_char = plaintext[i];

        if ((current_char >= 'A' && current_char <= 'Z')) {
            // Handle uppercase letters
            key = key % 26;
            ciphertext[i] = ((current_char - 'A' + key) % 26) + 'A';
            encoded_chars++;
            numAlphaNumericChars++;
        } else if (current_char >= 'a' && current_char <= 'z') {
            // Handle lowercase letters
            key = key % 26;
            ciphertext[i] = ((current_char - 'a' + key) % 26) + 'a';
            encoded_chars++;
            numAlphaNumericChars++;
        } else if (current_char >= '0' && current_char <= '9') {
            // Handle digits
            key = key % 10;
            ciphertext[i] = ((current_char - '0' + key) % 10) + '0';
            encoded_chars++;
            numAlphaNumericChars++;
        } else {
            // Non-alphanumeric characters remain unchanged
            ciphertext[i] = current_char;
        }
    }
    if (numAlphaNumericChars == 0) {
        const char *newString = "undefined__EOM__";
        int newStringLength = 16;  // Length of newString

        // Copy the contents of the new string into the allocated memory
        for (int i = 0; i < newStringLength; i++) {
            ciphertext[i] = newString[i];
        }
        ciphertext[newStringLength] = '\0';  // Null-terminate the string

        return 0;
    }

    // Add the EOM marker if there's enough space
    int ciphertext_length = strgLen((char*)plaintext);
    for (int i = 0; i < 7; i++) {
        if (ciphertext_length < 100 - 1) {  // Assuming a maximum capacity of 100 for ciphertext
            ciphertext[ciphertext_length] = "__EOM__"[i];
            ciphertext_length++;
        } else {
            return -1; // Insufficient memory for the EOM marker
        }
    }

    // Null-terminate the ciphertext
    ciphertext[ciphertext_length] = '\0';

    return encoded_chars;
}

int decrypt(const char *ciphertext, char *plaintext, int key) {
    // Check for NULL pointers
    if (plaintext == NULL || ciphertext == NULL) {
        return -2;
    }

    // Check if ciphertext is "empty__EOM__"
    if (ciphertext[0] == 'e' && ciphertext[1] == 'm' && ciphertext[2] == 'p' &&
        ciphertext[3] == 't' && ciphertext[4] == 'y' && ciphertext[5] == '_' &&
        ciphertext[6] == '_' && ciphertext[7] == 'E' && ciphertext[8] == 'O' &&
        ciphertext[9] == 'M' && ciphertext[10] == '_' && ciphertext[11] == '_') {
        // Special case: plaintext becomes "undefined"
        const char *newString = "undefined";
        int newStringLength = 9; // Length of "undefined"

        // Copy the contents of the new string into the allocated memory
        for (int i = 0; i < newStringLength; i++) {
            plaintext[i] = newString[i];
        }
        plaintext[newStringLength] = '\0'; // Null-terminate the string
        return 0;
    }

    int decrypted_chars = 0;
    int eom_index = -1; // Index of the EOM marker in ciphertext

    // Find the length of the ciphertext manually
    int ciphertext_length = 0;
    while (ciphertext[ciphertext_length] != '\0') {
        ciphertext_length++;
    }

    // Find the length of the plaintext manually
    int plaintext_length = 0;
    while (plaintext[plaintext_length] != '\0') {
        plaintext_length++;
    }

    // Find the EOM marker in ciphertext
    for (int i = 0; i <= ciphertext_length - 7; i++) {
        int is_eom = 1;
        for (int j = 0; j < 7; j++) {
            if (ciphertext[i + j] != "__EOM__"[j]) {
                is_eom = 0;
                break;
            }
        }
        if (is_eom) {
            eom_index = i;
            break;
        }
    }

    // If no EOM marker is found, return -1
    if (eom_index == -1) {
        return -1;
    }

    int countAlphaNumericChars = 0;
    // Decrypt characters up to the EOM marker or the length of plaintext, whichever is shorter
    for (int i = 0; i < eom_index; i++) {
        char current_char = ciphertext[i];

        if ((current_char >= 'A' && current_char <= 'Z') && plaintext_length > 0) {
            // Handle uppercase letters
            key = key % 26;
            plaintext[decrypted_chars] = ((current_char - 'A' - key + 26) % 26) + 'A';
            decrypted_chars++;
            countAlphaNumericChars++;
            plaintext_length--;
        } else if (current_char >= 'a' && current_char <= 'z'&& plaintext_length > 0) {
            // Handle lowercase letters
            key = key % 26;
            plaintext[decrypted_chars] = ((current_char - 'a' - key + 26) % 26) + 'a';
            decrypted_chars++;
            countAlphaNumericChars++;
            plaintext_length--;
        } else if (current_char >= '0' && current_char <= '9'&& plaintext_length > 0) {
            // Handle digits
            key = key % 10;
            plaintext[decrypted_chars] = ((current_char - '0' - key + 10) % 10) + '0';
            decrypted_chars++;
            countAlphaNumericChars++;
            plaintext_length--;
        } else if (plaintext_length > 0){
            // Non-alphanumeric characters remain unchanged
            plaintext[decrypted_chars] = current_char;
            decrypted_chars++;
            plaintext_length--;
        }
    }

    // Null-terminate the plaintext string
    plaintext[decrypted_chars] = '\0';

    if (countAlphaNumericChars == 0) {
        // Special case: plaintext becomes "undefined"
        const char *newString = "undefined";
        int newStringLength = 9; // Length of "undefined"

        // Copy the contents of the new string into the allocated memory
        for (int i = 0; i < newStringLength; i++) {
            plaintext[i] = newString[i];
        }
        plaintext[newStringLength] = '\0'; // Null-terminate the string
        return 0; // No characters decrypted
    }

    return countAlphaNumericChars;
}

int main(){
    // encrypt succeeded when one of the input is NULL, it correctly outputs -2
    char a2[] = "________________________";
    int result2 = encrypt("world", NULL, 5);
    printf("Result: %d\n\n", result2);//-2 as expected

    // decrypt succeeded when shifting with key = 26, leaving the letter unchanged
    char b3[] = "__________";
    int result3 = decrypt("rjmgi__EOM__", b3, 26);
    printf("Plaintext: %s\n", b3);//"rjmgi"
    printf("Result: %d\n\n", result3);
}