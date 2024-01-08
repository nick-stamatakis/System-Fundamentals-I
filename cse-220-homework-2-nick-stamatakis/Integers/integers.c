#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// FILL IN THE BODY OF THIS FUNCTION.
// Feel free to create any other functions you like; just include them in this file.

#define SIGN_MAG_MIN (-2147483647)  // -2^(N-1) + 1
#define SIGN_MAG_MAX (2147483647)   // 2^(N-1) - 1

void repr_convert(char source_repr, char target_repr, unsigned int repr) {
    //Check if source_rep and target_rep are valid, to ensure conversion is possible with the code below
    if ((source_repr != '2' && source_repr != 'S') || (target_repr != '2' && target_repr != 'S')) {
        printf("error\n");
        return;
    }
    //initialize value
    int value = repr;

    // Check if the value can be represented in the target representation
    if (target_repr == 'S') {
        if (value < SIGN_MAG_MIN || value > SIGN_MAG_MAX || repr == 0x80000000) {
            printf("undefined\n");
            return;
        }
    }

    //If same representations
    if (source_repr == target_repr || repr >> 31 == 0) {
        value = (int) repr;
    }

    //Conversions from 2s -> sign-mag and vice versa
    else if (source_repr == '2') {
        // Convert from two's complement to sign/magnitude
        if ((repr & 0x80000000) != 0) {
            // Negative value
            value = -((int)(repr & 0x7FFFFFFF));
        }
    }

    else {
        // Convert from sign/magnitude to two's complement
        if ((repr & 0x80000000) != 0) {
            // Negative value
            value = -((int)(repr & 0x7FFFFFFF));
        }
    }

    // Print the value in the target representation as an eight-digit hexadecimal value
    printf("%08x\n", (unsigned int)value);
}

//DO NOT CHANGE ANY CODE BELOW THIS LINE
int main(int argc, char *argv[]) {
    (void)argc; // Suppress compiler warning
    (void)argv;
    repr_convert(argv[1][0], argv[2][0], (int)strtol(argv[3], NULL, 16));
    return 0;
}
