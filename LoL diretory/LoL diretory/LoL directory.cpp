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
struct Node_SL
{
    Champion data;
    Node_SL* next;
}*head_sl = NULL;

struct Node_DL
{
    Champion data;
    Node_DL* next;
    Node_DL* prev;
}*head_dl = NULL;

// BT 구조체
struct BTNode {
    Champion data;
    BTNode* left, * right;
} *root_bt = NULL;

// --------- 파일 읽기 (SL 삽입) ----------
void loadFileToSL() {
    FILE* fp = fopen("loldi.txt", "r");
    if (!fp) {
        cout << "파일 열기 실패\n";
        return;
    }

    Champion temp;
    while (fscanf(fp, "%s %s %d %d %d", temp.position, temp.name, &temp.hp, &temp.atk, &temp.def) == 5) {
        BTNode* newbtnode = new BTNode{ temp,nullptr,nullptr };
        if (!root_bt) {
            root_bt = newbtnode;
        }
        else {
            BTNode* curnode = root_bt;
            while (true)
            {
                int temp = strcmp(curnode->data.name, newbtnode->data.name);
                if (temp < 0) { 
                    if (curnode->left == nullptr) {
                        curnode->left = newbtnode;
                        break;
                    }
                    else {
                        curnode = curnode->left;
                    }
                }
                else { 
                    if (curnode->right == nullptr) {
                        curnode->right = newbtnode;
                        break;
                    }
                    else {
                        curnode = curnode->right;
                    }
                }
            }
        }
    }

    fclose(fp);
}

void initialsetting() {
    Champion temp;
    FILE* fin = fopen("loldi.txt", "r");
    Node_SL* tail_sl = nullptr;
    if (!fin) {
        cout << "파일 열기 실패\n";
        return;
    }
    while (fscanf(fin, "%s %s %d %d %d", temp.position, temp.name, &temp.hp, &temp.atk, &temp.def) == 5){
        Node_SL* newNode_SL = new Node_SL{ temp, nullptr };
        if (!head_sl) {
            newNode_SL->next = newNode_SL;
            head_sl = newNode_SL;
            tail_sl = newNode_SL;
        }
        else {
            tail_sl->next = newNode_SL;
            newNode_SL->next = head_sl;
            tail_sl = newNode_SL;
        }
        Node_DL* newNode_DL = new Node_DL{ temp, nullptr, nullptr };
        if (!head_dl) {
            newNode_DL->next = newNode_DL;
            newNode_DL->prev = newNode_DL;
            head_dl = newNode_DL;
        }
        else {
            Node_DL* tail = head_dl->prev;
            tail->next = newNode_DL;
            newNode_DL->prev = tail;
            newNode_DL->next = head_dl;
            head_dl->prev = newNode_DL;
        }
    }
    fclose(fin);
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


void sorthp() {
    if (!head_dl || head_dl->next == head_dl) {
        return;
    }

    Node_DL* sorted = nullptr; // ���ĵȰ��� ��尪
    Node_DL* cur = head_dl;       // ���簪

    do {
        Node_DL* next = cur->next;
        if (!sorted) {
            cur->next = cur;
            cur->prev = cur;
            sorted = cur;
        }                   // ���� ó������
        else if (cur->data.hp > sorted->data.hp) {
            Node_DL* tail = sorted->prev;


            cur->next = sorted;
            cur->prev = tail;
            tail->next = cur;
            sorted->prev = cur;
            sorted = cur;

        }
        else {
            Node_DL* temp = sorted;
            while (temp->next != sorted && temp->next->data.hp >= cur->data.hp)
                temp = temp->next;
            cur->next = temp->next;
            cur->prev = temp;
            temp->next->prev = cur;
            temp->next = cur;
        }
        cur = next;
    } while (cur != head_dl);

    head_dl = sorted;
    cout << "���� �Ϸ�.\n";
}
// --------- BT 출력 ----------
// 전위
void printpreorderBT(BTNode* node) {
    if (!node) return;
    printf("%s %s %d %d %d\n", node->data.position, node->data.name, node->data.hp, node->data.atk, node->data.def);
    printpreorderBT(node->left);
    printpreorderBT(node->right);
}
// 중위
void printinorderBT(BTNode* node) {
    if (!node) return;
    printinorderBT(node->left);
    printf("%s %s %d %d %d\n", node->data.position, node->data.name, node->data.hp, node->data.atk, node->data.def);
    printinorderBT(node->right);
}
// 후위
void printpostorderBT(BTNode* node) {
    if (!node) return;
    printpostorderBT(node->left);
    printpostorderBT(node->right);
    printf("%s %s %d %d %d\n", node->data.position, node->data.name, node->data.hp, node->data.atk, node->data.def);
}

void printall(Node_DL* node = head_dl) {
    if (!node) return;
    printf("%s %s %d %d %d\n", node->data.position, node->data.name, node->data.hp, node->data.atk, node->data.def);
    if (node->next == head_dl) return;
    printall(node->next);
}
// --------- 메인 함수 ----------
int main() {
    loadFileToSL();
    initialsetting();
    int cho;
    while (true) {
        cout << "===== 메뉴 =====\n";
        cout << "1. SearchByName_BT\n";
        cout << "2. Insert_BT\n";
        cout << "3. Delete_BT\n";
        cout << "4. PrintAll_BT\n";
        cout << "0. 종료\n";
        cout << "==============\n";
        cin >> cho;

        char name[20];
        Champion temp;

        switch (cho) {
        case 1:
        {
            cout << "이름 입력: ";
            cin >> name;
            searchBT(name);
        }
            break;
        case 2:
        {
            cout << "포지션 이름 체력 공격 방어 입력: ";
            scanf("%s %s %d %d %d", temp.position, temp.name, &temp.hp, &temp.atk, &temp.def);
            auto start = high_resolution_clock::now();
            insertBT(temp);
            auto end = high_resolution_clock::now();
            cout << "Insert_BT: " << duration_cast<milliseconds>(end - start).count() << "ms\n";
            cout << "변환 완료\n";
        }
            break;
        case 3:
        {
            cout << "삭제할 이름 입력: ";
            cin >> name;

            auto start = high_resolution_clock::now();
            root_bt = deleteBT(root_bt, name);
            auto end = high_resolution_clock::now();
            cout << "Delete_BT: " << duration_cast<milliseconds>(end - start).count() << "ms\n";
        }
            break;
        case 4:
        {
            auto start = high_resolution_clock::now();
            printinorderBT(root_bt);
            auto end = high_resolution_clock::now();
            cout << "printall_BT: " << duration_cast<milliseconds>(end - start).count() << "ms\n";
            printall();
        }
            break;
        case 0:
        {
            sorthp();
        }
            break;
        default:
            cout << "잘못된 선택입니다.\n";
        }
    }

    return 0;
}