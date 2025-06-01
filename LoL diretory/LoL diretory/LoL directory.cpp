#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <chrono>
#include <cstring>
#include <cstdlib>
using namespace std;
using namespace chrono;

#define MAX 20000000 // 2000만 개 충분히 담기도록

struct Champion {
    char position[10];
    char name[20];
    int hp, atk, def;
};

// SL 구조체
struct SLNode {
    Champion data;
    SLNode* next;
} *head_sl = NULL;

// BT 구조체
struct BTNode {
    Champion data;
    BTNode* left, * right;
} *root_bt = NULL;

BTNode* sortedArr_BT[MAX];
int nodeCount = 0;

// --------- 파일 읽기 (SL 삽입) ----------
void loadFileToSL() {
    FILE* fp = fopen("LOLDic.txt", "r");
    if (!fp) {
        cout << "파일 열기 실패\n";
        return;
    }

    Champion temp;
    while (fscanf(fp, "%s %s %d %d %d", temp.position, temp.name, &temp.hp, &temp.atk, &temp.def) == 5) {
        SLNode* node = new SLNode{ temp, NULL };
        node->next = head_sl;
        head_sl = node;
    }

    fclose(fp);
}

// --------- SL → BT 변환 ----------
void insertBT(Champion data);
void convertSLtoBT() {
    root_bt = NULL; // 기존 트리 초기화
    SLNode* curr = head_sl;
    while (curr) {
        insertBT(curr->data);
        curr = curr->next;
    }
}

// --------- BT 삽입 ----------
void insertBT(Champion data) {
    BTNode** cur = &root_bt;
    while (*cur) {
        if (strcmp(data.name, (*cur)->data.name) < 0)
            cur = &((*cur)->left);
        else
            cur = &((*cur)->right);
    }
    *cur = new BTNode{ data, NULL, NULL };
}

// --------- BT 탐색 ----------
void searchBT(const char* name) {
    BTNode* cur = root_bt;
    while (cur) {
        int cmp = strcmp(name, cur->data.name);
        if (cmp == 0) {
            printf("찾음: %s %s %d %d %d\n", cur->data.position, cur->data.name, cur->data.hp, cur->data.atk, cur->data.def);
            return;
        }
        cur = (cmp < 0) ? cur->left : cur->right;
    }
    printf("찾을 수 없음: %s\n", name);
}

// --------- BT 삭제 ----------
BTNode* deleteBT(BTNode* root, const char* name) {
    if (!root) return NULL;
    int cmp = strcmp(name, root->data.name);
    if (cmp < 0) root->left = deleteBT(root->left, name);
    else if (cmp > 0) root->right = deleteBT(root->right, name);
    else {
        if (!root->left) {
            BTNode* temp = root->right;
            delete root;
            return temp;
        }
        else if (!root->right) {
            BTNode* temp = root->left;
            delete root;
            return temp;
        }
        BTNode* succ = root->right;
        while (succ->left) succ = succ->left;
        root->data = succ->data;
        root->right = deleteBT(root->right, succ->data.name);
    }
    return root;
}

// --------- BT 출력 (중위순회) ----------
void printBT(BTNode* node, int i = 0) {
    if (!node) return;
    printBT(node->left, i + 1);
    if (i % 10 == 0)
        printf("%s %s %d %d %d\n", node->data.position, node->data.name, node->data.hp, node->data.atk, node->data.def);
    printBT(node->right, i + 1);
}

// --------- SL 이름 기준 정렬 ----------
SLNode* mergeSortedLists(SLNode* a, SLNode* b) {
    if (!a) return b;
    if (!b) return a;
    SLNode* result = NULL;
    if (strcmp(a->data.name, b->data.name) < 0) {
        result = a;
        result->next = mergeSortedLists(a->next, b);
    }
    else {
        result = b;
        result->next = mergeSortedLists(a, b->next);
    }
    return result;
}

void splitList(SLNode* source, SLNode** front, SLNode** back) {
    SLNode* slow = source;
    SLNode* fast = source->next;
    while (fast) {
        fast = fast->next;
        if (fast) {
            slow = slow->next;
            fast = fast->next;
        }
    }
    *front = source;
    *back = slow->next;
    slow->next = NULL;
}

SLNode* mergeSort(SLNode* head) {
    if (!head || !head->next) return head;
    SLNode* a, * b;
    splitList(head, &a, &b);
    return mergeSortedLists(mergeSort(a), mergeSort(b));
}

// --------- BT 정렬 관련 함수들 ----------
void storeInorderArray_BT(BTNode* root) {
    if (!root) return;
    storeInorderArray_BT(root->left);
    sortedArr_BT[nodeCount++] = root;
    storeInorderArray_BT(root->right);
}

void merge_BT(BTNode** arr, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    BTNode** L = new BTNode * [n1];
    BTNode** R = new BTNode * [n2];

    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (strcmp(L[i]->data.name, R[j]->data.name) <= 0)
            arr[k++] = L[i++];
        else
            arr[k++] = R[j++];
    }

    while (i < n1)
        arr[k++] = L[i++];
    while (j < n2)
        arr[k++] = R[j++];

    delete[] L;
    delete[] R;
}

void mergeSort_BT(BTNode** arr, int left, int right) {
    if (left < right) {
        int mid = (left + right) / 2;
        mergeSort_BT(arr, left, mid);
        mergeSort_BT(arr, mid + 1, right);
        merge_BT(arr, left, mid, right);
    }
}

BTNode* buildBalancedTree_BT(int start, int end) {
    if (start > end) return NULL;
    int mid = (start + end) / 2;
    BTNode* root = sortedArr_BT[mid];
    root->left = buildBalancedTree_BT(start, mid - 1);
    root->right = buildBalancedTree_BT(mid + 1, end);
    return root;
}

// --------- 정렬 함수 (SL/BT) ----------
void SortByName_SL() {
    auto start = high_resolution_clock::now();
    head_sl = mergeSort(head_sl);
    auto end = high_resolution_clock::now();
    cout << "SortByName_SL: " << duration_cast<milliseconds>(end - start).count() << "ms\n";
}

void SortByName_BT() {
    nodeCount = 0;
    storeInorderArray_BT(root_bt);
    mergeSort_BT(sortedArr_BT, 0, nodeCount - 1);
    root_bt = buildBalancedTree_BT(0, nodeCount - 1);
}

// --------- 메인 함수 ----------
int main() {
    loadFileToSL();

    int cho;
    while (true) {
        cout << "===== 메뉴 =====\n";
        cout << "1. SortByName_SL\n";
        cout << "2. SL -> BT 변환\n";
        cout << "3. SearchByName_BT\n";
        cout << "4. Insert_BT\n";
        cout << "5. Delete_BT\n";
        cout << "6. PrintAll_BT\n";
        cout << "7. SortByName_BT\n";
        cout << "0. 종료\n";
        cout << "==============\n";
        cin >> cho;

        char name[20];
        Champion temp;

        switch (cho) {
        case 1:
            SortByName_SL();
            break;
        case 2:
            convertSLtoBT();
            cout << "변환 완료\n";
            break;
        case 3:
            cout << "이름 입력: ";
            cin >> name;
            searchBT(name);
            break;
        case 4:
            cout << "포지션 이름 체력 공격 방어 입력: ";
            scanf("%s %s %d %d %d", temp.position, temp.name, &temp.hp, &temp.atk, &temp.def);
            {
                auto start = high_resolution_clock::now();
                insertBT(temp);
                auto end = high_resolution_clock::now();
                cout << "Insert_BT: " << duration_cast<milliseconds>(end - start).count() << "ms\n";
            }
            break;
        case 5:
            cout << "삭제할 이름 입력: ";
            cin >> name;
            {
                auto start = high_resolution_clock::now();
                root_bt = deleteBT(root_bt, name);
                auto end = high_resolution_clock::now();
                cout << "Delete_BT: " << duration_cast<milliseconds>(end - start).count() << "ms\n";
            }
            break;
        case 6:
            printBT(root_bt);
            break;
        case 7:
        {
            auto start = high_resolution_clock::now();
            SortByName_BT();
            auto end = high_resolution_clock::now();
            cout << "SortByName_BT: " << duration_cast<milliseconds>(end - start).count() << "ms\n";
        }
        break;
        case 0:
            return 0;
        default:
            cout << "잘못된 선택입니다.\n";
        }
    }

    return 0;
}