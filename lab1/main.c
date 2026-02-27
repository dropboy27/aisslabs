#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int val;
    struct Node *parent;
    struct Node *left;
    struct Node *right;
} Node;

Node* CreateNode(int val) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) return NULL;
    newNode->val = val;
    newNode->parent = NULL;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}
Node* InsertNode(Node *root, Node *newNode){
    if (newNode == NULL){
        return root;
    } 
    if (root == NULL) {
        newNode->parent = NULL;
        return newNode;
    }
    
    Node *originalRoot = root;
    Node *parentLeft = NULL, *parentRight = NULL;
    while (1){
        if (root == NULL){
            if (parentLeft!=NULL){
                newNode->parent = parentLeft;
                parentLeft->left = newNode;
            }
            if (parentRight!=NULL){
                newNode->parent = parentRight;
                parentRight->right = newNode;
            }
            break;
        }
        if (newNode->val <= root->val){
            parentLeft = root;
            parentRight = NULL;
            root = root->left;
        }
        else{
            parentRight = root;
            parentLeft = NULL;
            root = root->right;
        }
    }
    return originalRoot;
}
    

int main() {
    
    return 0;
}