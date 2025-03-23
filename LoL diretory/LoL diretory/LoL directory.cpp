#include <iostream>
#include <stdio.h>
using namespace std;

struct lol
{
public:
	char name[30];
	int hp;
	int mp;
	int speed;
	int range;
	char position[4];
};

void say(lol camp[], char name[], int& campcount)
{
	for (int i = 0; i < campcount; i++) {
		if (camp[i].name == name) {
			cout << camp[i].name << endl << " ü�� : " << camp[i].hp << endl << " ���� : " << camp[i].mp << endl << " �ӵ� : " << camp[i].speed << endl << " ��Ÿ� : " << camp[i].range << endl << " �� ������ : " << camp[i].position << endl;
		}
	}
}
void insert(lol camp[], int& campcount)
{
	char name[30];
	int hp, mp, speed, range;
	char position[10];
	cout << "�̸�(����, �ִ� 20��) : ";
	cin >> name;
	cout << "ü�� : ";
	cin >> hp;
	cout << "���� : ";
	cin >> mp;
	cout << "�ӵ� : ";
	cin >> speed;
	cout << "��Ÿ� : ";
	cin >> range;
	cout << "��������(top, jugle, mid, bottom, support) : ";
	cin >> position;
	for (int i = 0; i < 20; i++)
		camp[campcount].name[i] = name[i];
	camp[campcount].hp = hp;
	camp[campcount].mp = mp;
	camp[campcount].speed = speed;
	camp[campcount].range = range;
	for (int i = 0; i < 10; i++)
		camp[campcount].position[i] = position[i];
	campcount++;
}
void deletename(lol camp[], int& campcount, char name[])
{
	for (int i = 0; i < campcount; i++) {
		if (camp[i].name == name) {
			for (int j = i; j < campcount; j++) {
				camp[j] = camp[j + 1];
			}
		}
	}
	campcount--;
}

void deleteall(lol camp[], int& campcount, char position[])
{
	for (int i = 0; i < campcount; i++) {
		if (camp[i].position == position) {
			for (int j = i; j < campcount; j++)
				camp[j] = camp[j + 1];
			i--;
			campcount--;
		}
	}
}

int main()
{
	lol camp[100];
	char cho[10];
	char name[30];
	char position[10];
	int campcount = 0;
	while (true)
	{
		cout << "========================================" << endl;
		cout << "Search [è�Ǿ��̸�] : �־��� è�Ǿ��� ������ �迭���� ã�� ����Ѵ�." << endl << "Insert : ���ο� è�Ǿ��� ������ �Է¹޾� �迭�� �����Ѵ�." << endl << "Delete [è�Ǿ��̸�] : �־��� è�Ǿ� ���� ������ �迭���� �����Ѵ�." << endl;
		cout << "DeleteAll [position](top, jugle, mid, bottom, support) : �־��� ��ġ�� ��� è�Ǿ� ������ �迭���� �����Ѵ�." << endl << "PrintAll : ��� è�Ǿ��� ������ �迭�� ����� ������� ����Ѵ�.(������ ������ �� PrintAll�� �����ϸ� ���ĵ� ������� ��µǾ�� �մϴ�.)" << endl;
		cout << "FindMaxHp: ���� ü���� ū è�Ǿ��� ������ ����Ѵ�.(HP�� ���� ū è�Ǿ��� �����̸� ��� ����Ѵ�)" << endl << "SortByHp: ü���� ū è�Ǿ���� ������� �����Ѵ�.(HP�� ������ è�Ǿ��� �������� ����Ǿ�� �մϴ�.)" << endl;
		cout << "========================================" << endl;
		cin >> cho;
		if (cho == "Search") {
			cin >> name;
			say(camp, name, campcount);
		}
		else if (cho == "Insert") {
			insert(camp, campcount);
		}
		else if (cho == "Delete") {
			cin >> name;
			deletename(camp, campcount, name);
		}
		else if (cho == "DeleteAll") {

		}
		else if (cho == "PrintAll") {

		}
		else if (cho == "FindMaxHp") {

		}
		else if (cho == "SortByHp") {

		}
		else {

		}
	}
}