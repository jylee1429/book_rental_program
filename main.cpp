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
	/* �ܼ�â ȯ�� ���� */
	system("mode con:cols=150 lines=40 |title ���� ���� ���α׷�");

	MemberList List;

	/*
	for (int i = 0; i < 3; i++) {
		List.memberRegister();
	}*/

	int menu; //1.å ���(addBook), 2. ȸ�� ���(memberRegister), 2-1. ����(memberBorrowBooks), 2-2. �ݳ�(memberReturnBooks),  3. ���� ���� ��Ȳ(memberShow) 4. ��� ���� ���(searchBook) (-1: ����)
	while (true)
	{
		cin >> menu;
		if (menu == -1)
		{
			cout << "�����մϴ�.\n";
			break;
		}

	}

	Book tmp;

	book_list.push_back(tmp);
	book_list[0].addBook(1234, "����", "����", "���ǻ�");
	book_list[1].addBook(1235, "����1", "����1", "���ǻ�1");
	book_list[2].addBook(1236, "����2", "����2", "���ǻ�2");

	for (int i = 0; i < 3; i++) {
		book_list[i].searchBook();
	}

	List.memberShow();

	List.memberBorrowBooks(1, "����");
	List.memberBorrowBooks(1, "����1");
	List.memberBorrowBooks(2, "����2");
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
	gotoxy(x - 2, y); //> ���
}

void gotoxy(int, int) {

}