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
			cout << camp[i].name << endl << " 체력 : " << camp[i].hp << endl << " 마나 : " << camp[i].mp << endl << " 속도 : " << camp[i].speed << endl << " 사거리 : " << camp[i].range << endl << " 주 포지션 : " << camp[i].position << endl;
		}
	}
}
void insert(lol camp[], int& campcount)
{
	char name[30];
	int hp, mp, speed, range;
	char position[10];
	cout << "이름(영어, 최대 20자) : ";
	cin >> name;
	cout << "체력 : ";
	cin >> hp;
	cout << "마나 : ";
	cin >> mp;
	cout << "속도 : ";
	cin >> speed;
	cout << "사거리 : ";
	cin >> range;
	cout << "주포지션(top, jugle, mid, bottom, support) : ";
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
		cout << "Search [챔피언이름] : 주어진 챔피언의 정보를 배열에서 찾아 출력한다." << endl << "Insert : 새로운 챔피언의 정보를 입력받아 배열에 삽입한다." << endl << "Delete [챔피언이름] : 주어진 챔피언에 대한 정보를 배열에서 삭제한다." << endl;
		cout << "DeleteAll [position](top, jugle, mid, bottom, support) : 주어진 위치의 모든 챔피언 정보를 배열에서 삭제한다." << endl << "PrintAll : 모든 챔피언의 정보를 배열에 저장된 순서대로 출력한다.(정렬을 수행한 후 PrintAll을 수행하면 정렬된 순서대로 출력되어야 합니다.)" << endl;
		cout << "FindMaxHp: 가장 체력이 큰 챔피언의 정보를 출력한다.(HP가 가장 큰 챔피언이 여럿이면 모두 출력한다)" << endl << "SortByHp: 체력이 큰 챔피언부터 순서대로 저장한다.(HP가 동일한 챔피언은 연속으로 저장되어야 합니다.)" << endl;
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