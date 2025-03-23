#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string.h>
using namespace std;

struct lol
{
public:
	char name[30];
	int hp;
	int mp;
	int speed;
	int range;
	char position[10];
};

lol camp[100];
int campcount = 0;

void say(int i)
{
    cout << camp[i].name << endl << "체력 : " << camp[i].hp << endl << "마나 : " << camp[i].mp << endl << "속도 : " << camp[i].speed << endl << "사거리 : " << camp[i].range << endl << "주 포지션 : " << camp[i].position << endl;
}

void Search(char name[])
{
    bool check = true;
    for (int i = 0; i < campcount; i++) {
        if (strcmp(camp[i].name, name) == 0) {
            say(i);
            check = false;
        }
    }
    if (check)
        cout << "해당 이름을 가진 챔피언은 없습니다." << endl;
}

void insert()
{
	char name[30];
	int hp, mp, speed, range;
	char position[10];
    while (true) {
        cout << "이름(영어, 최대 20자) 체력 마나 속도 사거리 주포지션(top, jungle, mid, bottom, support) : ";
        for (int i = 0; i < 22; i++) {
            getchar();
            scanf("%[^\t]s", name);
            cin >> hp >> mp >> speed >> range >> position;
            if (strlen(name) <= 20 && hp > 0 && mp >= 0 && speed > 0 && range > 0) {
                if (strcmp(position, "top") == 0 || strcmp(position, "jungle") == 0 || strcmp(position, "mid") == 0 || strcmp(position, "bottom") == 0 || strcmp(position, "support") == 0) {
                    for (int j = 0; j < 20; j++)
                        camp[i].name[j] = name[j];
                    camp[i].hp = hp;
                    camp[i].mp = mp;
                    camp[i].speed = speed;
                    camp[i].range = range;
                    for (int j = 0; j < 10; j++)
                        camp[i].position[j] = position[j];
                    campcount++;
                    cout << camp[i].position << endl;
                    cout << "추가되었습니다." << endl;
                }
                else
                    cout << "잘못입력하셨습니다 다시 입력해주십시오" << endl;
            }
            else
                cout << "잘못입력하셨습니다 다시 입력해주십시오" << endl;
        }
        return;
    }
}

void deletename(char name[])
{
	for (int i = 0; i < campcount; i++) {
		if (strcmp(camp[i].name, name) == 0) {
			for (int j = i; j < campcount; j++) {
				camp[j] = camp[j + 1];
			}
            campcount--;
            cout << "챔피언이 삭제되었습니다." << endl;
            return;
		}
	}
    cout << "해당 챔피언이 없습니다." << endl;
}

void deleteall(char position[])
{
	for (int i = 0; i < campcount; i++) {
		if (strcmp(camp[i].position,position) == 0) {
			for (int j = i; j < campcount; j++)
				camp[j] = camp[j + 1];
			i--;
			campcount--;
		}
	}
    cout << "해당 포지션의 챔피언이 삭제되었습니다" << endl;
}

void Findmaxhp()
{
    int maxhp = 0;
    for (int i = 0; i < campcount; i++) {
        if (camp[i].hp > maxhp)
            maxhp = camp[i].hp;
    }
    for (int i = 0; i < campcount; i++) {
        if (camp[i].hp == maxhp)
            say(i);
    }
}

void sortbyhp()
{
    for (int i = 0; i < campcount - 1; i++) {
        for (int j = i + 1; j < campcount; j++) {
            if (camp[i].hp < camp[j].hp) {
                lol temp = camp[i];
                camp[i] = camp[j];
                camp[j] = temp;
            }
        }
    }
    cout << "체력 기준으로 정렬완료" << endl;
}

int main()
{
	int cho;
    int last;
	while (true)
	{
        cout << "========================================" << endl << "명령어는 앞의 숫자로 입력한다." << endl;
        cout << "1. Search  2. Insert   3. Delete   4. DeleteAll" << endl << "5. PrintAll   6. FindMaxHp  7. SortByHp" << endl;
		cout << "========================================" << endl;
		cin >> cho;
        switch (cho)
        {
        case 1: 
        {
            char name[30];
            while (true) {
                cout << "이름(영어, 최대 20자) : ";
                getchar();
                scanf("%[^\n]s", name);
                if (strlen(name) <= 20) {
                    Search(name);
                    break;
                }
                else {
                    cout << "이름이 너무 긺" << endl;
                }
            }
            break;
        }
        case 2:
        {
            insert();
            break;
        }
        case 3:
        {
            char name[30];
            while (true) {
                cout << "이름(영어, 최대 20자) : ";
                getchar();
                scanf("%[^\n]s", name);
                if (strlen(name) <= 20) {
                    deletename(name);
                    break;
                }
                else {
                    cout << "이름이 너무 긺" << endl;
                }
            }
            break;
        }
        case 4:
        {
            char position[10];
            while (true) {
                cout << "주포지션(top, jungle, mid, bottom, support) : ";
                cin >> position;
                if (strcmp(position, "top") == 0 || strcmp(position, "jungle") == 0 || strcmp(position, "mid") == 0 || strcmp(position, "bottom") == 0 || strcmp(position, "support") == 0) {
                    deleteall(position);
                    break;
                }
                else {
                    cout << "포지션을 잘못 입력하였습니다." << endl;
                }
            }
            break;
        }
        case 5:
        {
            for (int i = 0; i < campcount; i++)
                say(i);
            break;
        }
        case 6:
        {
            Findmaxhp();
            break;
        }
        case 7:
        {
            sortbyhp();
            break;
        }
        default:
        {
            cout << "잘못 입력하였습니다." << endl;
            break;
        }
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
