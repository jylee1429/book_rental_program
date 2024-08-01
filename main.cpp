//#include <bits/stdc++.h>
#include <iostream>
#include <windows.h>
#include "member.h"
#include "book.h"

using namespace std;

vector<Book> book_list(3);
int menuDraw();


int main(void)
{
	/* 콘솔창 환경 설정 */
	system("mode con:cols=150 lines=40 |title 도서 관리 프로그램");

	MemberList List;

	/*
	for (int i = 0; i < 3; i++) {
		List.memberRegister();
	}*/

	int menu; //1.책 등록(addBook), 2. 회원 등록(memberRegister), 2-1. 대출(memberBorrowBooks), 2-2. 반납(memberReturnBooks),  3. 도서 대출 현황(memberShow) 4. 등록 도서 목록(searchBook) (-1: 종료)
	while (true)
	{
		cin >> menu;
		if (menu == -1)
		{
			cout << "종료합니다.\n";
			break;
		}

	}

	Book tmp;

	book_list.push_back(tmp);
	book_list[0].addBook(1234, "제목", "저자", "출판사");
	book_list[1].addBook(1235, "제목1", "저자1", "출판사1");
	book_list[2].addBook(1236, "제목2", "저자2", "출판사2");

	for (int i = 0; i < 3; i++) {
		book_list[i].searchBook();
	}

	List.memberShow();

	List.memberBorrowBooks(1, "제목");
	List.memberBorrowBooks(1, "제목1");
	List.memberBorrowBooks(2, "제목2");
	List.memberShow();

	List.memberReturnBooks(1, 1234);
	List.memberReturnBooks(1, 1235);

	List.memberShow();

	// List.memberShow();
}

int menuDraw()
{
	int x = 24;
	int y = 12;
	gotoxy(x - 2, y); //> 출력
}

void gotoxy(int, int) {

}