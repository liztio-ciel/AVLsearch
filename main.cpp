#include <stdio.h>
#include <stdlib.h>

struct Node {
    int key;
    struct Node *left;
    struct Node *right;
    int height;
};

int height (struct Node *n){
    if (n == NULL) return 0;
    return n->height;
}

int max (int a, int b){
    return ( a > b) ? a: b;
}

struct Node *newNode (int key){
    struct Node *node = (struct Node*) malloc (sizeof (struct Node));
    node->key = key;
    node->left = NULL;
    node->right = NULL;
    node->height = 1;
    return node;
}

struct Node *rightRotate (struct Node *y){
    struct Node *x = y->left;
    struct Node *T2 = x->right;
    
    x->right = y;
    y->left = T2;
    
    y->height = max (height(y->left), height (y->right)) + 1;
    x->height = max (height(x->left), height (x->right)) + 1;
    
    return x;
    
}

struct Node *leftRotate (struct Node *x){
    struct Node *y = x->right;
    struct Node *T2 = y->left;
    
    y->left = x;
    x->right = T2;
    
    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;
    
    return y;
}

int getBalance (struct Node *n){
    if (n == NULL) return 0;
    return height(n->left) - height(n->right);
}

struct Node *insert (struct Node *n, int key){
    
    if (n == NULL)
        return (newNode(key));
    
    if (key < n->key)
        n->left = insert(n->left, key);
    else if (key > n->key)
        n->right = insert(n->right, key);
    else
        return n;
    
    n->height = 1 + max(height(n->left), height(n->right));
    
    int balance = getBalance(n);
        
    if (balance > 1 && key < n->left->key)
        return rightRotate(n);
    
    if (balance < -1 && key > n->right->key)
        return leftRotate(n);
    
    if (balance > 1 && key > n->left->key){
        n->left = leftRotate(n->left);
        return rightRotate(n);
    }
    
    if (balance < -1 && key < n->right->key){
        n->right = rightRotate(n->right);
        return leftRotate(n);
    }
    
    return n;
    
}

struct Node *minValue (struct Node *node){
    struct Node *curr = node;
    
    while (curr->left != NULL){
        curr = curr->left;
    }
    return curr;
    
}

int search (struct Node *node, int cari){
    while (node != NULL){
        if (cari < node->key){
            node = node->left;
        } else if (cari > node->key){
            node = node->right;
        } else{ //if same
            return 1;
        }
    }
    //-1 means NOT FOUND
    return -1;
}

void preOrder (struct Node *root){
    if (root != NULL){
        printf("%d ", root->key);
        preOrder(root->left);
        preOrder(root->right);
    }
}


int main () {
    struct Node *root = NULL;
    root = insert(root, 5);
    root = insert(root, 3);
    root = insert(root, 10);
    root = insert(root, 2);
    root = insert(root, 1);
    root = insert(root, 4);
    root = insert(root, 7);
    root = insert(root, 6);
    root = insert(root, 9);
    root = insert(root, 8);
    root = insert(root, 11);
    root = insert(root, 12);

    printf ("All nodes inside the root:\n");
    preOrder(root);
    printf("\n");
    
    int cari = 0;
    printf("Input Number to search:\n> ");
    scanf("%d", &cari);
    
    int cek = search(root, cari);
    if (cek == 1){
        //if found
        printf("FOUND\n");
    } else{
        printf("NOT FOUND\n");
    }
    
    
    
    return 0;
}
