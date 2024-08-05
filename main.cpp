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
	/* 콘솔창 환경 설정 */
	system("mode con:cols=150 lines=40 |title 도서 관리 프로그램");

	MemberManage List;
	string title, author, publisher;
	int isbn, id, idx;
	Book temp;

	loadBook(bookList);														// 저장된 책 데이터 불러오기

	while (true)
	{
		int menu = menuDraw();
		if (menu == -1) {
			cout << endl << "프로그램을 종료합니다.\n";
			break;
		}

		cin.ignore();
		cout << endl;

		switch (menu) {
		// 책 등록 함수 호출
			case 1:															
				cout << "======= 책 등록 =======\n";
				cout << "책 제목 : ";
				getline(cin, title);
				cout << "저자 : ";
				getline(cin, author);
				cout << "출판사 : ";
				getline(cin, publisher);
				cout << "ISBN : ";
				cin >> isbn;

				temp.setBookInfo(title, author, publisher);
				temp.addBook(bookList, isbn);
				cout << endl;

				storeBook(bookList);
				break;
			// 회원 등록 함수 호출
			case 2: 
				cout << "======= 회원 등록 =======\n";
				List.memberRegister();
				cout << "회원 등록 완료\n";
				break;
			// 도서 대출 
			case 3:
				cout << "======= 대출 =======\n";
				cout << "회원 id : ";
				cin >> id;
				cout << "책 제목 : ";
				cin >> title;
				
				List.memberBorrowBooks(bookList, id, title);
				break;
			// 반납
			case 4:
				cout << "======= 반납 =======\n";
				cout << "회원 id : ";
				cin >> id;
				cout << "ISBN : ";
				cin >> isbn;
				
				List.memberReturnBooks(bookList, id, isbn);
				break;
			// 도서 대출 현황
			case 5:
				cout << "======= 도서 대출 현황 =======\n";
				List.memberShow();
				break;
			// 등록 도서 목록
			case 6:
				cout << "======= 등록 도서 목록 =======\n";
				List.showBoookList(bookList);
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

	int x = 0;
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
				(i == 2) ? "3. 대출     " :
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