#ifndef _BOOK_H_
#define _BOOK_H_

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <iomanip>

using namespace std;

class EachBook;

class Book {
protected:
	string title; //제목
	string author; //저자
	string publisher; //출판사
	vector<EachBook> each; //각각의 책 저장
public:
	Book();
	//Book(int isbn, string title, string author, string publisher);

	virtual string getTitle() const;
	string getAuthor() const;
	string getPublisher() const;
	int getBookISBN() const;

	void addBook(int isbn, const string& title, const string& author, const string& publisher); //책 등록
	void searchBook() const; //책 정보 출력
	Book borrowBook(int isbn, string& t); //책 대출
	void returnBook(int isbn); //책 반납
};


class EachBook : public Book {
protected:
	int ISBN;
	bool borrow_status; //대출 여부
	string title;
public:
	EachBook();
	EachBook(int ISBN);

	void setISBN(int isbn);
	int getISBN() const;
	bool available();

	void borrow(int ISBN); //책 대출
	void return_book(); //책 반납

	string getTitle() const;
	void setTitle(string t);
};

// 책 정보 불러오기
void loadBook(vector<Book>& vBook);
// 책 정보 저장
void storeBook(const vector<Book>& vBook);
#endif