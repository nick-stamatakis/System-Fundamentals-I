.data
A:      .asciiz "A["
B:      .asciiz "B["
C:      .asciiz "]="
spacechar:      .asciiz " "
bar:            .asciiz "|"

.align 2
pinA:   .space  400
pinB:   .space  400
num:    .word   10   # Number of elements
# n x 4 <= 400 This is the constraint

.text
main:
    la $a1, pinA     # Load base address of array A
    la $a2, pinB     # Load base address of array B
    lw $t0, num      # Load the number of elements from num

    li $t1, 1         # Initialize index to 1

init_loop:
    bgt $t1, $t0, end_init   # If index > num, exit loop

    # Print A[index] prompt
    li $v0, 4
    la $a0, A
    syscall
    li $v0, 1
    add $a0, $t1, $0    # Display index as user input (start from 1)
    syscall
    li $v0, 4
    la $a0, C
    syscall

    # Read user input for A[index]
    li $v0, 5
    syscall
    sw $v0, 0($a1)           # Store user input in array A

    # Print B[index] prompt
    li $v0, 4
    la $a0, B
    syscall
    li $v0, 1
    add $a0, $t1, $0    # Display index as user input (start from 1)
    syscall
    li $v0, 4
    la $a0, C
    syscall

    # Read user input for B[index]
    li $v0, 5
    syscall
    sw $v0, 0($a2)           # Store user input in array B

    addi $t1, $t1, 1          # Increment index
    addi $a1, $a1, 4          # Move to the next element in A array
    addi $a2, $a2, 4          # Move to the next element in B array
    j init_loop               # Repeat the loop

end_init:
    # Swap values in arrays A and B
    la $a1, pinA     # Load base address of array A
    la $a2, pinB     # Load base address of array B
    li $t1, 1        # Initialize index to 1

swap_loop:
    bgt $t1, $t0, print_swapped_arrays   # If index > num, exit loop

    # Swap A[index] and B[index]
    lw $t2, 0($a1)  # Load A[index] value
    lw $t3, 0($a2)  # Load B[index] value
    sw $t3, 0($a1)  # Store B[index] value in A[index]
    sw $t2, 0($a2)  # Store A[index] value in B[index]

    addi $t1, $t1, 1  # Increment index
    addi $a1, $a1, 4  # Move to the next element in A array
    addi $a2, $a2, 4  # Move to the next element in B array
    j swap_loop       # Repeat the loop

print_swapped_arrays:
    # Print alternating values in arrays A and B with a bar after every 2 numbers
    la $a1, pinA     # Load base address of array A
    la $a2, pinB     # Load base address of array B
    li $t1, 1        # Initialize index to 1
    li $t4, 0        # Initialize counter for bars

print_alternating_loop:
    bgt $t1, $t0, exit_program   # If index > num, exit program

    # Print A[index] value
    lw $a0, 0($a1)
    li $v0, 1
    syscall

    # Print space character
    li $v0, 4
    la $a0, spacechar
    syscall

    # Print B[index] value
    lw $a0, 0($a2)
    li $v0, 1
    syscall

    # Increment bar counter
    addi $t4, $t4, 1

    # Print space character and bar after every 2 numbers
    beqz $t4, no_bar
    li $v0, 4
    la $a0, bar
    syscall
    li $t4, 0   # Reset bar counter

no_bar:
    # Increment index and move to the next element in arrays A and B
    addi $t1, $t1, 1
    addi $a1, $a1, 4
    addi $a2, $a2, 4

    j print_alternating_loop  # Repeat the loop

exit_program:
    # Exit program
    li $v0, 10
    syscall
