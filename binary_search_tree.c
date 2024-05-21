#include <stdio.h>
#include <stdlib.h>

typedef struct TreeNode {
    char data;
    struct TreeNode* left;
    struct TreeNode* right;
} TreeNode;

TreeNode* createNode(char data) {
    TreeNode* newNode = (TreeNode*)malloc(sizeof(TreeNode));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

TreeNode* insertNode(TreeNode* root, char data) {
    if (root == NULL) {
        root = createNode(data);
    } else if (data < root->data) {
        root->left = insertNode(root->left, data);
    } else {
        root->right = insertNode(root->right, data);
    }
    return root;
}

TreeNode* findMinNode(TreeNode* node) {
    TreeNode* current = node;
    while (current && current->left != NULL)
        current = current->left;
    return current;
}

TreeNode* deleteNode(TreeNode* root, char data) {
    if (root == NULL) {
        printf("찾는 키가 없습니다! 문자를 찾지 못했습니다.\n");
        return root;
    }
    if (data < root->data) {
        root->left = deleteNode(root->left, data);
    } else if (data > root->data) {
        root->right = deleteNode(root->right, data);
    } else {
        if (root->left == NULL) {
            TreeNode* temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            TreeNode* temp = root->left;
            free(root);
            return temp;
        }
        TreeNode* temp = findMinNode(root->right);
        root->data = temp->data;
        root->right = deleteNode(root->right, temp->data);
    }
    return root;
}

TreeNode* searchNode(TreeNode* root, char data) {
    if (root == NULL || root->data == data)
        return root;
    if (data < root->data)
        return searchNode(root->left, data);
    return searchNode(root->right, data);
}

void inorder(TreeNode* root) {
    if (root != NULL) {
        inorder(root->left);
        printf("%c ", root->data);
        inorder(root->right);
    }
}

void displayMenu() {
    printf("\n*************************\n");
    printf("1 : 트리 출력\n");
    printf("2 : 문자 삽입\n");
    printf("3 : 문자 삭제\n");
    printf("4 : 문자 검색\n");
    printf("5 : 종료\n");
    printf("*************************\n");
    printf("메뉴 입력 >> ");
}

int main() {
    TreeNode* root = NULL;
    root = insertNode(root, 'A');
    root = insertNode(root, 'B');
    root = insertNode(root, 'D');
    root = insertNode(root, 'E');
    root = insertNode(root, 'G');
    root = insertNode(root, 'H');
    root = insertNode(root, 'I');
    root = insertNode(root, 'J');
    root = insertNode(root, 'L');
    root = insertNode(root, 'M');
    root = insertNode(root, 'N');
    root = insertNode(root, 'Q');

    int choice;
    char input;
    
    while (1) {
        displayMenu();
        scanf(" %d", &choice);
        switch (choice) {
            case 1:
                printf("[이진 트리 출력] ");
                inorder(root);
                printf("\n");
                break;
            case 2:
                printf("삽입할 문자를 입력하세요: ");
                scanf(" %c", &input);
                root = insertNode(root, input);
                break;
            case 3:
                printf("삭제할 문자를 입력하세요: ");
                scanf(" %c", &input);
                root = deleteNode(root, input);
                break;
            case 4:
                printf("검색할 문자를 입력하세요: ");
                scanf(" %c", &input);
                TreeNode* foundNode = searchNode(root, input);
                if (foundNode != NULL)
                    printf("찾은 문자는: %c\n", foundNode->data);
                else
                    printf("찾는 키가 없습니다! 문자를 찾지 못했습니다.\n");
                break;
            case 5:
                exit(0);
            default:
                printf("잘못된 입력입니다. 다시 입력하세요.\n");
        }
    }

    return 0;
}
