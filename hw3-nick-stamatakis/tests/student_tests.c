#include "unit_tests.h"

TestSuite(student_suite, .timeout=TEST_TIMEOUT);

/*
Test(student_suite, name_of_test, .description="description of test") {
    // Steps of unit test go here
}
*/
//int main(){
//
//    return 0;
//}
////Given strgLen(char *s) test cases
//printf("%d\n",strgLen("Stony Brook"));//11
//printf("%d\n",strgLen("CSE 220"));//7
//printf("%d\n",strgLen("C"));//1
//printf("%d\n",strgLen("System Fundamental"));//18
//printf("%d\n",strgLen("1"));//1
//printf("%d\n",strgLen(""));//0
//printf("%d\n",strgLen(NULL));//-1
//
////Given strgCopy(char *s, char *d) test cases
//char testCases[][20] = {
//        "Computer Science",
//        "CSE-220",
//        "System Fundamental",
//        "1",
//        "",
//        NULL,
//        "Computer Science"
//};
//char destination[20]; // Create a destination buffer
//char destination[] = "Compster Scienc"; // Create a destination buffer
//
//for (int i = 0; i < sizeof(testCases) / sizeof(testCases[0]); i++) {
//char *source = testCases[i]; // Use a pointer to the test case as source
//
//// Call the strgCopy function to copy the content of source to destination
//strgCopy(source, destination);
//
//printf("Content of s: \"%s\"\n", testCases[i]);
//printf("Content of d (after calling the function): \"%s\"\n\n", destination);
//}
////Additional test case
//char source2[] = "Computer Science";
//char destination2[5]; // Create a destination buffer with space for 5 bytes
//
//// Call the strgCopy function with the destination size
//strgCopy(source2, destination2);
//
//printf("Content of s: \"%s\"\n", source2);
//printf("Content of d (after calling the function): \"%s\"\n", destination2);
//
////strgChangeCase(char *s) test cases
//char test1[] = "Stony Brook";
//strgChangeCase(test1);
//printf("Before: Stony Brook\tAfter: %s\n", test1);
//
//char test2[] = "CSE220";
//strgChangeCase(test2);
//printf("Before: CSE220\tAfter: %s\n", test2);
//
//char test3[] = "C";
//strgChangeCase(test3);
//printf("Before: C\tAfter: %s\n", test3);
//
//char test4[] = "System Fundamental";
//strgChangeCase(test4);
//printf("Before: System Fundamental\tAfter: %s\n", test4);
//
//char test5[] = "1";
//strgChangeCase(test5);
//printf("Before: 1\tAfter: %s\n", test5);
//
//char test6[] = "";
//strgChangeCase(test6);
//printf("Before: (empty)\tAfter: %s\n", test6);
//
//char *test7 = NULL;
//strgChangeCase(test7);
//printf("Before: (NULL)\tAfter: (NULL)\n");
//
////Test cases for strgDiff
//const char* s1;
//const char* s2;
//int diffIndex;
//
//s1 = "Hello";
//s2 = "Hello";
//diffIndex = strgDiff((char*)s1, (char*)s2);
//printf("\"%s\" \"%s\" %d\n", s1, s2, diffIndex);
//
//s1 = "CSE-220";
//s2 = "CSE220";
//diffIndex = strgDiff((char*)s1, (char*)s2);
//printf("\"%s\" \"%s\" %d\n", s1, s2, diffIndex);
//
//s1 = "CSE220";
//s2 = "SE220";
//diffIndex = strgDiff((char*)s1, (char*)s2);
//printf("\"%s\" \"%s\" %d\n", s1, s2, diffIndex);
//
//s1 = "";
//s2 = "";
//diffIndex = strgDiff((char*)s1, (char*)s2);
//printf("\"%s\" \"%s\" %d\n", s1, s2, diffIndex);
//
//// Test Case 6: Strings differ at the beginning
//s1 = "Hello";
//s2 = "Hi there";
//diffIndex = strgDiff(s1, s2);
//printf("\"%s\" \"%s\" %d\n", s1, s2, diffIndex); // Expected: "Hello" "Hi there" 1
//
//// Test Case 7: Strings differ in the middle
//s1 = "CSE220";
//s2 = "CSE120";
//diffIndex = strgDiff(s1, s2);
//printf("\"%s\" \"%s\" %d\n", s1, s2, diffIndex); // Expected: "CSE220" "CSE120" 3
//
//// Test Case 8: Strings differ at the end
//s1 = "Programming";
//s2 = "Programmin";
//diffIndex = strgDiff(s1, s2);
//printf("\"%s\" \"%s\" %d\n", s1, s2, diffIndex); // Expected: "Programming" "Programmin" 10
//
////test cases for strgInterLeave(s1,s2,d)
//char a[5];  // Ensure d has enough space (1 extra for null-terminator)
//a[4] = '\0';
//strgInterleave("abc", "123", a);
//printf("Result: %s\n", a);  // Expected: "a1b2c3"
//
//strgInterleave("abcdef", "123", a);
//printf("Result: %s\n", a);  // Expected: "a1b2c3"
//
//strgInterleave("cse", "12345", a);
//printf("Result: %s\n", a);  // Expected: "c1s2e345"
//
//strgInterleave("1234", "cs", a);
//printf("Result: %s\n", a);  // Expected: "1c2s34"
//
//strgInterleave("", "", a);
//printf("Result: %s\n", a);  // Expected: ""
//
//strgInterleave("", "123", a);
//printf("Result: %s\n", a);  // Expected: "123"
//
//strgInterleave("abc", "123", a);
//printf("Result: %s\n", a);  // Expected: "a1b2"


////Test cases for encrypting strings
//char ciphertext[100];
//const char *plaintext;
//int key;
//int expected_encoded_chars;
//
//// Example 1
//plaintext = "abc";
//key = 2;
//expected_encoded_chars = 3;
//int result = encrypt(plaintext, ciphertext, key);
//printf("Plaintext: \"%s\", Key: %d\n", plaintext, key);
//printf("Ciphertext after function call: \"%s\"\n", ciphertext);
//printf("Return value: %d (Expected: %d)\n\n", result, expected_encoded_chars);
//
//// Example 2
//plaintext = "Ayb";
//key = 3;
//expected_encoded_chars = 3;
//result = encrypt(plaintext, ciphertext, key);
//printf("Plaintext: \"%s\", Key: %d\n", plaintext, key);
//printf("Ciphertext after function call: \"%s\"\n", ciphertext);
//printf("Return value: %d (Expected: %d)\n\n", result, expected_encoded_chars);
//
//// Example 3
//plaintext = "Cse220";
//key = 1;
//expected_encoded_chars = 6;
//result = encrypt(plaintext, ciphertext, key);
//printf("Plaintext: \"%s\", Key: %d\n", plaintext, key);
//printf("Ciphertext after function call: \"%s\"\n", ciphertext);
//printf("Return value: %d (Expected: %d)\n\n", result, expected_encoded_chars);
//
//// Example 4
//plaintext = "CS";
//key = 0;
//expected_encoded_chars = 2;
//result = encrypt(plaintext, ciphertext, key);
//printf("Plaintext: \"%s\", Key: %d\n", plaintext, key);
//printf("Ciphertext after function call: \"%s\"\n", ciphertext);
//printf("Return value: %d (Expected: %d)\n\n", result, expected_encoded_chars);
//
//// Example 5
//plaintext = "";
//key = -5;
//expected_encoded_chars = 0;
//result = encrypt(plaintext, ciphertext, key);
//printf("Plaintext: \"%s\", Key: %d\n", plaintext, key);
//printf("Ciphertext after function call: \"%s\"\n", ciphertext);
//printf("Return value: %d (Expected: %d)\n\n", result, expected_encoded_chars);
//
////Decryption test cases
////Test Cases for decrypt
////Test Cases for decrypt
//// Test Case 1
//char ciphertext1[] = "cde__EOM__";
//char plaintext1[12];
//int result1 = decrypt(ciphertext1, plaintext1, 2);
//printf("Test Case 1:\n");
//printf("Decrypted message: %s\n", plaintext1);
//printf("Result: %d\n\n", result1);
//
//// Test Case 2
//char ciphertext2[] = "Dbe__EOM__";
//char plaintext2[12];
//int result2 = decrypt(ciphertext2, plaintext2, 3);
//printf("Test Case 2:\n");
//printf("Decrypted message: %s\n", plaintext2);
//printf("Result: %d\n\n", result2);
//
//// Test Case 3
//char ciphertext3[] = "Dtf331__EOM__";
//char plaintext3[12];
//int result3 = decrypt(ciphertext3, plaintext3, 1);
//printf("Test Case 3:\n");
//printf("Decrypted message: %s\n", plaintext3);
//printf("Result: %d\n\n", result3);
//
//// Test Case 4
//char ciphertext4[] = "CS__EOM__";
//char plaintext4[12];
//int result4 = decrypt(ciphertext4, plaintext4, 0);
//printf("Test Case 4:\n");
//printf("Decrypted message: %s\n", plaintext4);
//printf("Result: %d\n\n", result4);
//
//// Test Case 5
//char ciphertext5[] = "empty__EOM__";
//char plaintext5[12];
//int result5 = decrypt(ciphertext5, plaintext5, 5);
//printf("Test Case 5:\n");
//printf("Decrypted message: %s\n", plaintext5);
//printf("Result: %d\n\n", result5);