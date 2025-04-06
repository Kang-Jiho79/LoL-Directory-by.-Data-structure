#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string.h>
using namespace std;

struct lol {
public:
    char name[30] = "\0";
    int hp = 0;
    int mp = 0;
    int speed = 0;
    int range = 0;
    char position[10] = "\0";
};

lol champ[100];
int champcount = 0;

void say(int i) {
    cout << champ[i].name << endl
        << "ü�� : " << champ[i].hp << endl
        << "���� : " << champ[i].mp << endl
        << "�ӵ� : " << champ[i].speed << endl
        << "��Ÿ� : " << champ[i].range << endl
        << "�� ������ : " << champ[i].position << endl;
}

void SearchRecursive(int i, char name[], bool found = false) {
    if (i >= champcount) {
        if (!found)
            cout << "�ش� �̸��� ���� è�Ǿ��� �����ϴ�." << endl;
        return;
    }
    if (strcmp(champ[i].name, name) == 0) {
        say(i);
        found = true;
    }
    SearchRecursive(i + 1, name, found);
}

void insert() {
    char name[30];
    int hp, mp, speed, range;
    char position[10];

    cout << "�̸�(����, �ִ� 20��) ü�� ���� �ӵ� ��Ÿ� ��������(top, jungle, mid, bottom, support) : ";
    cin.ignore();
    scanf("%[^	]s", name);
    if (!(cin >> hp >> mp >> speed >> range >> position)) {
        cout << "�Է� �����Դϴ�." << endl;
        cin.clear(); cin.ignore(1000, '\n');
        return;
    }

    if (strlen(name) <= 20 && hp > 0 && mp >= 0 && speed > 0 && range > 0) {
        if (strcmp(position, "top") == 0 || strcmp(position, "jungle") == 0 || strcmp(position, "mid") == 0 || strcmp(position, "bottom") == 0 || strcmp(position, "support") == 0) {
            for (int i = 0; i < 100; i++) {
                if (champ[i].name[0] == '\0') {
                    strncpy(champ[i].name, name, sizeof(champ[i].name));
                    champ[i].hp = hp;
                    champ[i].mp = mp;
                    champ[i].speed = speed;
                    champ[i].range = range;
                    strncpy(champ[i].position, position, sizeof(champ[i].position));
                    champcount++;
                    cout << champ[i].position << endl;
                    cout << "�߰��Ǿ����ϴ�." << endl;
                    return;
                }
            }
            cout << "���� ������ �����ϴ�." << endl;
        }
        else {
            cout << "�߸��Է��ϼ̽��ϴ�." << endl;
        }
    }
    else {
        cout << "�߸��Է��ϼ̽��ϴ�." << endl;
    }
}

void deletenameRecursive(int i, char name[]) {
    if (i >= champcount) {
        cout << "�ش� è�Ǿ��� �����ϴ�." << endl;
        return;
    }
    if (strcmp(champ[i].name, name) == 0) {
        champ[i].name[0] = '\0';
        champ[i].hp = champ[i].mp = champ[i].speed = champ[i].range = 0;
        champ[i].position[0] = '\0';
        champcount--;
        cout << "è�Ǿ��� �����Ǿ����ϴ�." << endl;
        return;
    }
    deletenameRecursive(i + 1, name);
}

void deleteallRecursive(int i, char position[]) {
    if (i >= champcount) {
        cout << "�ش� �������� è�Ǿ��� �����Ǿ����ϴ�" << endl;
        return;
    }
    if (strcmp(champ[i].position, position) == 0) {
        champ[i].name[0] = '\0';
        champ[i].hp = champ[i].mp = champ[i].speed = champ[i].range = 0;
        champ[i].position[0] = '\0';
        champcount--;
    }
    deleteallRecursive(i + 1, position);
}

void FindmaxhpRecursive(int i = 0, int maxhp = 0) {
    if (i >= champcount) {
        for (int j = 0; j < champcount; j++) {
            if (champ[j].hp == maxhp)
                say(j);
        }
        return;
    }
    if (champ[i].hp > maxhp)
        maxhp = champ[i].hp;
    FindmaxhpRecursive(i + 1, maxhp);
}

void sortbyhpRecursive(int i = 0) {
    if (i >= champcount - 1) {
        cout << "ü�� �������� ���ĿϷ�" << endl;
        return;
    }
    for (int j = i + 1; j < champcount; j++) {
        if (champ[i].hp < champ[j].hp) {
            lol temp = champ[i];
            champ[i] = champ[j];
            champ[j] = temp;
        }
    }
    sortbyhpRecursive(i + 1);
}

void printAllRecursive(int i = 0) {
    if (i >= champcount) return;
    say(i);
    printAllRecursive(i + 1);
}

void initalsetting_recursive(int i = 0) {
    if (i >= 22) return;

    char name[30];
    int hp, mp, speed, range;
    char position[10];

    if (i == 0)
        cout << "�ʱ� �����Դϴ�. text ���� ��ü�� �����ؼ� �ٿ��־� �ּ���." << endl;

    if (i != 0)
        getchar();

    if (scanf("%[^\t]s", name) != 1) {
        cout << "�̸� �Է� ����, �ٽ� �õ��� �ּ���." << endl;
        cin.clear(); cin.ignore(1000, '\n');
        initalsetting_recursive(i);
        return;
    }

    if (!(cin >> hp >> mp >> speed >> range >> position)) {
        cout << "���� �Է� ����, �ٽ� �õ��� �ּ���." << endl;
        cin.clear(); cin.ignore(1000, '\n');
        initalsetting_recursive(i);
        return;
    }

    if (strlen(name) <= 20 && hp > 0 && mp >= 0 && speed > 0 && range > 0) {
        if (strcmp(position, "top") == 0 || strcmp(position, "jungle") == 0 || strcmp(position, "mid") == 0 || strcmp(position, "bottom") == 0 || strcmp(position, "support") == 0) {
            strncpy(champ[i].name, name, sizeof(champ[i].name));
            champ[i].hp = hp;
            champ[i].mp = mp;
            champ[i].speed = speed;
            champ[i].range = range;
            strncpy(champ[i].position, position, sizeof(champ[i].position));
            champcount++;
            cout << "�߰��Ǿ����ϴ�." << endl;
        }
        else {
            cout << "�߸��Է��ϼ̽��ϴ�. (������ ����)" << endl;
        }
    }
    else {
        cout << "�߸��Է��ϼ̽��ϴ�. (���� ������)" << endl;
    }

    initalsetting_recursive(i + 1);
}

int main() {
    int cho, last;
    initalsetting_recursive();
    while (true) {
        cout << "========================================" << endl << "��ɾ�� ���� ���ڷ� �Է��Ѵ�." << endl;
        cout << "1. Search  2. Insert   3. Delete   4. DeleteAll" << endl << "5. PrintAll   6. FindMaxHp  7. SortByHp" << endl;
        cout << "========================================" << endl;
        cin >> cho;
        switch (cho) {
        case 1: {
            char name[30];
            cout << "�̸�(����, �ִ� 20��) : ";
            cin.ignore();
            scanf("%[^\n]s", name);
            if (strlen(name) <= 20) {
                SearchRecursive(0, name);
            }
            else {
                cout << "�̸��� �ʹ� ��" << endl;
            }
            break;
        }
        case 2:
            insert();
            break;
        case 3: {
            char name[30];
            cout << "�̸�(����, �ִ� 20��) : ";
            cin.ignore();
            scanf("%[^\n]s", name);
            if (strlen(name) <= 20) {
                deletenameRecursive(0, name);
            }
            else {
                cout << "�̸��� �ʹ� ��" << endl;
            }
            break;
        }
        case 4: {
            char position[10];
            cout << "��������(top, jungle, mid, bottom, support) : ";
            cin >> position;
            if (strcmp(position, "top") == 0 || strcmp(position, "jungle") == 0 || strcmp(position, "mid") == 0 || strcmp(position, "bottom") == 0 || strcmp(position, "support") == 0) {
                deleteallRecursive(0, position);
            }
            else {
                cout << "�������� �߸� �Է��Ͽ����ϴ�." << endl;
            }
            break;
        }
        case 5:
            printAllRecursive();
            break;
        case 6:
            FindmaxhpRecursive();
            break;
        case 7:
            sortbyhpRecursive();
            break;
        default:
            cout << "�߸� �Է��Ͽ����ϴ�." << endl;
            break;
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