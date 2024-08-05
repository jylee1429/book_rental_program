#include <iostream>
#include <windows.h>
#include <thread>
#include <chrono>
#include <conio.h>
#include <map>
#include "member.h"
#include "book.h"

using namespace std;
using namespace std::this_thread; // sleep_for, sleep_until
using namespace std::chrono; // nanoseconds, system_clock, seconds

int menuDraw();
void gotoxy(int x, int y);
void setConsoleColor(int background, int foreground);
void printCentered(const string& text, int y, int width);
int navigateMenu(int x, int y, int options);


vector<Book> bookList;

int main(void)
{
	/* �ܼ�â ȯ�� ���� */
	system("mode con:cols=150 lines=40 |title ���� ���� ���α׷�");

	MemberManage List;
	string title, author, publisher;
	int isbn, id, idx;
	Book temp;

	loadBook(bookList);														// ����� å ������ �ҷ�����

	while (true)
	{
		int menu = menuDraw();
		if (menu == -1) {
			cout << endl << "���α׷��� �����մϴ�.\n";
			break;
		}

		cin.ignore();
		cout << endl;

		switch (menu) {
		// å ��� �Լ� ȣ��
			case 1:															
				cout << "======= å ��� =======\n";
				cout << "å ���� : ";
				getline(cin, title);
				cout << "���� : ";
				getline(cin, author);
				cout << "���ǻ� : ";
				getline(cin, publisher);
				cout << "ISBN : ";
				cin >> isbn;

				temp.setBookInfo(title, author, publisher);
				temp.addBook(bookList, isbn);
				cout << endl;

				storeBook(bookList);
				break;
			// ȸ�� ��� �Լ� ȣ��
			case 2: 
				cout << "======= ȸ�� ��� =======\n";
				List.memberRegister();
				cout << "ȸ�� ��� �Ϸ�\n";
				break;
			// ���� ���� 
			case 3:
				cout << "======= ���� =======\n";
				cout << "ȸ�� id : ";
				cin >> id;
				cout << "å ���� : ";
				cin >> title;
				
				List.memberBorrowBooks(bookList, id, title);
				break;
			// �ݳ�
			case 4:
				cout << "======= �ݳ� =======\n";
				cout << "ȸ�� id : ";
				cin >> id;
				cout << "ISBN : ";
				cin >> isbn;
				
				List.memberReturnBooks(bookList, id, isbn);
				break;
			// ���� ���� ��Ȳ
			case 5:
				cout << "======= ���� ���� ��Ȳ =======\n";
				List.memberShow();
				break;
			// ��� ���� ���
			case 6:
				cout << "======= ��� ���� ��� =======\n";
				List.showBoookList(bookList);
				break;
			default:
				cout << "�߸��� �����Դϴ�.\n";
				break;
		}
		system("pause");
	}
}

void printCentered(const string& text, int y, int width)
{
	int x = (width - text.length()) / 2;
	gotoxy(x, y);
	cout << text;
}

int menuDraw()
{
	system("cls"); // ȭ�� clear

	CONSOLE_SCREEN_BUFFER_INFO csbi;
	int columns, rows;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
	columns = csbi.srWindow.Right - csbi.srWindow.Left + 1;
	rows = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;

	int x = 0;
	int y = 0;

	return navigateMenu(x, y + 2, 7);
}

int navigateMenu(int x, int y, int options)
{
	int currentSelection = 0;

	while (true)
	{
		// ȭ��ǥ�� ���� ������ ���� ǥ��
		for (int i = 0; i < options; i++)
		{
			if (i == currentSelection)
			{
				setConsoleColor(BACKGROUND_RED | BACKGROUND_INTENSITY, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
			}
			else
			{
				setConsoleColor(0, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
			}

			gotoxy(x, y + i);
			cout << ((i == 0) ? "1. å ���       " :
				(i == 1) ? "2. ȸ�� ���     " :
				(i == 2) ? "3. ����     " :
				(i == 3) ? "4. �ݳ�          " :
				(i == 4) ? "5. ���� ���� ��Ȳ" :
				(i == 5) ? "6. ��� ���� ���" :
				"-1. ����          ");
		}

		setConsoleColor(0, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);

		// Ű �Է� ó��
		int key = _getch();
		switch (key)
		{
		case 72: // ȭ��ǥ ��
			currentSelection = (currentSelection - 1 + options) % options;
			break;
		case 80: // ȭ��ǥ �Ʒ�
			currentSelection = (currentSelection + 1) % options;
			break;
		case 13: // Enter Ű
			if (currentSelection == options - 1)
				return-1;
			return currentSelection + 1;
		}
	}
}

void gotoxy(int x, int y)
{
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void setConsoleColor(int background, int foreground)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), background | foreground);
}