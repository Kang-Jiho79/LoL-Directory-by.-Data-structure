#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
using namespace std;

struct lol {
    char name[30];
    int hp;
    int mp;
    int speed;
    int range;
    char position[10];
};

struct Node {
    lol data;
    Node* next;
};

Node* head = nullptr;
bool isSorted = false;

void say(const lol& champ) {
    cout << champ.name << endl;
    cout << "ü�� : " << champ.hp << endl;
    cout << "���� : " << champ.mp << endl;
    cout << "�ӵ� : " << champ.speed << endl;
    cout << "��Ÿ� : " << champ.range << endl;
    cout << "�� ������ : " << champ.position << endl;
}

void insert() {
    lol temp;
    cout << "�̸� : ";
    getchar();  // ���� ����
    scanf("%[^\n]s", temp.name);
    getchar();  // �� ����
    cout << "ü�� ���� �ӵ� ��Ÿ� ��������(top, jungle, mid, bottom, support) : ";
    if (!(cin >> temp.hp >> temp.mp >> temp.speed >> temp.range >> temp.position)) {
        cout << "�Է� ����\n"; cin.clear(); cin.ignore(1000, '\n'); return;
    }

    if (strlen(temp.name) > 20 || temp.hp <= 0 || temp.speed <= 0 || temp.range <= 0 ||
        !(strcmp(temp.position, "top") == 0 || strcmp(temp.position, "jungle") == 0 ||
            strcmp(temp.position, "mid") == 0 || strcmp(temp.position, "bottom") == 0 ||
            strcmp(temp.position, "support") == 0)) {
        cout << "�Է� ���� ������\n";
        return;
    }

    Node* newNode = new Node{ temp, nullptr };

    if (!head) {
        newNode->next = newNode;
        head = newNode;
    }
    else if (isSorted && temp.hp > head->data.hp) {
        Node* tail = head;
        while (tail->next != head)
            tail = tail->next;
        newNode->next = head;
        head = newNode;
        tail->next = head;
    }
    else if (isSorted) {
        Node* cur = head;
        while (cur->next != head && cur->next->data.hp >= temp.hp)
            cur = cur->next;
        newNode->next = cur->next;
        cur->next = newNode;
    }
    else {
        Node* tail = head;
        while (tail->next != head)
            tail = tail->next;
        tail->next = newNode;
        newNode->next = head;
    }

    cout << "�߰��Ǿ����ϴ�.\n";
}

void deletenameRecursive(Node*& cur, char name[]) {
    if (!head) {
        cout << "è�Ǿ��� �����ϴ�.\n";
        return;
    }

    Node* prev = nullptr;
    Node* node = head;

    do {
        if (strcmp(node->data.name, name) == 0) {
            if (node == head) {
                Node* tail = head;
                while (tail->next != head)
                    tail = tail->next;

                if (head == head->next) {
                    delete head;
                    head = nullptr;
                }
                else {
                    Node* temp = head;
                    head = head->next;
                    tail->next = head;
                    delete temp;
                }
            }
            else {
                prev->next = node->next;
                delete node;
            }
            cout << "è�Ǿ��� �����Ǿ����ϴ�.\n";
            return;
        }
        prev = node;
        node = node->next;
    } while (node != head);

    cout << "�ش� è�Ǿ��� �����ϴ�.\n";
}

void deleteallRecursive(Node*& node, char position[]) {
    if (!head) return;

    Node* prev = nullptr;
    Node* cur = head;
    bool deleted = false;

    do {
        if (strcmp(cur->data.position, position) == 0) {
            if (cur == head) {
                Node* tail = head;
                while (tail->next != head)
                    tail = tail->next;

                if (head == head->next) {
                    delete head;
                    head = nullptr;
                    break;
                }
                else {
                    Node* temp = head;
                    head = head->next;
                    tail->next = head;
                    cur = head;
                    delete temp;
                }
            }
            else {
                prev->next = cur->next;
                delete cur;
                cur = prev->next;
            }
            deleted = true;
        }
        else {
            prev = cur;
            cur = cur->next;
        }
    } while (cur != head);

    if (deleted)
        cout << "�������� è�Ǿ��� �����Ǿ����ϴ�.\n";
    else
        cout << "������ �������� �����ϴ�.\n";
}

void SearchRecursive(Node* node, char name[], bool found = false, Node* start = nullptr) {
    if (!node) return;
    if (!start) start = node;

    if (strcmp(node->data.name, name) == 0) {
        say(node->data);
        found = true;
    }

    if (node->next == start) {
        if (!found) cout << "�ش� �̸��� ���� è�Ǿ��� �����ϴ�.\n";
        return;
    }
    SearchRecursive(node->next, name, found, start);
}

void printAllRecursive(Node* node, Node* start = nullptr) {
    if (!node) return;
    if (!start) start = node;
    say(node->data);
    if (node->next == start) return;
    printAllRecursive(node->next, start);
}

void FindmaxhpRecursive(Node* node, bool findMax = true, int maxhp = 0, Node* start = nullptr) {
    static int maxFound = 0;
    if (!node) return;
    if (!start) start = node;

    if (findMax) {
        if (node->data.hp > maxFound)
            maxFound = node->data.hp;
        if (node->next == start)
            FindmaxhpRecursive(head, false, maxFound);
        else
            FindmaxhpRecursive(node->next, true, maxFound, start);
    }
    else {
        if (node->data.hp == maxhp)
            say(node->data);
        if (node->next == start) {
            maxFound = 0;
            return;
        }
        FindmaxhpRecursive(node->next, false, maxhp, start);
    }
}

void deleteAllNodes(Node* node) {
    if (!node) return;
    Node* cur = node->next;
    while (cur != node) {
        Node* temp = cur;
        cur = cur->next;
        delete temp;
    }
    delete node;
    head = nullptr;
}

void sorthp() {
    if (!head || head->next == head) {
        isSorted = true;
        return;
    }

    Node* sorted = nullptr;
    Node* cur = head;

    do {
        Node* next = cur->next;
        if (!sorted) {
            cur->next = cur;
            sorted = cur;
        }
        else if (cur->data.hp > sorted->data.hp) {
            Node* tail = sorted;
            while (tail->next != sorted)
                tail = tail->next;
            cur->next = sorted;
            sorted = cur;
            tail->next = sorted;
        }
        else {
            Node* temp = sorted;
            while (temp->next != sorted && temp->next->data.hp >= cur->data.hp)
                temp = temp->next;
            cur->next = temp->next;
            temp->next = cur;
        }
        cur = next;
    } while (cur != head);

    head = sorted;
    isSorted = true;
    cout << "���� �Ϸ�.\n";
}

void initialsetting_recursive(int i = 0) {
    if (i >= 22) return;

    lol temp;
    if (i == 0)
        cout << "�ʱ� �����Դϴ�. �ؽ�Ʈ ������ �����ؼ� �ٿ��־� �ּ���.\n";

    if (i != 0)
        getchar();

    if (scanf("%[^\t]s", temp.name) != 1) {
        cout << "�̸� �Է� ����, �ٽ� �õ��� �ּ���.\n";
        cin.clear(); cin.ignore(1000, '\n');
        initialsetting_recursive(i);
        return;
    }

    getchar();
    if (!(cin >> temp.hp >> temp.mp >> temp.speed >> temp.range >> temp.position)) {
        cout << "���� �Է� ����, �ٽ� �õ��� �ּ���.\n";
        cin.clear(); cin.ignore(1000, '\n');
        initialsetting_recursive(i);
        return;
    }

    if (strlen(temp.name) <= 20 && temp.hp > 0 && temp.mp >= 0 && temp.speed > 0 && temp.range > 0 &&
        (strcmp(temp.position, "top") == 0 || strcmp(temp.position, "jungle") == 0 ||
            strcmp(temp.position, "mid") == 0 || strcmp(temp.position, "bottom") == 0 ||
            strcmp(temp.position, "support") == 0)) {

        Node* newNode = new Node{ temp, nullptr };
        if (!head) {
            newNode->next = newNode;
            head = newNode;
        }
        else {
            Node* tail = head;
            while (tail->next != head)
                tail = tail->next;
            tail->next = newNode;
            newNode->next = head;
        }

        cout << "�߰��Ǿ����ϴ�.\n";
    }
    else {
        cout << "�Է� ���� ������\n";
    }

    initialsetting_recursive(i + 1);
}

int main() {
    int cho, last;
    initialsetting_recursive();
    while (true) {
        cout << "\n===== �޴� =====\n";
        cout << "1. Search  2. Insert  3. Delete  4. DeleteAll\n";
        cout << "5. PrintAll  6. FindMaxHp  7. SortHp  8. ����\n";
        cout << "==============\n";
        cin >> cho;

        switch (cho) {
        case 1: {
            char name[30];
            cout << "�̸� �Է�: ";
            cin.ignore();
            scanf("%[^\n]s", name);
            SearchRecursive(head, name);
            break;
        }
        case 2:
            insert();
            break;
        case 3: {
            char name[30];
            cout << "������ �̸� �Է�: ";
            cin.ignore();
            scanf("%[^\n]s", name);
            deletenameRecursive(head, name);
            break;
        }
        case 4: {
            char position[10];
            cout << "������ �Է�: ";
            cin >> position;
            deleteallRecursive(head, position);
            break;
        }
        case 5:
            printAllRecursive(head);
            break;
        case 6:
            FindmaxhpRecursive(head);
            break;
        case 7:
            sorthp();
            break;
        case 8:
            deleteAllNodes(head);
            cout << "���α׷� ����\n";
            return 0;
        default:
            cout << "�߸��� �����Դϴ�.\n";
        }
        while (true) {
            cout << "��� �����ϰڴٸ� 1 �׸��ϰڴٸ� 2 : " << endl;
            cin >> last;
            if (last == 1) {
                system("cls");
                break;
            }
            else if (last == 2) {
                return 0;
            }
            else {
                cout << "�ٽ� �Է��Ͻʽÿ�" << endl;
            }
        }
    }
}
