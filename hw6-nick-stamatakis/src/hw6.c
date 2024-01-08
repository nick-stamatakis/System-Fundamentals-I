#include "../include/hw6.h"

int main() {
    for (int i = 1; i <= 20; ++i) {
        char filename[20];
        snprintf(filename, sizeof(filename), "../tests.in/script%02d.txt", i);

        // Open the file
        FILE* file = fopen(filename, "r");
        if (file == NULL) {
            fprintf(stderr, "Error opening file %s for Test Case %d.\n", filename, i);
            continue;
        }

        // Read and print the contents of the file
        printf("Test Case %d:\n", i);
        printf("Contents of file %s:\n", filename);

        char buffer[256];
        while (fgets(buffer, sizeof(buffer), file) != NULL) {
            printf("%s", buffer);
        }

        fclose(file);  // Close the file

        // Execute the script and print the output
        matrix_sf* result = execute_script_sf(filename);

        if (result != NULL) {
            printf("\nOutput of test case:\n");
            print_matrix_sf(result);
            free(result);
        } else {
            fprintf(stderr, "Error executing script for Test Case %d.\n", i);
        }

        printf("\n\n");
    }

    return 0;
}

bst_sf* insert_bst_sf(matrix_sf *mat, bst_sf *root) {
    // Create a new node if the BST is empty
    if (root == NULL) {
        bst_sf *newNode = (bst_sf *)malloc(sizeof(bst_sf));
        if (!newNode) {
            fprintf(stderr, "Memory allocation failed.\n");
            exit(EXIT_FAILURE);
        }

        newNode->mat = mat;
        newNode->left_child = newNode->right_child = NULL;
        return newNode;
    }
    // printf("%c", mat->name);
    // printf("%c", root->mat->name);

    // Compare matrix names to determine the insertion point
    int compareResult = mat->name - root->mat->name;

    // Insert to the left subtree if the matrix name is smaller
    if (compareResult < 0) {
        root->left_child = insert_bst_sf(mat, root->left_child);
    }
        // Insert to the right subtree if the matrix name is larger
    else if (compareResult > 0) {
        root->right_child = insert_bst_sf(mat, root->right_child);
    }
    return root;
}

matrix_sf* find_bst_sf(char name, bst_sf *root) {
    // Base case: If the tree is empty
    if (root == NULL) {
        return NULL;
    }

    // If the matrix is found
    if (root->mat != NULL && root->mat->name == name) {
        return root->mat;
    }

    // If the matrix name is smaller, search in the left subtree
    if (name < root->mat->name) {
        return find_bst_sf(name, root->left_child);
    }
        // If the matrix name is larger, search in the right subtree
    else {
        return find_bst_sf(name, root->right_child);
    }
}



void free_bst_sf(bst_sf *root) {
    if (root == NULL) {
        return;  // Base case: reached a leaf or an empty tree
    }

    // Recursively free the left and right subtrees
    free_bst_sf(root->left_child);
    free_bst_sf(root->right_child);

    // Free the matrix_sf struct pointed to by the current node
    if (root->mat != NULL) {
        // Only free the matrix_sf struct itself
        free(root->mat);
    }

    // Free the current BST node
    free(root);
}

void free_bst_sf2(bst_sf *root) {
    if (root == NULL) {
        return;  // Base case: reached a leaf or an empty tree
    }

    // Recursively free the left and right subtrees
    free_bst_sf(root->left_child);
    free_bst_sf(root->right_child);

    // Free the matrix_sf struct pointed to by the current node
    if (root->mat != NULL) {
        // Only free the matrix_sf struct itself
        free(root->mat);
    }

    // Free the current BST node
    // free(root);
}

matrix_sf* add_mats_sf(const matrix_sf *mat1, const matrix_sf *mat2) {
    if (mat1->num_rows != mat2->num_rows || mat1->num_cols != mat2->num_cols) {
        fprintf(stderr, "Matrix dimensions do not match for addition.\n");
        return NULL;
    }

    matrix_sf *result = (matrix_sf *)malloc(sizeof(matrix_sf) + mat1->num_rows * mat1->num_cols * sizeof(int));
    if (!result) {
        fprintf(stderr, "Memory allocation failed.\n");
        return NULL;
    }

    result->name = ' ';
    result->num_rows = mat1->num_rows;
    result->num_cols = mat1->num_cols;

    for (unsigned int i = 0; i < result->num_rows * result->num_cols; ++i) {
        result->values[i] = mat1->values[i] + mat2->values[i];
    }

    return result;
}

matrix_sf* mult_mats_sf(const matrix_sf *mat1, const matrix_sf *mat2) {
    if (mat1->num_cols != mat2->num_rows) {
        fprintf(stderr, "Invalid matrix dimensions for multiplication.\n");
        return NULL;
    }

    matrix_sf *result = (matrix_sf *)malloc(sizeof(matrix_sf) + mat1->num_rows * mat2->num_cols * sizeof(int));
    if (!result) {
        fprintf(stderr, "Memory allocation failed.\n");
        return NULL;
    }

    result->name = ' ';
    result->num_rows = mat1->num_rows;
    result->num_cols = mat2->num_cols;

    for (unsigned int i = 0; i < result->num_rows; ++i) {
        for (unsigned int j = 0; j < result->num_cols; ++j) {
            int sum = 0;
            for (unsigned int k = 0; k < mat1->num_cols; ++k) {
                sum += mat1->values[i * mat1->num_cols + k] * mat2->values[k * mat2->num_cols + j];
            }
            result->values[i * result->num_cols + j] = sum;
        }
    }

    return result;
}

matrix_sf* transpose_mat_sf(const matrix_sf *mat) {
    // Allocate memory for the transposed matrix
    matrix_sf *transposed = (matrix_sf *)malloc(sizeof(matrix_sf) + mat->num_cols * mat->num_rows * sizeof(int));
    if (!transposed) {
        fprintf(stderr, "Memory allocation failed.\n");
        return NULL;
    }

    transposed->name = ' ';
    transposed->num_rows = mat->num_cols;
    transposed->num_cols = mat->num_rows;

    // Fill in the transposed matrix values directly
    for (unsigned int i = 0; i < transposed->num_rows; ++i) {
        for (unsigned int j = 0; j < transposed->num_cols; ++j) {
            transposed->values[i * transposed->num_cols + j] = mat->values[j * mat->num_cols + i];
        }
    }

    return transposed;
}
matrix_sf* create_matrix_sf(char name, const char *expr) {
    printf("%c\n", name);

    // Set num_rows and num_cols
    unsigned int num_rows, num_cols;
    sscanf(expr, "%u %u", &num_rows, &num_cols);

    // Allocate memory for the entire structure, including the flexible array member
    matrix_sf *matrix = malloc(sizeof(matrix_sf) + num_rows * num_cols * sizeof(int));

    if (matrix == NULL) {
        // Memory allocation failed
        return NULL;
    }

    matrix->name = name;
    matrix->num_rows = num_rows;
    matrix->num_cols = num_cols;

    // Parse and fill in the matrix values
    const char *ptr = expr;
    int index = 0;

    // Skip header information (number of rows and columns)
    while (*ptr != '[' && *ptr != '\0') {
        ptr++;
    }

    while (*ptr != '\0' && *ptr != ']') {
        if ((*ptr >= '0' && *ptr <= '9') || (*ptr == '-' && *(ptr + 1) >= '0' && *(ptr + 1) <= '9')) {
            // Read an integer value (including negative numbers)
            matrix->values[index] = strtol(ptr, (char **)&ptr, 10);
            index++;
        } else {
            // Skip non-numeric characters
            ptr++;
        }
    }

    return matrix;
}

// Structure to represent a stack
struct Stack {
    int top;
    unsigned capacity;
    char* array;
};

// Function to check if a character is an operand (matrix name)
int isOperand(char ch) {
    return (ch >= 'A' && ch <= 'Z');
}

// Function to check precedence of operators
int precedence(char op) {
    if (op == '\'') return 3; // higher precedence for transpose
    if (op == '*' || op == '/') return 2;
    if (op == '+' || op == '-') return 1;
    return -1;
}

// Function to push a character to the stack
void push(struct Stack* stack, char item) {
    stack->array[++stack->top] = item;
}

// Function to create a stack with a given capacity
struct Stack* createStack(unsigned capacity) {
    struct Stack* stack = (struct Stack*)malloc(sizeof(struct Stack));
    stack->top = -1;
    stack->capacity = capacity;
    stack->array = (char*)malloc(stack->capacity * sizeof(char));
    return stack;
}

// Function to pop a character from the stack
char pop(struct Stack* stack) {
    if (stack->top == -1)
        return '\0';
    return stack->array[stack->top--];
}

char* infix2postfix_sf(char *infix) {
    int len = strlen(infix);
    struct Stack* stack = createStack(len);
    char* postfix = (char*)malloc((len + 1) * sizeof(char));
    int i, j;

    for (i = 0, j = 0; i < len; ++i) {
        char c = infix[i];

        if (isOperand(c)) {
            postfix[j++] = c;
        } else if (c == '(') {
            push(stack, c);
        } else if (c == ')') {
            while (stack->top != -1 && stack->array[stack->top] != '(') {
                postfix[j++] = pop(stack);
            }
            pop(stack); // Pop '('
        } else {
            while (stack->top != -1 && precedence(c) <= precedence(stack->array[stack->top])) {
                postfix[j++] = pop(stack);
            }
            push(stack, c);
        }
    }

    while (stack->top != -1) {
        postfix[j++] = pop(stack);
    }

    postfix[j] = '\0';

    // Free the memory allocated for the stack
    free(stack->array);
    free(stack);

    return postfix;
}

// Structure to represent a stack of matrix_sf pointers
typedef struct MatrixStack {
    int top;
    unsigned capacity;
    matrix_sf **array;
} MatrixStack;

// Function to push a matrix_sf pointer to the stack
void pushMatrix(MatrixStack *stack, matrix_sf *item) {
    stack->array[++stack->top] = item;
}

// Function to create a stack with a given capacity for matrix_sf pointers
MatrixStack *createMatrixStack(unsigned capacity) {
    MatrixStack *stack = (MatrixStack *)malloc(sizeof(MatrixStack));
    stack->top = -1;
    stack->capacity = capacity;
    stack->array = (matrix_sf **)malloc(stack->capacity * sizeof(matrix_sf *));
    return stack;
}

// Function to pop a matrix_sf pointer from the stack
matrix_sf *popMatrix(MatrixStack *stack) {
    if (stack->top == -1)
        return NULL;
    return stack->array[stack->top--];
}

// Function to check if the matrix stack is empty
int isEmptyMatrixStack(MatrixStack *stack) {
    return stack->top == -1;
}

// Function to free memory used by the matrix stack
void freeMatrixStack(MatrixStack *stack) {
    free(stack->array);
    free(stack);
}
// Function to remove whitespace characters from a string
char* removeWhitespace(const char *str) {
    if (str == NULL) {
        // Handle NULL input if needed
        return NULL;
    }

    int len = strlen(str);
    char *result = (char *)malloc((len + 1) * sizeof(char));  // Allocate memory for the new string

    if (result == NULL) {
        // Memory allocation failed
        fprintf(stderr, "Memory allocation failed.\n");
        exit(EXIT_FAILURE);  // Or handle the error in another way
    }

    int readIndex = 0, writeIndex = 0;

    while (readIndex < len) {
        if (!isspace((unsigned char)str[readIndex])) {
            // If the character is not a whitespace character, copy it to the new string
            result[writeIndex] = str[readIndex];
            writeIndex++;
        }

        readIndex++;
    }

    // Null-terminate the new string
    result[writeIndex] = '\0';

    return result;
}

matrix_sf *evaluate_expr_sf(char name, char *expr, bst_sf *root) {
    // Convert infix expression to postfix
    char *noSpaceExpr = removeWhitespace(expr);
    char *postfixExpr = infix2postfix_sf(noSpaceExpr);
    //printf("%s\n", postfixExpr);

    // Create a stack for matrix_sf pointers
    MatrixStack *matrixStack = createMatrixStack(strlen(postfixExpr));

    // Process characters sequentially from postfixExpr
    for (int i = 0; postfixExpr[i] != '\0'; ++i) {
        char c = postfixExpr[i];

        if (isOperand(c)) {
            // Operand (matrix name): Push the matrix onto the stack
            matrix_sf *matrix = find_bst_sf(c, root);
            if (matrix != NULL) {
                pushMatrix(matrixStack, matrix);
            } else {
                fprintf(stderr, "Matrix %c not found in the BST.\n", c);
                // Handle the error as needed, e.g., return NULL or exit the function
            }
        } else if (c == '\'') {
            // Transpose: Pop the top matrix, transpose it, and push the result
            matrix_sf *matrix = popMatrix(matrixStack);
            if (matrix != NULL) {
                matrix_sf *result = transpose_mat_sf(matrix);
                // Set the name of the result matrix
                result->name = name;
                pushMatrix(matrixStack, result);
            } else {
                fprintf(stderr, "Error: Attempted to transpose a NULL matrix.\n");
                // Handle the error as needed, e.g., return NULL or exit the function
            }
        } else if (c == '+' || c == '*') {
            // Binary operation: Pop the top two matrices, perform the operation, and push the result
            matrix_sf *matrix2 = popMatrix(matrixStack);
            matrix_sf *matrix1 = popMatrix(matrixStack);

            if (matrix1 != NULL && matrix2 != NULL) {
                matrix_sf *result;
                if (c == '+') {
                    result = add_mats_sf(matrix1, matrix2);
                } else if (c == '*') {
                    result = mult_mats_sf(matrix1, matrix2);
                }

                // Set the name of the result matrix
                result->name = name;

                pushMatrix(matrixStack, result);

                // Free the matrices as they were popped off the stack
                // Do not free them here; free them after the loop
            }
        }
    }

    // The final result is on top of the stack
    matrix_sf *finalResult = popMatrix(matrixStack);

    //free whitespace expression
    free(noSpaceExpr);

    // Free the postfix expression
    free(postfixExpr);

    // Free matrices left on the stack
    while (!isEmptyMatrixStack(matrixStack)) {
        matrix_sf *matrix = popMatrix(matrixStack);
        free(matrixStack->array);
        free(matrix);
    }

    // Free the matrix stack
    freeMatrixStack(matrixStack);

    return finalResult;
}

matrix_sf* execute_script_sf(char* filename) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        fprintf(stderr, "Error opening file: %s\n", filename);
        return NULL;
    }

    char* line = NULL;
    size_t max_line_size = MAX_LINE_LEN*2;

    // Initialize an empty BST
    bst_sf* matrix_bst = NULL;
    matrix_sf* result = NULL;
    matrix_sf* finalResult = NULL;

    // Read lines from the file using getline
    while (getline(&line, &max_line_size, file) != -1) {
        // Check if the line is empty
        if (line[0] == '\n') {
            continue;
        }


        char name = line[0];
        int index_of_equals_sign = 2;
        // Allocate memory for expr
        char* expr = malloc(MAX_LINE_LEN*2);

        // Copy all characters after the equal sign to expr
        strcpy(expr, line + index_of_equals_sign+ 1);

        // Print the results (you can modify this part based on your requirements)
        // printf("Name: %c\n", name);
        // printf("Index of '=': %d\n", index_of_equals_sign);
        //printf("Expr: %s\n", expr);

        char first_non_space = ' ';  // Default to space if none is found
        for (int i = 0; expr[i] != '\0'; i++) {
            if (isalpha(expr[i]) || isdigit(expr[i])) {
                first_non_space = expr[i];
                //printf("%c", expr[i]);
                break;
            }
        }
        //printf("%c\n", first_non_space);
        if (isdigit(first_non_space)) {
            // Creating a matrix
            result = create_matrix_sf(name, expr);  // Assuming create_matrix_sf returns a matrix_sf*
            matrix_bst = insert_bst_sf(result, matrix_bst);
            //print_matrix_sf(result);
            //print_matrices_in_bst(matrix_bst);
        }
        else {
            //printf("%c\n", name);
            // Evaluating an expression
            result = evaluate_expr_sf(name, expr, matrix_bst);
            //print_matrix_sf(result);
            matrix_bst = insert_bst_sf(result, matrix_bst);
            //print_matrices_in_bst(matrix_bst);
            finalResult = copy_matrix(result->num_rows, result->num_cols, result->values);
        }

        // Free the memory allocated for the expression
        result = NULL;
        free(expr);
    }

    // Free the memory allocated for line
    free(line);
    fclose(file);

    // Free the entire BST (including matrix values)
    free_bst_sf2(matrix_bst);
    return finalResult;
}

// This is a utility function used during testing. Feel free to adapt the code to implement some of
// the assignment. Feel equally free to ignore it.
matrix_sf *copy_matrix(unsigned int num_rows, unsigned int num_cols, int values[]) {
    matrix_sf *m = malloc(sizeof(matrix_sf)+num_rows*num_cols*sizeof(int));
    m->name = '?';
    m->num_rows = num_rows;
    m->num_cols = num_cols;
    memcpy(m->values, values, num_rows*num_cols*sizeof(int));
    return m;
}
// Don't touch this function. It's used by the testing framework.
// It's been left here in case it helps you debug and test your code.
void print_matrix_sf(matrix_sf *mat) {
    assert(mat != NULL);
    assert(mat->num_rows <= 1000);
    assert(mat->num_cols <= 1000);
    printf("%d %d ", mat->num_rows, mat->num_cols);
    for (unsigned int i = 0; i < mat->num_rows*mat->num_cols; i++) {
        printf("%d", mat->values[i]);
        if (i < mat->num_rows*mat->num_cols-1)
            printf(" ");
    }
    printf("\n");
}
void print_matrices_in_bst(bst_sf* root) {
    if (root != NULL) {
        print_matrices_in_bst(root->left_child);
        if (root->mat != NULL) {
            printf("Matrix %c:\n", root->mat->name);
            print_matrix_sf(root->mat);
        }
        print_matrices_in_bst(root->right_child);
    }
}