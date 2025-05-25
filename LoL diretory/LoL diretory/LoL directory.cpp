#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <chrono>
using namespace std;
using namespace chrono;

#define size 20000000

struct lol {
    char position[10];
    char name[30];
    int hp;
    int attack;
    int depend;
};

struct Node_SL {
    lol data;
    Node_SL* next;
};

struct Node_DL {
    lol data;
    Node_DL* next;
    Node_DL* prev; // prev 추가
};

Node_SL* head_sl = nullptr;
Node_DL* head_dl = nullptr;
bool isSorted = false;

void say(const lol& champ) {
    cout << champ.position << " " << champ.name << " " << champ.hp << " " << champ.attack << " " << champ.depend << endl;
}

void printAll_sl() {
    Node_SL* node_sl = head_sl;
    for (int i = 0; i < size; ++i) {
        if (i % 100000 == 0)
            say(node_sl->data);
        node_sl = node_sl->next;
    }
}

void printAll_dl() {
    Node_DL* node_dl = head_dl;
    for (int i = 0; i < size; ++i) {
        if (i % 100000 == 0)
            say(node_dl->data);
        node_dl = node_dl->next;
    }
}

void Findmaxhp_sl() {
    Node_SL* node_sl = head_sl;
    int maxhp = 0;
    while (node_sl->next != head_sl) {
        if (node_sl->data.hp > maxhp)
            maxhp = node_sl->data.hp;
        node_sl = node_sl->next;
    }
    node_sl = head_sl;
    while (node_sl->next != head_sl) {
        if (node_sl->data.hp == maxhp)
            say(node_sl->data);
        node_sl = node_sl->next;
    }
}

void Findmaxhp_dl() {
    Node_DL* node_dl = head_dl;
    int maxhp = 0;
    while (node_dl->next != head_dl) {
        if (node_dl->data.hp > maxhp)
            maxhp = node_dl->data.hp;
        node_dl = node_dl->next;
    }
    node_dl = head_dl;
    while (node_dl->next != head_dl) {
        if (node_dl->data.hp == maxhp)
            say(node_dl->data);
        node_dl = node_dl->next;
    }
}

void deleteAllNode(Node_SL* node_sl = head_sl, Node_DL* node_dl = head_dl) {
    if (!node_sl) return;
    if (!node_dl) return;
    Node_SL* cur_sl = node_sl->next;
    Node_DL* cur_dl = node_dl->next;
    while (cur_sl != node_sl) {
        Node_SL* temp_sl = cur_sl;
        Node_DL* temp_dl = cur_dl;
        cur_sl = cur_sl->next;
        cur_dl = cur_dl->next;
        delete temp_sl;
        delete temp_dl;
    }
    delete node_sl;
    delete node_dl;
    head_sl = nullptr;
    head_dl = nullptr;
}

void initialsetting() {
    lol temp;
    FILE* fin = fopen("LOLDic.txt", "r");
    Node_SL* tail_sl = nullptr;
    if (!fin) {
        cout << "파일을 찾을 수 없습니다." << endl;
        return;
    }
     for (int i = 0; i < 20000000; ++i) {
        fscanf(fin, "%s %s %d %d %d", temp.position, temp.name, &temp.hp, &temp.attack, &temp.depend);
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

Node_SL* breakCircular_sl(Node_SL* head) {
    if (!head || head->next == head) return head;
    Node_SL* tail = head;
    while (tail->next != head)
        tail = tail->next;
    tail->next = nullptr;
    return head;
}

Node_SL* bottomUpSort_sl(Node_SL* head) {
    if (!head || !head->next) return head;

    head = breakCircular_sl(head);  // 원형 끊기

    int listSize = 1;
    Node_SL dummy{ {}, head };

    while (true) {
        Node_SL* cur = dummy.next;
        Node_SL* tail = &dummy;
        int merges = 0;

        while (cur) {
            merges++;

            Node_SL* left = cur;
            Node_SL* right = nullptr;
            Node_SL* next = nullptr;

            // left 리스트 추출
            int leftSize = 0;
            for (leftSize = 0; leftSize < listSize && cur; ++leftSize)
                cur = cur->next;

            // right 리스트 추출
            right = cur;
            int rightSize = 0;
            for (rightSize = 0; rightSize < listSize && cur; ++rightSize)
                cur = cur->next;

            // next = 남은 부분
            next = cur;

            // 병합
            int l = leftSize, r = rightSize;
            while (l > 0 || r > 0) {
                if (l == 0) {
                    tail->next = right;
                    right = right->next;
                    r--;
                }
                else if (r == 0 || (left->data.hp >= right->data.hp)) {
                    tail->next = left;
                    left = left->next;
                    l--;
                }
                else {
                    tail->next = right;
                    right = right->next;
                    r--;
                }
                tail = tail->next;
            }

            tail->next = next;
        }

        if (merges <= 1)
            break;

        listSize *= 2;
    }

    // 원형 복원
    Node_SL* last = dummy.next;
    while (last->next)
        last = last->next;
    last->next = dummy.next;

    return dummy.next;
}

Node_DL* breakCircular_dl(Node_DL* head) {
    if (!head || head->next == head) return head;
    Node_DL* tail = head->prev;
    tail->next = nullptr;
    head->prev = nullptr;
    return head;
}

Node_DL* bottomUpSort_dl(Node_DL* head) {
    if (!head || !head->next) return head;

    head = breakCircular_dl(head);

    int listSize = 1;
    Node_DL dummy{ {}, head, nullptr };

    while (true) {
        Node_DL* cur = dummy.next;
        Node_DL* tail = &dummy;
        int merges = 0;

        while (cur) {
            merges++;

            Node_DL* left = cur;
            Node_DL* right = nullptr;
            Node_DL* next = nullptr;

            int leftSize = 0;
            for (; leftSize < listSize && cur; ++leftSize)
                cur = cur->next;

            right = cur;

            int rightSize = 0;
            for (; rightSize < listSize && cur; ++rightSize)
                cur = cur->next;

            next = cur;

            // 병합 시작
            int l = leftSize, r = rightSize;
            while (l > 0 || r > 0) {
                if (l == 0) {
                    tail->next = right;
                    right->prev = tail;
                    right = right->next;
                    r--;
                }
                else if (r == 0 || (left->data.hp >= right->data.hp)) {
                    tail->next = left;
                    left->prev = tail;
                    left = left->next;
                    l--;
                }
                else {
                    tail->next = right;
                    right->prev = tail;
                    right = right->next;
                    r--;
                }
                tail = tail->next;
            }

            tail->next = next;
            if (next) next->prev = tail;
        }

        if (merges <= 1)
            break;

        listSize *= 2;
    }

    // 원형 리스트 복원
    Node_DL* last = dummy.next;
    while (last->next)
        last = last->next;

    dummy.next->prev = last;
    last->next = dummy.next;

    return dummy.next;
}

int main() {
    int cho, last;
    initialsetting();
    while (true) {
        cout << "===== 메뉴 =====\n";
        cout << "1. PrintAll  2. SortByHp  3. FindMaxHp\n";
        cout << "==============\n";
        cin >> cho;

        switch (cho) {
        case 1: {
            auto start = high_resolution_clock::now();
            printAll_sl();
            auto end = high_resolution_clock::now();
            auto duration_sl = duration_cast<milliseconds>(end - start);
            start = high_resolution_clock::now();
            printAll_dl();
            end = high_resolution_clock::now();
            auto duration_dl = duration_cast<milliseconds>(end - start);
            cout << "SL : " << duration_sl.count() << "ms, DL : " << duration_dl.count() << "ms" << endl;
            break;
        }
        case 2: {
            auto start = high_resolution_clock::now();
            head_sl = bottomUpSort_sl(head_sl);
            auto end = high_resolution_clock::now();
            auto duration_sl = duration_cast<milliseconds>(end - start);
            start = high_resolution_clock::now();
            head_dl = bottomUpSort_dl(head_dl);
            end = high_resolution_clock::now();
            auto duration_dl = duration_cast<milliseconds>(end - start);
            cout << "SL : " << duration_sl.count() << "ms, DL : " << duration_dl.count() << "ms" << endl;
            break;
        }
        case 3: {
            auto start = high_resolution_clock::now();
            Findmaxhp_sl();
            auto end = high_resolution_clock::now();
            auto duration_sl = duration_cast<milliseconds>(end - start);
            start = high_resolution_clock::now();
            Findmaxhp_dl();
            end = high_resolution_clock::now();
            auto duration_dl = duration_cast<milliseconds>(end - start);
            cout << "SL : " << duration_sl.count() << "ms, DL : " << duration_dl.count() << "ms" << endl;
            break;
        }
        default:
            cout << "잘못된 선택입니다.\n";
        }
        system("pause");
        system("cls");
    }
}