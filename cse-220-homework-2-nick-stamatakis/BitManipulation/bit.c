#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/*
 * Gets A bit in num at position pos
 * num >> pos shifts the bit at the desired position to the least significant bit (LSB),
 * effectively isolating the bit you want to check.
 * & 1 performs a bitwise AND with 1 to extract the least significant bit,
 * e.g. if you find a 0 you do 0 & 1 = 0, if you do it's 1 & 1 = 1
 */
int GetBit(int num, int pos){
    return (num >> pos) & 1;
}
/*
 * Set a bit in num at position pos, 1->1, 0->1
 */
int SetBit(int num, int pos){
    // Check if the pos-th bit is already set
    if ((num & (1 << pos)) == 0) {
        // If it's not set, set it to 1
        num |= (1 << pos);
    }
    // Return the new integer value
    return num;
}

/*
 * Should clear bit at num, 0->0, 1 ->0
 */
int ClearBit(int num, int pos){
    // Create a mask with only the bit at the specified position set to 0
    int mask = ~(1 << pos);

    // Use bitwise AND to clear the bit at the specified position
    int result = num & mask;

    return result;
}

/*
 * Reverse a bits of a 32 bit number
 * i.e. 1000000..0 -> 00000000...1
 */
int Reversbit(int num){
    int reversedNum = 0;
    int numOfBits = sizeof(num) * 8; // Calculate the number of bits in an integer

    for (int i = 0; i < numOfBits; i++) {
        reversedNum <<= 1; // Shift the reversed number left by 1 bit
        reversedNum |= (num & 1); // Set the least significant bit of reversedNum to the current bit of num
        num >>= 1; // Shift num right by 1 bit to process the next bit
    }

    return reversedNum;
}
/*
 * Counts the number of 1s
 * e.g. 0010 -> 1 one
 */
int CountBit(int num){
    int count = 0;

    while (num > 0) {
        count += num & 1;  // Check the least significant bit
        num >>= 1;        // Right shift num by 1 bit
    }

    return count;
}
/*
 * Checks if num is an exact power of 2 i.e. n within {2^0, 2^1, ..., 2^n}
 * 1000-> 8 (which is a power of 2) should return 1
 */
int PowerofTwo(unsigned int num){
    // Check if num is 0 or has more than one bit set to 1
    if (num == 0 || (num & (num - 1)) != 0) {
        return 0; // Not a power of two
    } else {
        return 1; // It's a power of two
    }
}

/*
 * Rotates Bits to the left
 */
int RotateLeft(int num, unsigned int pos) {
    int num_bits = sizeof(num) * 8; // Calculate the number of bits in 'num'

    // Ensure 'pos' is within the range [0, num_bits)
    pos = pos % num_bits;

    // Perform the left rotation
    return (num << pos) | (num >> (num_bits - pos));
}
/*
 * Rotates bits to the right
 */
int RotateRight(int num, unsigned int pos){
    // Calculate the number of bits in an integer
    int num_bits = sizeof(int) * 8;

    // Ensure pos is within the valid range [0, num_bits - 1]
    pos %= num_bits;

    // Right-rotate the number by pos positions and combine with left-rotated part
    return (num >> pos) | (num << (num_bits - pos));
}

int main(int argc, char* argv[]){
	(void)argc;
	(void)argv;
    if(atoi(argv[1])){ // to convert from ASCII, * means to dereference
        printf("%d\n", GetBit(atoi(argv[2]), atoi(argv[3])));
    }
    else if(atoi(argv[1]) - 48 == 2){ // to convert from ASCII
        printf("%d\n", SetBit(atoi(argv[2]), atoi(argv[3])));
    }
    else if((atoi(argv[1])) == 3){ // to convert from ASCII
        printf("%d\n", ClearBit(atoi(argv[2]), atoi(argv[3])));
    }
    else if(atoi(argv[1]) == 4){ // to convert from ASCII
        printf("%d\n", Reversbit(atoi(argv[2])));
    }
    else if(atoi(argv[1]) == 5){ // to convert from ASCII
        printf("%d\n", CountBit(atoi(argv[2])));
    }
    else if((*argv[1]) - 48 == 6){ // to convert from ASCII
        printf("%d\n", PowerofTwo(atoi(argv[2])));
    }

    return 0;
}
def getMaximumProfit(price, profit):
    n = len(price)

    if n < 3:
        return -1

    max_profit = [0] * n  # Initialize an array to store maximum profit for each day

    for j in range(1, n):
        for i in range(j):
            if price[i] < price[j]:
                max_profit[j] = max(max_profit[j], max_profit[i] + profit[j])

    # Find the maximum profit among all days
    result = max(max_profit)

    return result if result > 0 else -1


