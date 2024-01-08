#include "../include/global.h"

int strgLen(char *s){
    // Check if the input pointer matches a predefined "NULL" pointer value
    if (s == NULL) {
        return -1; // Return -1 for "NULL" pointer
    }
    // length initialized to be 0
    int length = 0;

    while(*s != '\0'){//marks the end of the string
        length++;//Increment length for each char
        s++; //Move char pointer to the next character
    }
    return length;// After while loop is exited the length of the string has been obtained.
}

void strgCopy(char *s,char *d ){
    // Check if the input pointers match a predefined "NULL" pointer value
    if (s == NULL || d == NULL) {
        return; // Return nothing for "NULL" pointer
    }
    int destSize = strgLen(d);// Find the size of the destination buffer

    //Loop until we reach '\0' in the source string
    while(*s != '\0' && destSize > 0 ){
        *d = *s; //copy value from s to d
        s++;
        d++;//increment both s and d so we get to the next char
        destSize--; // Decrement the remaining space in the destination buffer
    }
    //Add the null terminator to the destination string -- it's not automatically there
    *d = '\0';
}

void strgChangeCase(char *s){
    if (s == NULL) {// Do nothing and return if the input string is NULL
        return;
    }
    while(*s != '\0') {//not at end of string
        if(*s >= 'a' && *s <= 'z') {//in correct range of lowercase letters
            *s = *s - ('a'-'A');//Subtract
        }
        else if(*s >= 'A' && *s <= 'Z') {//in correct range of uppercase letters
            *s = *s + ('a'-'A');
        }
        s++;//Move pointer to next char
    }
}

int strgDiff(char *s1,char *s2 ){
    // Check for NULL or empty strings
    if (s1 == NULL || s2 == NULL || s1[0] == '\0' || s2[0] == '\0') {
        return -2;
    }
    //check index where strings differ
    int index = 0;
    while (s1[index] != '\0' && s2[index] != '\0') {
        if (s1[index] != s2[index]) {
            return index;
        }
        index++;
    }

    //return based on if strings are the same or different
    if (s1[index] == '\0' && s2[index] == '\0') {
        return -1; // Strings are equal
    } else {
        return index; // Strings differ at this index
    }
}

void strgInterleave(char *s1, char *s2, char *d) {
    if (s1 == NULL || s2 == NULL || d == NULL) {//make sure string are not null, return if they are
        return;
    }

    int length = strgLen(d);//calculate length

    //add strings when both s1 and s2 are non-empty
    while (*s1 != '\0' && *s2 != '\0' && length > 0) {
        *d++ = *s1++;
        length = length - 1;
        if (length > 0) {
            *d++ = *s2++;
            length = length - 1;
        }
    }

    //add the rest of s1 if there's more
    while (*s1 != '\0'&& length > 0) {
        *d++ = *s1++;
        length = length - 1;
    }

    //add the rest of s2 if there's more
    while (*s2 != '\0'&& length > 0) {
        *d++ = *s2++;
        length = length - 1;
    }
    *d = '\0';
}

//int main() {
//    //strInterleave and strCopy SUCCEED when size of char array is smaller than inputs
//    //The outputs of the print statements are in comments below
//    char cs[] = "Computer Science";
//    char cs2[] = "aaaaaa";
//    strgCopy(cs, cs2);
//    printf("%s\n", cs);//"Computer Science"
//    printf("%s\n", cs2);//"Comput"
//
//    char d2[] = "aaa";
//    strgInterleave("abcdef", "123", d2);
//    printf("%s\n", d2);//"a1b"
//}
