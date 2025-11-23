#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node *left;
    struct Node *right;
    int height;
};

int max(int a, int b) {
    return (a > b) ? a : b;
}

int height(struct Node* node) {
    return (node == NULL) ? 0 : node->height;
}

int get_balance(struct Node* node) {
    return (node == NULL) ? 0 : height(node->left) - height(node->right);
}

struct Node *new_node(int data) {
    struct Node *node = (struct Node*)malloc(sizeof(struct Node));
    node->data = data;
    node->left = node->right = NULL;
    node->height = 1;

    return node;
}

struct Node *right_rotate(struct Node* y) {
    struct Node* x = y->left;
    struct Node* T2 = x->right;

    x->right = y;
    y->left = T2;

    x->height = 1 + max(height(x->left), height(x->right));
    y->height = 1 + max(height(y->left), height(y->right));

    return x;
}

struct Node *left_rotate(struct Node* y) {
    struct Node *x = y->right;
    struct Node *T2 = x->left;

    x->left = y;
    y->right = T2;

    x->height = 1 + max(height(x->left), height(x->right));
    y->height = 1 + max(height(y->left), height(y->right));

    return x;
}

struct Node *insert(struct Node *node, int data) {
    if (node == NULL) return new_node(data);

    if (data < node->data) {
        node->left = insert(node->left, data);
    }
    else if(data > node->data) {
        node->right = insert(node->right, data);
    }
    else {
        return node;
    }

    node->height = 1 + max(height(node->left), height(node->right));

    int balance = get_balance(node);

    if (balance > 1 && data < node->left->data) {
        return right_rotate(node);
    }

    if (balance < -1 && data > node->right->data) {
        return left_rotate(node);
    }

    if (balance > 1 && data > node->left->data) {
        node->left = left_rotate(node->left);
        return right_rotate(node);
    }

    if (balance < -1 && data < node->right->data) {
        node->right = right_rotate(node->right);
        return left_rotate(node);
    }

    return node;
}

void inorder(struct Node *root) {
    if (root == NULL) return;

    inorder(root->left);
    printf("%d ", root->data);
    inorder(root->right);
}

int main(void) {
    struct Node *root = NULL;

    root = insert(root, 10);
    root = insert(root, 20);
    root = insert(root, 30);   // RR rotation
    root = insert(root, 40);
    root = insert(root, 50);
    root = insert(root, 25);

    inorder(root);
    printf("\n");

    return 0;
}