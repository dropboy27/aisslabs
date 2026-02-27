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
    Node *parent = NULL;
    int isleft = 0;
    while (1){
        if (root == NULL){
            if (parent!=NULL && isleft == 1){
                newNode->parent = parent;
                parent->left = newNode;
            }
            if (parent!=NULL && isleft == 0){
                newNode->parent = parent;
                parent->right = newNode;
            }
            break;
        }
        if (newNode->val <= root->val){
            parent = root;
            isleft = 1;
            root = root->left;
        }
        else{
            parent = root;
            isleft = 0;
            root = root->right;
        }
    }
    return originalRoot;
}
    
void PrintTree(Node *root, int depth){
    if (root==NULL){
        return NULL;
    }
    for (int i = 0; i < depth; i++) {
        printf("    ");
        printf("%d\n", root->val);
    }
    PrintTree(root->left, depth + 1);
    PrintTree(root->right, depth + 1);
}

Node* DeleteNode(Node *TargetNode){
    if (TargetNode == NULL){
        return NULL;
    }

    Node *root = TargetNode;
    while (root->parent != NULL){
        root = root->parent;
    }

    if (TargetNode->left == NULL && TargetNode->right == NULL){
        Node *NodeParent = TargetNode->parent;
        if (NodeParent == NULL) {
            free(TargetNode);
            return NULL;
        }
        if(TargetNode == NodeParent->left){
            NodeParent->left = NULL; 
        }
        else{
            NodeParent->right = NULL;
        }
        free(TargetNode);
        return root;
    }

    else if (TargetNode->left != NULL && TargetNode->right == NULL){
        Node *NodeParent = TargetNode->parent;
        if (NodeParent == NULL) {
            TargetNode->left->parent = NULL;
            free(TargetNode);
            return NULL;
        }
        TargetNode->left->parent = NodeParent;
        if(TargetNode == NodeParent->left){
            NodeParent->left = TargetNode->left; 
        }
        else{
            NodeParent->right = TargetNode->left;
        }
        free(TargetNode);
        return root;
    }
    else if (TargetNode->left == NULL && TargetNode->right != NULL){
        Node *NodeParent = TargetNode->parent;
        if (NodeParent == NULL) {
            TargetNode->right->parent = NULL;
            free(TargetNode);
            return NULL;
        }
        TargetNode->right->parent = NodeParent;
        if(TargetNode == NodeParent->left){
            NodeParent->left = TargetNode->right;
            
        }
        else{
            NodeParent->right = TargetNode->right;
        }
        free(TargetNode);
        return root;
    }
    else if (TargetNode->left != NULL && TargetNode->right != NULL) {
        Node *NewNode = TargetNode->right;
        while (NewNode->left !=NULL)
        {
            NewNode = NewNode->left;
        }
        if (NewNode->parent == TargetNode){
            NewNode->parent = TargetNode->parent;
            NewNode->left = TargetNode->left;
            free(TargetNode);
        }
        else{
            NewNode->right->parent = NewNode->parent;
            NewNode->parent->left = NewNode->right;
            NewNode->parent = TargetNode ->parent;
            NewNode->left = TargetNode->left;
            NewNode->right = TargetNode->right;
            free(TargetNode);
        }
    }
}


int main() {
    
    return 0;
}