//#include <bits/stdc++.h>
#include <iostream>
#include "member.h"
#include "book.h"

using namespace std;

vector<Book> book_list(3);

int main(void) {
	MemberList List;

	for (int i = 0; i < 3; i++) {
		List.memberRegister();
	}

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