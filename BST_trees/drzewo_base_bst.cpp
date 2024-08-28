#include <iostream>
#include<stdio.h>
using namespace std;

class BSTNode
{
public:
    int key;
    BSTNode* Left;
    BSTNode* Right;
    BSTNode* Parent;

    static BSTNode* Insert(BSTNode* node, int key);
    static void Remove(BSTNode*& node, BSTNode* z);
    static void printTreePreOrder(BSTNode* node);
    static void printTreePostOrder(BSTNode* node);
    static void printTreeInOrder(BSTNode* node);

    static BSTNode* min(BSTNode* root);
    static BSTNode* max(BSTNode* root);

    static BSTNode* inOrderSuccessor(BSTNode* n);
    static BSTNode* inOrderPredeccessor(BSTNode* n);

};

BSTNode* BSTNode::Insert(BSTNode* node, int key)
{

    if (node == NULL)
    {
        node = new BSTNode;
        node->key = key;
        node->Left = NULL;
        node->Right = NULL;
        node->Parent = NULL;
    }
    else if (node->key < key) {
        node->Right = Insert(node->Right, key);
        node->Right->Parent = node;
    }
    else
    {
        node->Left = Insert(node->Left, key);
        node->Left->Parent = node;
    }

    return node;

}

//przechodzenie drzewa preorder (KORZEN, LEWO, PRAWO)
void BSTNode::printTreePreOrder(BSTNode* node) {
    if (node == NULL) {
        return;

    }
    cout << node->key << endl;
    if (node->Left) {
        printTreePreOrder(node->Left);
    }
    if (node->Right) {
        printTreePreOrder(node->Right);
    }
}

//przechodzenie drzewa inorder
void BSTNode::printTreeInOrder(BSTNode* node) {
    if (node == NULL) {
        return;
    }
    if (node->Left) {
        printTreeInOrder(node->Left);

    }
    cout << node->key << endl;
    if (node->Right) {
        printTreeInOrder(node->Right);
    }
}
//przechodzenie drzewa postOrder
void BSTNode::printTreePostOrder(BSTNode* node) {
    if (node == NULL) {
        return;
    }
    if (node->Left) {
        printTreePostOrder(node->Left);
    }
    if (node->Right) {
        printTreePostOrder(node->Right);

    }
    cout << node->key << endl;
}
//wyszukiwanie minimum
BSTNode* BSTNode::min(BSTNode* root) {
    while (root->Left) {
        root = root->Left;
    }
    return root;
}
//wyszukiwanie maximum
BSTNode* BSTNode::max(BSTNode* root) {
    while (root->Right) {
        root = root->Right;
    }
    return root;
}

//znajdowanie wysokosci drzewa
int height(BSTNode* node) {
    if (node == NULL) return 0;
    else {
        int lHeight = height(node->Left);
        int rHeight = height(node->Right);
        if (lHeight > rHeight) {
            return (lHeight + 1);
        }
        else return (rHeight + 1);
    }

}
//znajdowanie nastepnika
BSTNode* BSTNode::inOrderSuccessor(BSTNode* n) {
    if (n->Right) return min(n->Right);
    BSTNode* y = n->Parent;
    while ((y == y->Right) && (n == y->Right)) {
        n = y;
        y = y->Parent;
    }
    return y;
}

//znajdowanie poprzednika
BSTNode* BSTNode::inOrderPredeccessor(BSTNode* n) {
    if (n->Left) return max(n->Left);
    BSTNode* y = n->Parent;
    while ((y == y->Left) && (n == y->Left)) {
        n = y;
        y = y->Parent;
    }
    return y;
}

//usuwanie węzła 
void BSTNode::Remove(BSTNode*& node, BSTNode* z) {
    BSTNode* y;
    if ((z->Left) && (z->Right)) y = inOrderSuccessor(z);
    else y = z;
    BSTNode* x;
    if (y->Left) x = y->Left;
    else x = y->Right;
    if (x) x->Parent = y->Parent;
    if (y->Parent) {
        if (y = y->Parent->Left) {
            y->Parent->Left = x;
        }
        else {
            y->Parent->Right = x;
        }
    }
    else node = x;
    if (y != z) z->key = y->key;
    delete y;
}
int main()
{

    BSTNode* root = NULL;  // Creating an empty tree
    BSTNode* min_node = NULL;
    BSTNode* succ_node = NULL;
    root = BSTNode::Insert(root, 15);
    root = BSTNode::Insert(root, 10);
    root = BSTNode::Insert(root, 20);
    root = BSTNode::Insert(root, 25);
    root = BSTNode::Insert(root, 8);
    root = BSTNode::Insert(root, 12);



    cout << "Preorder :" << endl;
    BSTNode::printTreePreOrder(root);

    cout << "Inorder :" << endl;
    BSTNode::printTreeInOrder(root);

    cout << "Postorder: " << endl;
    BSTNode::printTreePostOrder(root);

    cout << "Minimum : " << (BSTNode::min(root))->key << endl;
    cout << "Maximum : " << (BSTNode::max(root))->key << endl;

    cout << "Inorder successor: " << (BSTNode::inOrderSuccessor(root)->key) << endl;
    cout << "Inorder predecessor: " << (BSTNode::inOrderPredeccessor(root)->key) << endl;

    
    cout<<"Remove 15"<<(BSTNode::Remove(root,15 ))<<endl
    cout << "Stan po usunieciu :" << endl;
    BSTNode::printTreePreOrder(root);

}