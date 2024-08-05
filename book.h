#ifndef _BOOK_H_
#define _BOOK_H_

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <map>
#include <algorithm>

using namespace std;

class EachBook;

class Book {
protected:
	string title;				// 제목
	string author;				// 저자
	string publisher;			// 출판사
	vector<EachBook> each;		// 제목, 저자, 출판사가 같은 책들 저장(isbn 미동일)
public:														
	Book(string title="-", string author="", string publisher="");
	int compareBook(vector<Book>& bookList);
	virtual string getTitle() const;
	string getAuthor() const;
	string getPublisher() const;
	void setBookInfo(string title, string author, string publisher);
	int getBookISBN() const;
	void addBook(vector<Book>& bookList, int isbn);
	void addEachBook(int isbn);										// isbn이 다른 책 등록
	void returnBook(vector<Book>& booklist, int isbn);
	Book borrowBook(int isbn, const string& title);					//책 대출
	void returnBook(int isbn);										//책 반납
	bool searchISBN(vector<Book>& booklist, int isbn);
	void showBook() const;
	bool returnISBN(vector<Book>& booklist, int isbn);
	bool operator==(const Book& other) const;
};


class EachBook : public Book {
	int ISBN;
	string title;
	bool borrow_status;							 //대출 여부
public:
	EachBook();
	EachBook(int ISBN);
	void setISBN(int isbn);
	int getISBN() const;
	bool available();
	void borrow(int ISBN);						//책 대출
	void returnBook();
	string getTitle() const;
	void setTitle(string t);
};



// 책 정보 불러오기
void loadBook(vector<Book>& vBook);
// 책 정보 저장
void storeBook(const vector<Book>& vBook);

#endif