#ifndef _BOOK_H_
#define _BOOK_H_
#include <iostream>
#include <string>
#include <map>
#include <vector>
#include "eachBook.h"
using namespace std;

class Book {
protected:
	string title; //제목
	string author; //저자
	string publisher; //출판사

	vector<EachBook> each; //각각의 책 저장

public:
	Book();
	//Book(int isbn, string title, string author, string publisher);

	string getTitle();
	string getAuthor();
	string getPublisher();

	void addBook(int isbn, string title, string author, string publisher); //책 등록
	void searchBook(int isbn); //책 정보 검색
	void returnBook(int isbn); //책 반납
};
#endif