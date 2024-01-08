.data
  M:      .space 400      # int M[][] The matrix
  V:      .space 400      # int V[]   The vector
  C:      .space 400      # int C[] : The output vector
  m:      .word 10         # m is an int whose value is at most 10
                           # max value for rows and columns
  MAX_MEMORY: .word 400   # Maximum allowed memory
  col_m: .word 2          # columns for matrix M: This should not be more than 10
  row_m: .word 2          # rows for matrix M:    This should not be more than 10
                           # (col_m * row_m) * 4 <= M
  col_v: .word 1           # columns for vector V. For a vector, the column is always one
  row_v: .word 2          # rows for vector V. This should not be more than 10
                           # (col_v * row_v) * 4 <= V

  msg_matrix:    .asciiz "Enter values for matrix M:\n"
  msg_vector:    .asciiz "Enter values for vector V:\n"
  msg_input:     .asciiz "Enter a value: "
  msg_print_vector_c: .asciiz "Vector C:\n"
  msg_dimension_error: .asciiz "NOT WORKABLE BECAUSE OF THE DIMENSIONS\n"
  msg_memory_error: .asciiz "NOT WORKABLE BECAUSE OF THE MEMORY\n"

.text
main:
  # Load the values of col_m, row_m, col_v, and row_v
  lw $t2, col_m            # Load the number of columns for matrix M
  lw $t7, row_v            # Load the number of rows for vector V

  # Check if col_m is equal to row_v
  beq $t2, $t7, check_memory
    # Print an error message
    li $v0, 4                # System call code 4 for print_str
    la $a0, msg_dimension_error # Load the address of the error message
    syscall                  # Print the error message

    # Terminate the program
    li $v0, 10              # System call code 10 for exit
    syscall                 # Exit the program

check_memory:
  # Load values for row_m, col_m, row_v, and col_v
  lw $t1, row_m            # Load the number of rows for matrix M
  lw $t2, col_m            # Load the number of columns for matrix M
  lw $t3, row_v            # Load the number of rows for vector V
  lw $t4, col_v            # Load the number of columns for vector V

  # Calculate memory sizes for matrix M and vector V
  mul $t5, $t1, $t2        # row_m * col_m
  mul $t6, $t3, $t4        # row_v * col_v

  # Load constant "4" into register $t9
  li $t9, 4

  # Load the value of MAX_MEMORY into register $t7
  lw $t7, MAX_MEMORY

  # Check if (row_m * col_m * 4) is strictly greater than max memory
  mul $t8, $t5, $t9         # (row_m * col_m) * 4
  bgt $t8, $t7, memory_error_row_m_col_m

  # Check if (row_v * col_v * 4) is strictly greater than max memory
  mul $t8, $t6, $t9         # (row_v * col_v) * 4
  bgt $t8, $t7, memory_error_row_v_col_v

  # If dimensions and memory are valid, continue with the program
  j valid_dimensions

memory_error_row_m_col_m:
  # Print an error message for (row_m * col_m * 4)
  li $v0, 4                # System call code 4 for print_str
  la $a0, msg_memory_error  # Load the address of the error message
  syscall                  # Print the error message
  j exit                   # Terminate the program

memory_error_row_v_col_v:
  # Print an error message for (row_v * col_v * 4)
  li $v0, 4                # System call code 4 for print_str
  la $a0, msg_memory_error  # Load the address of the error message
  syscall                  # Print the error message
  j exit                   # Terminate the program
  
valid_dimensions:
  # Load the base address of matrix M and other parameters
  la $t0, M                # Load the base address of matrix M
  lw $t1, row_m            # Load the number of rows for matrix M
  lw $t2, col_m            # Load the number of columns for matrix M

  # Print a message to prompt the user to enter values for matrix M
  li $v0, 4                # System call code 4 for print_str
  la $a0, msg_matrix       # Load the address of the message for matrix input
  syscall                  # Print the message

  # Read values for matrix M
  jal read_matrix

  # Load the base address of vector V and other parameters
  la $t0, V                # Load the base address of vector V
  lw $t1, row_v            # Load the number of rows for vector V

  # Print a message to prompt the user to enter values for vector V
  li $v0, 4                # System call code 4 for print_str
  la $a0, msg_vector       # Load the address of the message for vector input
  syscall                  # Print the message

  # Read values for vector V
  jal read_vector

  # Load the base address of matrix C and other parameters
  la $t5, C                # Load the base address of matrix C
  lw $t6, row_m            # Load the number of rows for matrix M
  lw $t7, col_v            # Load the number of columns for vector V

  # Matrix multiplication: C = M * V
  li $t8, 0                # i, row counter for matrix C
  MVM:
    # Check if we have processed all rows of matrix M
    bge $t8, $t6, MVM_done

    # Load the base address of matrix M and vector V
    la $t9, M                # Load the base address of matrix M
    la $s0, V                # Load the base address of vector V
    la $s1, C                # Load the base address of matrix C

    # Initialize the sum for the current row to 0
    li $s2, 0

    # Process each element in the row
    li $t4, 0                # j, column counter
    MVM_col_loop:
      # Calculate the address for M[i][j]
      mul $s3, $t8, $t2      # i * num_columns
      add $s3, $s3, $t4      # i * num_columns + j
      sll $s3, $s3, 2        # 4 * (i * num_columns + j)
      add $s3, $s3, $t9      # base_addr + 4 * (i * num_columns + j)

      # Load M[i][j] into $s4
      lw $s4, 0($s3)

      # Calculate the address for V[j]
      sll $s3, $t4, 2        # 4 * j
      add $s3, $s3, $s0      # base_addr + 4 * j

      # Load V[j] into $s5
      lw $s5, 0($s3)

      # Multiply M[i][j] by V[j] and add to the sum
      mul $s4, $s4, $s5
      add $s2, $s2, $s4

      # Move to the next column
      addi $t4, $t4, 1
      blt $t4, $t2, MVM_col_loop

    # Store the sum in C[i]
    sll $s3, $t8, 2          # 4 * i
    add $s3, $s3, $s1        # base_addr + 4 * i
    sw $s2, 0($s3)

    # Move to the next row
    addi $t8, $t8, 1
    j MVM

  MVM_done:

  # Print values for vector C
  li $v0, 4                # System call code 4 for print_str
  la $a0, msg_print_vector_c  # Load the address of the message for printing vector C
  syscall                  # Print the message

  li $t8, 0                # i, row counter
  print_vector_loop:
    li $t9, 0               # j, column counter
    print_vector_col_loop:
      # Calculate the address for C[i][j]
      mul $s0, $t8, $t7     # i * num_columns
      add $s0, $s0, $t9     # i * num_columns + j
      sll $s0, $s0, 2       # 4 * (i * num_columns + j)
      add $s0, $s0, $t5     # base_addr + 4 * (i * num_columns + j)

      lw $s1, 0($s0)        # Load the value from C[i][j]

      # Print the value
      li $v0, 1             # System call code 1 for print_int
      move $a0, $s1         # Load the value to be printed
      syscall               # Print the value

      # Print a space between values
      li $v0, 11            # System call code 11 for print_char
      li $a0, ' '           # Load the ASCII code for space character
      syscall               # Print the space

      addi $t9, $t9, 1      # j++
      blt $t9, $t7, print_vector_col_loop

    # Print a newline after each row
    li $v0, 11             # System call code 11 for print_char
    li $a0, '\n'           # Load the ASCII code for newline character
    syscall                # Print the newline

    addi $t8, $t8, 1       # i++
    blt $t8, $t6, print_vector_loop

exit:
  # Terminate the program
  li $v0, 10              # System call code 10 for exit
  syscall                 # Exit the program

read_matrix:
  # Function to read values for matrix M
  # Parameters: $t0 = base address of matrix M, $t1 = number of rows, $t2 = number of columns

  li $t3, 0                # i, row counter
matrix_input_loop:
  li $t4, 0                # j, column counter
matrix_col_input_loop:
  # Calculate the address for M[i][j]
  mul $t5, $t3, $t2        # i * num_columns
  add $t5, $t5, $t4        # i * num_columns + j
  sll $t5, $t5, 2          # 4 * (i * num_columns + j)
  add $t5, $t5, $t0         # base_addr + 4 * (i * num_columns + j)

  # Prompt the user to enter a value for matrix M[i][j]
  li $v0, 4                # System call code 4 for print_str
  la $a0, msg_input        # Load the address of the message for input
  syscall                  # Print the message

  li $v0, 5                # System call code 5 for read_int
  syscall                  # Read integer from the user
  sw $v0, 0($t5)           # Store the input value at the calculated address

  addi $t4, $t4, 1         # j++
  blt $t4, $t2, matrix_col_input_loop
matrix_col_input_done:

  addi $t3, $t3, 1         # i++
  blt $t3, $t1, matrix_input_loop

  jr $ra                   # Return from the function

read_vector:
  # Function to read values for vector V
  # Parameters: $t0 = base address of vector V, $t1 = number of rows

  li $t3, 0                # i, row counter
vector_input_loop:
  # Calculate the address for V[i]
  sll $t5, $t3, 2          # 4 * i
  add $t5, $t5, $t0         # base_addr + 4 * i

  # Prompt the user to enter a value for vector V[i]
  li $v0, 4                # System call code 4 for print_str
  la $a0, msg_input        # Load the address of the message for input
  syscall                  # Print the message

  li $v0, 5                # System call code 5 for read_int
  syscall                  # Read integer from the user
  sw $v0, 0($t5)           # Store the input value at the calculated address

  addi $t3, $t3, 1         # i++
  blt $t3, $t1, vector_input_loop

  jr $ra                   # Return from the function


#------- If you decide to make other functions, place their code here -------
#
#  You do not have to use helper methods, but you may if you would like to.
#  If you do use them, be sure to do all the proper stack management. 
#
#------------ END CODE ---------------