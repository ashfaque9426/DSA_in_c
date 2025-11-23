#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct TreeNode {
    char val[2];
    struct TreeNode *left;
    struct TreeNode *right;
};

struct TreeNode *root = NULL;

bool is_empty() {
    return root == NULL;
}

void set_root(char val) {
    if (!is_empty()) {
        printf("Root element already has been set.\n");
        return;
    }

    root = (struct TreeNode*) malloc(sizeof(struct TreeNode));

    root->val[0] = val;
    root->val[1] = '\0';

    root->left = NULL;
    root->right = NULL;

    printf("Root set to: %s\n", root->val);
}

bool insert_node(struct TreeNode* node, char searchVal, char insertion_val, bool add_left) {
    if (node == NULL) return false;

    if(node->val[0] == searchVal) {
        struct TreeNode* new_node = (struct TreeNode*) malloc(sizeof(struct TreeNode));

        new_node->val[0] = insertion_val;
        new_node->val[1] = '\0';
        new_node->left = NULL;
        new_node->right = NULL;

        if(add_left) node->left = new_node;
        else node->right = new_node;

        printf("Inserted '%c' to the %s of '%c'\n", insertion_val, add_left ? "left" : "right", searchVal);
        return true;
    }

    if (insert_node(node->left, searchVal, insertion_val, add_left)) return true;
    if (insert_node(node->right, searchVal, insertion_val, add_left)) return true;

    return false;
}

void display_nodes(struct TreeNode* node) {
    if (is_empty()) {
        printf("The head node is empty.\n");
        return;
    }

    if (node == NULL) return;

    if(node == root) printf("'%c' is the Root Node.\n", node->val[0]);

    if (node->left != NULL) printf("The left child of node '%c' is '%c'\n", node->val[0], node->left->val[0]);

    if (node->right != NULL) printf("The right child of node '%c' is '%c'\n", node->val[0], node->right->val[0]);   

    display_nodes(node->left);
    display_nodes(node->right);
}

int main(void) {
    set_root('A');
    insert_node(root, 'A', 'B', true);
    insert_node(root, 'A', 'C', false);
    insert_node(root, 'B', 'D', true);
    insert_node(root, 'B', 'E', false);
    insert_node(root, 'C', 'F', true);
    insert_node(root, 'C', 'G', false);

    printf("\n");

    printf("Displaying the Binary Tree nodes.\n");
    display_nodes(root);
    
    return 0;
}