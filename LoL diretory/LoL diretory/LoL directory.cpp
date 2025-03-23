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
    cout << camp[i].name << endl << "ü�� : " << camp[i].hp << endl << "���� : " << camp[i].mp << endl << "�ӵ� : " << camp[i].speed << endl << "��Ÿ� : " << camp[i].range << endl << "�� ������ : " << camp[i].position << endl;
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
        cout << "�ش� �̸��� ���� è�Ǿ��� �����ϴ�." << endl;
}

void insert()
{
	char name[30];
	int hp, mp, speed, range;
	char position[10];
    while (true) {
        cout << "�̸�(����, �ִ� 20��) ü�� ���� �ӵ� ��Ÿ� ��������(top, jungle, mid, bottom, support) : ";
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
                    cout << "�߰��Ǿ����ϴ�." << endl;
                }
                else
                    cout << "�߸��Է��ϼ̽��ϴ� �ٽ� �Է����ֽʽÿ�" << endl;
            }
            else
                cout << "�߸��Է��ϼ̽��ϴ� �ٽ� �Է����ֽʽÿ�" << endl;
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
            cout << "è�Ǿ��� �����Ǿ����ϴ�." << endl;
            return;
		}
	}
    cout << "�ش� è�Ǿ��� �����ϴ�." << endl;
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
    cout << "�ش� �������� è�Ǿ��� �����Ǿ����ϴ�" << endl;
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
    cout << "ü�� �������� ���ĿϷ�" << endl;
}

int main()
{
	int cho;
    int last;
	while (true)
	{
        cout << "========================================" << endl << "��ɾ�� ���� ���ڷ� �Է��Ѵ�." << endl;
        cout << "1. Search  2. Insert   3. Delete   4. DeleteAll" << endl << "5. PrintAll   6. FindMaxHp  7. SortByHp" << endl;
		cout << "========================================" << endl;
		cin >> cho;
        switch (cho)
        {
        case 1: 
        {
            char name[30];
            while (true) {
                cout << "�̸�(����, �ִ� 20��) : ";
                getchar();
                scanf("%[^\n]s", name);
                if (strlen(name) <= 20) {
                    Search(name);
                    break;
                }
                else {
                    cout << "�̸��� �ʹ� ��" << endl;
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
                cout << "�̸�(����, �ִ� 20��) : ";
                getchar();
                scanf("%[^\n]s", name);
                if (strlen(name) <= 20) {
                    deletename(name);
                    break;
                }
                else {
                    cout << "�̸��� �ʹ� ��" << endl;
                }
            }
            break;
        }
        case 4:
        {
            char position[10];
            while (true) {
                cout << "��������(top, jungle, mid, bottom, support) : ";
                cin >> position;
                if (strcmp(position, "top") == 0 || strcmp(position, "jungle") == 0 || strcmp(position, "mid") == 0 || strcmp(position, "bottom") == 0 || strcmp(position, "support") == 0) {
                    deleteall(position);
                    break;
                }
                else {
                    cout << "�������� �߸� �Է��Ͽ����ϴ�." << endl;
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
            cout << "�߸� �Է��Ͽ����ϴ�." << endl;
            break;
        }
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
