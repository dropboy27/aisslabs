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
        return;
    }
    for (int i = 0; i < depth; i++) {
        printf("    ");
        printf("%d\n", root->val);
    }
    PrintTree(root->left, depth + 1);
    PrintTree(root->right, depth + 1);
}


Node* DeleteNode(Node *TargetNode) {
    if (TargetNode == NULL) {
        return NULL;
    }

    Node *root = TargetNode;
    while (root->parent != NULL) {
        root = root->parent;
    }

    if (TargetNode->left == NULL && TargetNode->right == NULL) {
        Node *parent = TargetNode->parent;
        if (parent != NULL) {
            if (parent->left == TargetNode) {
                parent->left = NULL;
            } else {
                parent->right = NULL;
            }
        }
        free(TargetNode);
        if (parent == NULL) {
            return NULL;
        } else {
            return root;
    }

    if (TargetNode->left != NULL && TargetNode->right == NULL) {
        Node *child = TargetNode->left;
        Node *parent = TargetNode->parent;
        child->parent = parent;
        if (parent != NULL) {
            if (parent->left == TargetNode) {
                parent->left = child;
            } else {
                parent->right = child;
            }
            free(TargetNode);
            return root;
        } else {
            free(TargetNode);
            return child;
        }
    }

    if (TargetNode->left == NULL && TargetNode->right != NULL) {
        Node *child = TargetNode->right;
        Node *parent = TargetNode->parent;
        child->parent = parent;
        if (parent != NULL) {
            if (parent->left == TargetNode) {
                parent->left = child;
            } else {
                parent->right = child;
            }
            free(TargetNode);
            return root;
        } else {
            free(TargetNode);
            return child;
        }
    }

    if (TargetNode->left != NULL && TargetNode->right != NULL) {
        Node *successor = TargetNode->right;
        while (successor->left != NULL) {
            successor = successor->left;
        }
        TargetNode->val = successor->val;
        Node *parentOfSucc = successor->parent;

        if (successor->right != NULL) {
            successor->right->parent = parentOfSucc;
            if (parentOfSucc->left == successor) {
                parentOfSucc->left = successor->right;
            } else {
                parentOfSucc->right = successor->right;
            }
        } else {
            if (parentOfSucc->left == successor) {
                parentOfSucc->left = NULL;
            } else {
                parentOfSucc->right = NULL;
            }
        }
        free(successor);

        return root;
    }

    return root;
    }
}

int CountVertex(Node* root){
    if (root == NULL){
        return 0;
    }
    else{
        return 1 + CountVertex(root->left) + CountVertex(root->right);
    }
}

Node* FindNode(Node* root, int val) {
    while (root != NULL) {
        if (val == root->val)
            return root;
        else if (val < root->val)
            root = root->left;
        else
            root = root->right;
    }
    return NULL;
}

int main() {
    Node *root = NULL;
    int choice, val;

    while (1) {
        printf("1. Add node\n");
        printf("2. Print tree\n");
        printf("3. Delete node\n");
        printf("4. Count vertices\n");
        printf("5. Exit\n");
        printf("Choose: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter value: ");
                scanf("%d", &val);
                Node *newNode = CreateNode(val);
                if (newNode == NULL) {
                    printf("Memory allocation failed\n");
                } else {
                    root = InsertNode(root, newNode);
                }
                break;

            case 2:
                PrintTree(root, 0);
                break;

            case 3:
                printf("Enter value to delete: ");
                scanf("%d", &val);
                Node *toDelete = FindNode(root, val);
                if (toDelete == NULL) {
                    printf("Node not found\n");
                } else {
                    root = DeleteNode(toDelete);
                }
                break;

            case 4:
                printf("Number of vertices: %d\n", CountVertex(root));
                break;

            case 5:
                return 0;

            default:
                printf("Invalid choice\n");
        }
    }

    return 0;
}