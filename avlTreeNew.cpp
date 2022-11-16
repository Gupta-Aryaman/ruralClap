#define NULL __null
#include<iostream>

class AVLNode{
    int m_data;
    AVLNode* m_left;
    AVLNode* m_right;
    int m_height;

    public:
        AVLNode(int key);

    friend class AVLTree;
};


class AVLTree{
    AVLNode *m_root;
    int m_height;
    bool m_availibility;

    public:
        AVLTree(bool avail){
            m_root = NULL;
            m_availibility = avail;
            m_height = 0;
        }

        int height(AVLNode *N)
        {
            if (N == NULL)
                return 0;
            return N->m_height;
        }

        AVLNode* giveRoot(){
            return m_root;
        }

        int getBalance(AVLNode *N);

        AVLNode *leftRotate(AVLNode *x);
        AVLNode *rightRotate(AVLNode *y);
        AVLNode* insert(AVLNode* node, int key);
};


int max(int a, int b)
{
    return (a > b)? a : b;
}

AVLNode::AVLNode(int key)
{
    m_data = key;
    m_left = NULL;
    m_right = NULL;
    m_height = 1; // new node is initially

}
 
int AVLTree::getBalance(AVLNode *N)
{
    if (N == NULL)
        return 0;
    return height(N->m_left) - height(N->m_right);
}

AVLNode* AVLTree::rightRotate(AVLNode *y)
{
    AVLNode *x = y->m_left;
    AVLNode *T2 = x->m_right;
 
    // Perform rotation
    x->m_right = y;
    y->m_left = T2;
 
    // Update heights
    y->m_height = max(height(y->m_left), height(y->m_right)) + 1;
    x->m_height = max(height(x->m_left), height(x->m_right)) + 1;
 
    // Return new root
    return x;
}
 
// A utility function to left
// rotate subtree rooted with x
// See the diagram given above.
AVLNode* AVLTree::leftRotate(AVLNode *x)
{
    AVLNode *y = x->m_right;
    AVLNode *T2 = y->m_left;
 
    // Perform rotation
    y->m_left = x;
    x->m_right = T2;
 
    // Update heights
    x->m_height = max(height(x->m_left), height(x->m_right)) + 1;
    y->m_height = max(height(y->m_left), height(y->m_right)) + 1;
 
    // Return new root
    return y;
}

AVLNode* AVLTree::insert(AVLNode* root, int key)
{   
    AVLNode *node = new AVLNode(key);
    //AVLNode* root = m_root;

    /* 1. Perform the normal BST insertion */
    if (m_root == NULL)
        m_height+=1;
        m_root = node;
        return(node);
 
    if (key < root->m_data)
        node->m_left = insert(root->m_left, key);
    else if (key > root->m_data)
        node->m_right = insert(root->m_right, key);
    else // Equal keys are not allowed in BST
        return node;
 
    /* 2. Update height of this ancestor node */
    node->m_height = 1 + max(height(node->m_left),
                        height(node->m_right));
 
    /* 3. Get the balance factor of this ancestor
        node to check whether this node became
        unbalanced */
    int balance = getBalance(node);
 
    // If this node becomes unbalanced, then
    // there are 4 cases
 
    // Left Left Case
    if (balance > 1 && key < node->m_left->m_data)
        return rightRotate(node);
 
    // Right Right Case
    if (balance < -1 && key > node->m_right->m_data)
        return leftRotate(node);
 
    // Left Right Case
    if (balance > 1 && key > node->m_left->m_data)
    {
        node->m_left = leftRotate(node->m_left);
        return rightRotate(node);
    }
 
    // Right Left Case
    if (balance < -1 && key < node->m_right->m_data)
    {
        node->m_right = rightRotate(node->m_right);
        return leftRotate(node);
    }
 
    /* return the (unchanged) node pointer */
    return node;
}