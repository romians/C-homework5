#include <stdio.h>
#include <stdlib.h>

// 이진 탐색 트리 노드를 나타내는 구조체 정의
struct TreeNode {
    int data;
    struct TreeNode* left;
    struct TreeNode* right;
};

// 새로운 노드를 생성하는 함수
struct TreeNode* newNode(int data) {
    struct TreeNode* node = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    node->data = data;
    node->left = NULL;
    node->right = NULL;
    return node;
}

// 이진 탐색 트리에 노드를 추가하는 함수 (재귀)
struct TreeNode* insertNode(struct TreeNode* root, int data) {
    if (root == NULL) {
        return newNode(data);
    }

    if (data < root->data) {
        root->left = insertNode(root->left, data);
    } else if (data > root->data) {
        root->right = insertNode(root->right, data);
    }

    return root;
}

// 이진 탐색 트리에서 노드를 검색하는 함수 (반복)
struct TreeNode* searchNode(struct TreeNode* root, int data) {
    while (root != NULL && root->data != data) {
        if (data < root->data) {
            root = root->left;
        } else {
            root = root->right;
        }
    }
    return root;
}

// 이진 탐색 트리에서 가장 작은 노드를 찾는 함수
struct TreeNode* findMinNode(struct TreeNode* root) {
    while (root->left != NULL) {
        root = root->left;
    }
    return root;
}

// 이진 탐색 트리에서 노드를 삭제하는 함수 (재귀)
struct TreeNode* deleteNode(struct TreeNode* root, int data) {
    if (root == NULL) {
        return root;
    }

    if (data < root->data) {
        root->left = deleteNode(root->left, data);
    } else if (data > root->data) {
        root->right = deleteNode(root->right, data);
    } else {
        // 삭제할 노드를 찾은 경우
        if (root->left == NULL) {
            struct TreeNode* temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            struct TreeNode* temp = root->left;
            free(root);
            return temp;
        }

        // 두 개의 자식 노드가 있는 경우
        struct TreeNode* temp = findMinNode(root->right);
        root->data = temp->data;
        root->right = deleteNode(root->right, temp->data);
    }
    return root;
}

// 이진 탐색 트리를 중위 순회로 출력하는 함수 (재귀)
void inorderTraversal(struct TreeNode* root) {
    if (root != NULL) {
        inorderTraversal(root->left);
        printf("%d ", root->data);
        inorderTraversal(root->right);
    }
}

int main() {
    struct TreeNode* root = NULL;
    char choice;
    int data;

    while (1) {
        printf("\n메뉴 선택 (s: 검색, i: 추가, d: 삭제, t: 중위 순회, I: 추가 반복, D: 삭제 반복, q: 종료): ");
        scanf(" %c", &choice);

        if (choice == 'q') {
            break;
        }

        switch (choice) {
            case 's':
                printf("검색할 값을 입력하세요: ");
                scanf("%d", &data);
                if (searchNode(root, data) != NULL) {
                    printf("%d를 찾았습니다.\n", data);
                } else {
                    printf("%d를 찾지 못했습니다.\n", data);
                }
                break;

            case 'i':
                printf("추가할 값을 입력하세요: ");
                scanf("%d", &data);
                root = insertNode(root, data);
                break;

            case 'd':
                printf("삭제할 값을 입력하세요: ");
                scanf("%d", &data);
                root = deleteNode(root, data);
                break;

            case 't':
                printf("중위 순회 결과: ");
                inorderTraversal(root);
                printf("\n");
                break;

            case 'I':
                printf("반복적으로 추가할 값을 입력하세요 (종료하려면 0 입력): ");
                while (1) {
                    scanf("%d", &data);
                    if (data == 0) {
                        break;
                    }
                    root = insertNode(root, data);
                }
                break;

            case 'D':
                printf("반복적으로 삭제할 값을 입력하세요 (종료하려면 0 입력): ");
                while (1) {
                    scanf("%d", &data);
                    if (data == 0) {
                        break;
                    }
                    root = deleteNode(root, data);
                }
                break;

            default:
                printf("잘못된 메뉴 선택입니다.\n");
        }
    }

    // 프로그램 종료 시 메모리 해제
    // (실제 프로덕션 코드에서는 더 신경을 써서 메모리 관리해야 합니다.)
    free(root);

    return 0;
}