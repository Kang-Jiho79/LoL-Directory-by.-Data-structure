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
        << "체력 : " << champ[i].hp << endl
        << "마나 : " << champ[i].mp << endl
        << "속도 : " << champ[i].speed << endl
        << "사거리 : " << champ[i].range << endl
        << "주 포지션 : " << champ[i].position << endl;
}

void SearchRecursive(int i, char name[], bool found = false) {
    if (i >= champcount) {
        if (!found)
            cout << "해당 이름을 가진 챔피언은 없습니다." << endl;
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

    cout << "이름(영어, 최대 20자) 체력 마나 속도 사거리 주포지션(top, jungle, mid, bottom, support) : ";
    cin.ignore();
    scanf("%[^	]s", name);
    if (!(cin >> hp >> mp >> speed >> range >> position)) {
        cout << "입력 오류입니다." << endl;
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
                    cout << "추가되었습니다." << endl;
                    return;
                }
            }
            cout << "저장 공간이 없습니다." << endl;
        }
        else {
            cout << "잘못입력하셨습니다." << endl;
        }
    }
    else {
        cout << "잘못입력하셨습니다." << endl;
    }
}

void deletenameRecursive(int i, char name[]) {
    if (i >= champcount) {
        cout << "해당 챔피언이 없습니다." << endl;
        return;
    }
    if (strcmp(champ[i].name, name) == 0) {
        champ[i].name[0] = '\0';
        champ[i].hp = champ[i].mp = champ[i].speed = champ[i].range = 0;
        champ[i].position[0] = '\0';
        champcount--;
        cout << "챔피언이 삭제되었습니다." << endl;
        return;
    }
    deletenameRecursive(i + 1, name);
}

void deleteallRecursive(int i, char position[]) {
    if (i >= champcount) {
        cout << "해당 포지션의 챔피언이 삭제되었습니다" << endl;
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
        cout << "체력 기준으로 정렬완료" << endl;
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
        cout << "초기 세팅입니다. text 파일 전체를 복사해서 붙여넣어 주세요." << endl;

    if (i != 0)
        getchar();

    if (scanf("%[^\t]s", name) != 1) {
        cout << "이름 입력 오류, 다시 시도해 주세요." << endl;
        cin.clear(); cin.ignore(1000, '\n');
        initalsetting_recursive(i);
        return;
    }

    if (!(cin >> hp >> mp >> speed >> range >> position)) {
        cout << "숫자 입력 오류, 다시 시도해 주세요." << endl;
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
            cout << "추가되었습니다." << endl;
        }
        else {
            cout << "잘못입력하셨습니다. (포지션 오류)" << endl;
        }
    }
    else {
        cout << "잘못입력하셨습니다. (조건 불충족)" << endl;
    }

    initalsetting_recursive(i + 1);
}

int main() {
    int cho, last;
    initalsetting_recursive();
    while (true) {
        cout << "========================================" << endl << "명령어는 앞의 숫자로 입력한다." << endl;
        cout << "1. Search  2. Insert   3. Delete   4. DeleteAll" << endl << "5. PrintAll   6. FindMaxHp  7. SortByHp" << endl;
        cout << "========================================" << endl;
        cin >> cho;
        switch (cho) {
        case 1: {
            char name[30];
            cout << "이름(영어, 최대 20자) : ";
            cin.ignore();
            scanf("%[^\n]s", name);
            if (strlen(name) <= 20) {
                SearchRecursive(0, name);
            }
            else {
                cout << "이름이 너무 긺" << endl;
            }
            break;
        }
        case 2:
            insert();
            break;
        case 3: {
            char name[30];
            cout << "이름(영어, 최대 20자) : ";
            cin.ignore();
            scanf("%[^\n]s", name);
            if (strlen(name) <= 20) {
                deletenameRecursive(0, name);
            }
            else {
                cout << "이름이 너무 긺" << endl;
            }
            break;
        }
        case 4: {
            char position[10];
            cout << "주포지션(top, jungle, mid, bottom, support) : ";
            cin >> position;
            if (strcmp(position, "top") == 0 || strcmp(position, "jungle") == 0 || strcmp(position, "mid") == 0 || strcmp(position, "bottom") == 0 || strcmp(position, "support") == 0) {
                deleteallRecursive(0, position);
            }
            else {
                cout << "포지션을 잘못 입력하였습니다." << endl;
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
            cout << "잘못 입력하였습니다." << endl;
            break;
        }

        while (true) {
            cout << "계속 진행하겠다면 1 그만하겠다면 2 : " << endl;
            cin >> last;
            if (last == 1) {
                system("cls");
                break;
            }
            else if (last == 2) {
                return 0;
            }
            else {
                cout << "다시 입략하십시오" << endl;
            }
        }
    }
}