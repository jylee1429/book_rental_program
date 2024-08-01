#include <iostream>
#include <windows.h>
#include <thread>
#include <chrono>
#include <conio.h>
#include "member.h"
#include "book.h"

using namespace std;
using namespace std::this_thread; // sleep_for, sleep_until
using namespace std::chrono; // nanoseconds, system_clock, seconds

vector<Book> book_list;
int menuDraw();
void gotoxy(int x, int y);
void setConsoleColor(int background, int foreground);
void printCentered(const string& text, int y, int width);
int navigateMenu(int x, int y, int options);

int main(void)
{
	/* 콘솔창 환경 설정 */
	system("mode con:cols=150 lines=40 |title 도서 관리 프로그램");

	MemberList List;

	while (true)
	{
		int menu = menuDraw();
		if (menu == -1) {
			cout << endl << "프로그램을 종료합니다.\n";
			break;
		}

		Book tmp;
		string title, author, publisher;
		int isbn, id;

		cin.ignore();
		cout << endl;
		switch (menu)
		{
		case 1: // 책 등록 함수 호출
			cout << "======= 책 등록 =======\n";
			cout << "책 제목 : ";
			getline(cin, title);
			cout << "저자 : ";
			getline(cin, author);
			cout << "출판사 : ";
			getline(cin, publisher);
			cout << "ISBN : ";
			cin >> isbn;
			tmp.addBook(isbn, title, author, publisher);
			book_list.push_back(tmp);

			cout << "책 등록 완료\n";
			break;
		case 2: // 회원 등록 함수 호출
			cout << "======= 회원 등록 =======\n";
			List.memberRegister();
			cout << "회원 등록 완료\n";
			break;
		case 3:// 도서 대출 
			cout << "======= 대출 =======\n";
			cout << "회원 id : ";
			cin >> id;
			cout << "책 제목 : ";
			cin >> title;
			List.memberBorrowBooks(id, title);
			break;
		case 4: //반납
			cout << "======= 반납 =======\n";
			cout << "회원 id : ";
			cin >> id;
			cout << "ISBN : ";
			cin >> isbn;
			List.memberReturnBooks(id, isbn);
			break;
		case 5: //도서 대출 현황
			cout << "======= 도서 대출 현황 =======\n";
			List.memberShow();
			break;
		case 6:// 등록 도서 목록
			cout << "======= 등록 도서 목록 =======\n";
			for (auto& it : book_list)
				it.searchBook();
			break;
		default:
			cout << "잘못된 선택입니다.\n";
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
	system("cls"); // 화면 clear

	CONSOLE_SCREEN_BUFFER_INFO csbi;
	int columns, rows;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
	columns = csbi.srWindow.Right - csbi.srWindow.Left + 1;
	rows = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;

	int x = 10;
	int y = 0;

	return navigateMenu(x, y + 2, 7);
}

int navigateMenu(int x, int y, int options)
{
	int currentSelection = 0;

	while (true)
	{
		// 화살표로 현재 선택을 강조 표시
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
			cout << ((i == 0) ? "1. 책 등록       " :
				(i == 1) ? "2. 회원 등록     " :
				(i == 2) ? "3. 도서 대출     " :
				(i == 3) ? "4. 반납          " :
				(i == 4) ? "5. 도서 대출 현황" :
				(i == 5) ? "6. 등록 도서 목록" :
				"-1. 종료          ");
		}

		setConsoleColor(0, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);

		// 키 입력 처리
		int key = _getch();
		switch (key)
		{
		case 72: // 화살표 위
			currentSelection = (currentSelection - 1 + options) % options;
			break;
		case 80: // 화살표 아래
			currentSelection = (currentSelection + 1) % options;
			break;
		case 13: // Enter 키
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
