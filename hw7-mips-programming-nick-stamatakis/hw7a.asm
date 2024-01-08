############################################
# Triangle(0) or Square(1) or Pyramid (2)?1
# Required size? 3
# 
# ***
# ***
# ***
# -- program is finished running --
############################################

.data
prompt_choice:  .asciiz "Triangle(0) or Square(1) or Pyramid (2)? "
prompt_size:    .asciiz "Required size? "
error_message_size: .asciiz "Error: Size must be a non-negative integer.\n"
error_message_choice: .asciiz "Error: Invalid choice. Please enter 0, 1, or 2.\n"
star:           .asciiz "*"
newline:        .asciiz "\n"
space:          .asciiz " "
buffer_choice:  .space 4    # Reserve space for reading choice input
buffer_size:    .space 10   # Reserve space for reading size input

.text
main:
    # Prompt user for the choice
    li $v0, 4               # syscall code for print_str
    la $a0, prompt_choice   # load address of prompt_choice
    syscall

    # Read user input for choice
    li $v0, 5               # syscall code for read_int
    syscall
    move $t6, $v0           # store the choice in $t6

    # Check the entered choice
        # Check the entered choice
    li $t7, 0   # Load immediate 0 into $t7
    beq $t6, $t7, triangle_selected

    li $t7, 1   # Load immediate 1 into $t7
    beq $t6, $t7, square_selected

    li $t7, 2   # Load immediate 2 into $t7
    beq $t6, $t7, pyramid_selected
    
    # Invalid choice
    j choice_error

pyramid_selected:
    # Prompt user for the size of the pyramid
    li $v0, 4               # syscall code for print_str
    la $a0, prompt_size     # load address of prompt_size
    syscall

    # Read user input for size
    li $v0, 5               # syscall code for read_int
    syscall
    move $t0, $v0           # store the size in $t0
    
    # Check if size is negative
    blt $t0, $zero, size_error

    # Draw the pyramid
    jal draw_pyramid
    j end_program

triangle_selected:
    # Prompt user for the size of the triangle
    li $v0, 4               # syscall code for print_str
    la $a0, prompt_size     # load address of prompt_size
    syscall

    # Read user input for size
    li $v0, 5               # syscall code for read_int
    syscall
    move $t0, $v0           # store the size in $t0
    
    # Check if size is negative
    blt $t0, $zero, size_error

    # Draw the triangle
    jal draw_triangle
    j end_program

square_selected:
    # Prompt user for the size of the square
    li $v0, 4               # syscall code for print_str
    la $a0, prompt_size     # load address of prompt_size
    syscall

    # Read user input for size
    li $v0, 5               # syscall code for read_int
    syscall
    move $t0, $v0           # store the size in $t0
    
    # Check if size is negative
    blt $t0, $zero, size_error

    # Draw the square
    jal draw_square
    j end_program

end_program:
    # Exit program
    li $v0, 10              # syscall code for exit
    syscall

# Draw Pyramid function
draw_pyramid:
    # Arguments: $t0 = height

    # Initialize loop counter
    li $t1, 1               # $t1 = i (starting from 1)

    draw_row_loop_pyramid:
        # Check if i > height
        bgt $t1, $t0, end_draw_pyramid

        # Calculate the number of spaces for the current row
        sub $t4, $t0, $t1       # $t4 = height - i

        # Inner loop to print spaces
        li $t2, 0               # $t2 = j
        draw_space_loop_pyramid:
            # Check if j > $t4
            bge $t2, $t4, draw_star_loop_pyramid

            # Print space
            li $v0, 4               # syscall code for print_str
            la $a0, space           # load address of space
            syscall

            # Increment j
            addi $t2, $t2, 1
            j draw_space_loop_pyramid

        draw_star_loop_pyramid:
            # Inner loop to print stars
            li $t3, 0               # $t3 = k
            draw_star_inner_loop_pyramid:
                # Check if k >= i
                bge $t3, $t1, newline_after_row_pyramid

                # Check if it's the first star in the row
                beq $t3, $zero, print_star_pyramid_first_star

                # Print space between stars
                li $v0, 4               # syscall code for print_str
                la $a0, space           # load address of space
                syscall

                print_star_pyramid_first_star:
                # Print "*"
                li $v0, 4               # syscall code for print_str
                la $a0, star            # load address of star
                syscall

                # Increment k
                addi $t3, $t3, 1
                j draw_star_inner_loop_pyramid

            newline_after_row_pyramid:
                # Print newline
                li $v0, 4               # syscall code for print_str
                la $a0, newline         # load address of newline
                syscall

        # Increment i
        addi $t1, $t1, 1
        j draw_row_loop_pyramid

    end_draw_pyramid:
    jr $ra

# Draw Triangle function
draw_triangle:
    # Arguments: $t0 = height

    # Initialize loop counter
    li $t1, 0               # $t1 = i

    draw_row_loop:
        # Check if i >= height
        bge $t1, $t0, end_draw_triangle

        # Inner loop to print stars
        li $t2, 0               # $t2 = j
        draw_star_loop:
            # Check if j > i
            bgt $t2, $t1, newline_after_row

            # Print "*"
            li $v0, 4               # syscall code for print_str
            la $a0, star            # load address of star
            syscall

            # Increment j
            addi $t2, $t2, 1
            j draw_star_loop

        newline_after_row:
            # Print newline
            li $v0, 4               # syscall code for print_str
            la $a0, newline         # load address of newline
            syscall

        # Increment i
        addi $t1, $t1, 1
        j draw_row_loop

    end_draw_triangle:
    jr $ra

# Draw Square function
draw_square:
    # Arguments: $t0 = size

    # Initialize loop counter
    li $t1, 0               # $t1 = i

    draw_row_loop_square:
        # Check if i >= size
        bge $t1, $t0, end_draw_square

        # Inner loop to print stars
        li $t2, 0               # $t2 = j
        draw_star_loop_square:
            # Check if j >= size
            bge $t2, $t0, newline_after_row_square

            # Print "*"
            li $v0, 4               # syscall code for print_str
            la $a0, star            # load address of star
            syscall

            # Increment j
            addi $t2, $t2, 1
            j draw_star_loop_square

        newline_after_row_square:
            # Print newline
            li $v0, 4               # syscall code for print_str
            la $a0, newline         # load address of newline
            syscall

        # Increment i
        addi $t1, $t1, 1
        j draw_row_loop_square

    end_draw_square:
    jr $ra

size_error:
    # Print error message for invalid size
    li $v0, 4               # syscall code for print_str
    la $a0, error_message_size   # load address of error_message_size
    syscall
    j end_program
    
choice_error:
    # Print error message for invalid choice
    li $v0, 4               # syscall code for print_str
    la $a0, error_message_choice   # error message
    syscall
    j end_program