// MOHAKJOT DHIMAN
// 2023MCB1302

#include <stdio.h>
#include <stdlib.h>

//  function to find the maximum of two numbers
//  Input : two integers a and b
//  Output : integer (maximum of a and b)
int max(int a, int b) {
    if (a > b) return a;
    else return b;
}

// make a struct node and typedef it as 'node'
// node has 4 parameters : key, height, pointer to left and right node
typedef struct node{
    int key;
    struct node* left;
    struct node* right;
    int height;
} node;

// function to create a new node
// Input : key of the node to be created
// Output : pointer to the newly allocated node
node* create_node(int key) {
    // allocate memory for the new node
    node* new_node = (node*)malloc(sizeof(node));

    // if the memory is not allocated, show error
    if (new_node == NULL) {
        printf("Memory allocation failed\n");
        exit(1);
    }

    // assign the key to newly created node
    new_node->key = key;

    // assign height as 1
    new_node->height = 1;

    // assign left and right node pointers as NULL
    new_node->left = NULL;
    new_node->right = NULL;

    // return the pointer to newly created node
    return new_node;
}

// function to find the height of a tree with given node as root node
// Input : pointer to a node
// Output : integer height of the node
int height(node* x) {
    // if the node is null, return 0, else return is height
    if (x == NULL) return 0;
    return x->height;
}


// function to find the balance factor of a node
// Input : pointer of a node
// Output : balance factor of the node
int get_balance_factor(node* x) {
    // if the entered pointer to the node is null, return 0
    if (x == NULL) return 0;

    // balance factor is height of left subtree minus height of right subtree
    return height(x->left) - height(x->right);
}

// function to perform LL-rotation on a node
// Input : pointer to a node
// Output : pointer to the node, which comes at the place of initial node after rotation
node* LL_rotation(node* x ){
    // assign y as the left node of the given node
    node* y = x->left;
    // and z as the right node of y
    node* z = y->right;

    // perform the rotation
    y->right = x;
    x->left = z;

    // update the heights of the nodes x and y after performin the rotation
    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;

    // return the node y
    // because y comes in the place of x after rotation
    return y;
}


// function to perform RR-rotation on a node
// Input : pointer to a node
// Output : pointer to the node, which comes at the place of initial node after rotation
node* RR_rotation(node* x ){
    // assign the node y as the right node of the given node
    node* y = x->right;
    // and z as the left node of y
    node* z = y->left;

    // perform the rotation
    y->left = x;
    x->right = z;

    // update the heights of the nodes x and y after performing the rotation
    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;

    // return the node y
    // which comes in the place of node x after rotation
    return y;
}


// function to perform LR-rotation on a node
// Input : pointer to a node
// Output : pointer to the node, which comes at the place of initial node after rotation
node* LR_rotation(node* x) {
    // in LR case, we first perform RR rotation and then LL rotation

    // perform RR rotation on the left node of the entered node
    x->left = RR_rotation(x->left);

    // now perform LL rotation of the entered node
    return LL_rotation(x);
}

// function to perform RL-rotation on a node
// Input : pointer to a node
// Output : pointer to the node, which comes at the place of initial node after rotation
node* RL_rotation(node* x) {
    // in RL case, we first perform LL rotation and then RR rotation

    // perform LL rotation on the left node of the entered node
    x->right = LL_rotation(x->right);

    // now perform RR rotation on the entered node
    return RR_rotation(x);
}

// function to insert a new node
// Input : pointer to the root of the tree in which new node is to be inserted, key of the new node
// Output : pointer to the root of tree after insertion of the node
node* insert(node* node, int key) {
    // if the node is null, create a new node
    if (node == NULL) return create_node(key);

    // if the key is less than the node, call insert recursively on the left subtree
    if(key < node->key) node->left = insert(node->left, key);
    // if the key is greater than the node, call insert recursively ont he right subtree
    else if(key > node->key) node->right = insert(node->right, key);

    // if it is the same, dont insert
    else return node;

    // update the height of the node
    node->height = max(height(node->left), height(node->right)) + 1;

    // find the balance factor of the node
    int balance_factor = get_balance_factor(node);

    // LL-rotation case
    if (balance_factor > 1 && key < node->left->key) 
        return LL_rotation(node);
   
    // RR rotation case
    if (balance_factor < -1 && key > node->right->key)
        return RR_rotation(node);

    // LR rotation case 
    if (balance_factor > 1 && key > node->left->key) 
        return LR_rotation(node);

    // RL rotation case
    if (balance_factor < -1 && key < node->right->key)
        return RL_rotation(node);

    // return the root node after insertion
    return node;
}

// function to print the inorder traversal of the tree
// Input : pointer to the root of the tree
// Output : prints the nodes inorder but return nothing
void inorder_traversal(node* root) {
    if (root != NULL) {
        // recursively call the function on left subtree
        inorder_traversal(root->left);
        // print the root node key
        printf("%i ", root->key);
        // recursively call the function on the right subtree
        inorder_traversal(root->right);
    }
}

// function to print the preorder traversal of the tree
// Input : pointer to the root of the tree
// Output : prints the nodes in preorder but return nothing
void preorder_traversal(node* root) {
    if(root != NULL) {
        // print the key of the root node
        printf("%d ", root->key);
        // recursively call the function on the left subtree
        preorder_traversal(root->left);
        // recursively cal the function on the right subtree
        preorder_traversal(root->right);
    }
}

// function to search for a node in a tree
// Input : pointer to the root of tree in which search is to be performed
// Output : pointer to the node to be searched for
node* search(node* root, int key) {
    // in case the key is found or root is null, return it
    if (root == NULL || key == root->key) return root;

    // if key is greater than the key of root, search in the right subtree
    if (key > root->key) return search(root->right, key);

    // else search in the left subtree
    else return search(root->left, key);
}

// MAIN FUNCTION
int main()
{
    // create a null pointer for the root
    node* root = NULL;

    // insert 0 to 24 in the tree rooted at root node
    for (int i = 0 ; i < 25; i++) {
        root = insert(root, i);
    }
    printf("AVL tree constructed by inserting 0 to 24 elements\n");

    // while loop to perform operations according to the user
    while (1) {
        // print the choices of operation
        printf("\ni) Insert:\n");
        printf("s) Search:\n");
        printf("p) Preorder and Inorder in Separate lines:\n");
        printf("q) Quit:\n\n");

        // input the choice of the user
        char choice;
        printf("Enter Your Choice: ");
        scanf(" %c", &choice);

        // Insert
        if (choice == 'i') {
            // input the value to be inserted
            int n;
            printf("Enter a data to insert: ");
            scanf("%i", &n);

            // insert the key in the root 
            root = insert(root, n);
        }

        // Search 
        if (choice == 's') {
            // input the key to be searched for
            int n;
            printf("Enter data you want to search: ");
            scanf("%i", &n);

            // store the node in s_node after searching
            node* s_node = search(root, n);

            // if s_node is NULL, node is not found
            if (s_node == NULL) printf("Not Present\n");

            // if the node is found, print its balance factor and height
            else {
                printf("Present\n");
                printf("Balance factor of %i is %i\n", s_node->key, get_balance_factor(s_node));
                printf("Height of %i in the AVL tree is %i\n", s_node->key, s_node->height - 1);
            }
        }

        // preorder and inorder traversal
        if (choice == 'p') {
            // print the preorder traversal of the tree
            printf("Preorder Sequence:\n");
            preorder_traversal(root);

            // print the inroder traversal of the tree
            printf("\nInorder Sequence:\n");
            inorder_traversal(root);
            printf("\n");
        }

        // Quit
        // break from the while loop
        if (choice == 'q') break;

    }

    return 0;
}
