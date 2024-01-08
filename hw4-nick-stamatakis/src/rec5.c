//
// Created by Nikol on 10/24/2023.
//
#include <stdio.h>
#include <stdlib.h>

typedef struct TreeNode {
    int value;
    struct TreeNode *left;
    struct TreeNode *right;
} TreeNode;

void print_tree(TreeNode *root) {
    if (root == NULL) {
        return;
    }
    print_tree(root->left);
    printf("%d  ", root->value);
    if(root->left != NULL) {
        printf(" %d", root->left->value);
    } else {
        printf(" NULL");
    }
    if(root->right != NULL) {
        printf(" %d", root->right->value);
    } else {
        printf(" NULL");
    }
    printf("\n");
    print_tree(root->right);
}

/**
 * Argv takes in integers in level order and creates a binary tree.
 * Use atoi to convert the input string to an integer.
*/
int main(int argc, char *argv[]){
    TreeNode* used[100];
    TreeNode *root = NULL;
    TreeNode *current = NULL;
    int previous = 1;

    for(int i = 1; i < argc; i++){
        used[i] = malloc(sizeof(TreeNode));
        used[i]->value = atoi(argv[i]);
        used[i]->left = NULL;
        used[i]->right = NULL;
    }
    // For each argument, create a new TreeNode and add it to the tree.
    for(int i = 1; i < argc; i++) {
        current = used[i];
        // FILL IN HERE
    }

    print_tree(root);

    return EXIT_SUCCESS;
}
