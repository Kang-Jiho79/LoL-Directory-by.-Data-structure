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
    Node* prev; // prev �߰�
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
    getchar();
    scanf("%[^\n]s", temp.name);
    getchar();
    cout << "ü�� ���� �ӵ� ��Ÿ� ��������(top, jungle, mid, bottom, support) : ";
    if (!(cin >> temp.hp >> temp.mp >> temp.speed >> temp.range >> temp.position)) {
        cout << "�Է� ����\n"; 
        cin.clear(); 
        cin.ignore(1000, '\n'); 
        return;
    }

    if (strlen(temp.name) > 20 || temp.hp <= 0 || temp.speed <= 0 || temp.range <= 0 ||
        !(strcmp(temp.position, "top") == 0 || strcmp(temp.position, "jungle") == 0 ||
            strcmp(temp.position, "mid") == 0 || strcmp(temp.position, "bottom") == 0 ||
            strcmp(temp.position, "support") == 0)) {
        cout << "�Է� ���� ������\n";
        return;
    }

    Node* newNode = new Node{ temp, nullptr, nullptr };

    if (!head) {
        newNode->next = newNode;
        newNode->prev = newNode;
        head = newNode;
    }
    else if (isSorted && temp.hp > head->data.hp) {
        Node* tail = head->prev;
        newNode->next = head;
        newNode->prev = tail;
        head->prev = newNode;
        tail->next = newNode;
        head = newNode;
    }
    else if (isSorted) {
        Node* cur = head;
        while (cur->next != head && cur->next->data.hp >= temp.hp)
            cur = cur->next;
        newNode->next = cur->next;
        newNode->prev = cur;
        cur->next->prev = newNode;
        cur->next = newNode;
    }
    else {
        Node* tail = head->prev;
        tail->next = newNode;
        newNode->prev = tail;
        newNode->next = head;
        head->prev = newNode;
    }

    cout << "�߰��Ǿ����ϴ�.\n";
}

void deletenameRecursive(char name[]) {
    if (!head) {
        cout << "è�Ǿ��� �����ϴ�.\n";
        return;
    }

    Node* node = head;
    do {
        if (strcmp(node->data.name, name) == 0) {
            if (node == head && node->next == head) {
                delete node;
                head = nullptr;
            }
            else {
                node->prev->next = node->next;
                node->next->prev = node->prev;
                if (node == head)
                    head = node->next;
                delete node;
            }
            cout << "è�Ǿ��� �����Ǿ����ϴ�.\n";
            return;
        }
        node = node->next;
    } while (node != head);

    cout << "�ش� è�Ǿ��� �����ϴ�.\n";
}

void deleteallRecursive(char position[]) {
    if (!head) return;

    Node* cur = head;
    bool deleted = false;
    do {
        Node* next = cur->next;
        if (strcmp(cur->data.position, position) == 0) {
            if (cur == head && cur->next == head) {
                delete cur;
                head = nullptr;
                deleted = true;
                break;
            }
            else {
                cur->prev->next = cur->next;
                cur->next->prev = cur->prev;
                if (cur == head)
                    head = cur->next;
                delete cur;
                deleted = true;
            }
        }
        cur = next;
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

void printAllRecursive(Node* node = head, Node* start = nullptr) {
    if (!node) return;
    if (!start) start = node;
    say(node->data);
    if (node->next == start) return;
    printAllRecursive(node->next, start);
}

void printAllback(Node* node = head->prev, Node* start = nullptr) {
    if (!node) return;
    if (!start) start = node;
    say(node->data);
    if (node->prev == start) return;
    printAllback(node->prev, start);
}

void FindmaxhpRecursive(Node* node = head, bool findMax = true, int maxhp = 0, Node* start = nullptr) {
    if (!node) return;
    if (!start) start = node;

    if (findMax) {
        if (node->data.hp > maxhp)
            maxhp = node->data.hp;
        if (node->next == start)
            FindmaxhpRecursive(head, false, maxhp);
        else
            FindmaxhpRecursive(node->next, true, maxhp, start);
    }
    else {
        if (node->data.hp == maxhp)
            say(node->data);
        if (node->next == start) {
            return;
        }
        FindmaxhpRecursive(node->next, false, maxhp, start);
    }
}

void deleteAllNodes(Node* node = head) {
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

    Node* sorted = nullptr; // ���ĵȰ��� ��尪
    Node* cur = head;       // ���簪

    do {
        Node* next = cur->next;
        if (!sorted) {
            cur->next = cur;
            cur->prev = cur;
            sorted = cur;
        }                   // ���� ó������
        else if (cur->data.hp > sorted->data.hp) {
            Node* tail = sorted->prev;
            cur->next = sorted;
            cur->prev = tail;
            tail->next = cur;
            sorted->prev = cur;
            sorted = cur;
        }
        else {
            Node* temp = sorted;
            while (temp->next != sorted && temp->next->data.hp >= cur->data.hp)
                temp = temp->next;
            cur->next = temp->next;
            cur->prev = temp;
            temp->next->prev = cur;
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

        Node* newNode = new Node{ temp, nullptr, nullptr };
        if (!head) {
            newNode->next = newNode;
            newNode->prev = newNode;
            head = newNode;
        }
        else {
            Node* tail = head->prev;
            tail->next = newNode;
            newNode->prev = tail;
            newNode->next = head;
            head->prev = newNode;
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
            deletenameRecursive(name);
            break;
        }
        case 4: {
            char position[10];
            cout << "������ �Է�: ";
            cin >> position;
            deleteallRecursive(position);
            break;
        }
        case 5: {
            int print;
            cout << "ó������ ����ϱ� ���Ѵٸ� 1\n���������� ����ϱ� ���Ѵٸ� 2\n";
            cin >> print;
            switch (print)
            {
            case 1:
                printAllRecursive();
                break;
            case 2:
                printAllback();
                break;
            default:
                break;
            }

        }
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
                cout << "�ٽ� �Է��Ͻʽÿ�\n";
            }
        }
    }
}