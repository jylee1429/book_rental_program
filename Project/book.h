#ifndef _BOOK_H_
#define _BOOK_H_
#include <iostream>
#include <string>
#include <vector>
#include "eachBook.h"
using namespace std;

//vector<Book> book_list;

class Book {
protected:
	string title; //제목
	string author; //저자
	string publisher; //출판사
	vector<EachBook> each; //각각의 책 저장
public:
	Book();
	//Book(int isbn, string title, string author, string publisher);

	string getTitle() const;
	string getAuthor() const;
	string getPublisher() const;

	void addBook(int isbn, const string& title, const string& author, const string& publisher); //책 등록
	void searchBook() const; //책 정보 출력
	void borrowBook(); //책 대출
	void returnBook(int isbn); //책 반납
};

#endif