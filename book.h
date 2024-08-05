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
	string title;				// ����
	string author;				// ����
	string publisher;			// ���ǻ�
	vector<EachBook> each;		// ����, ����, ���ǻ簡 ���� å�� ����(isbn �̵���)
public:														
	Book(string title="-", string author="", string publisher="");
	int compareBook(vector<Book>& bookList);
	virtual string getTitle() const;
	string getAuthor() const;
	string getPublisher() const;
	void setBookInfo(string title, string author, string publisher);
	int getBookISBN() const;
	void addBook(vector<Book>& bookList, int isbn);
	void addEachBook(int isbn);										// isbn�� �ٸ� å ���
	void returnBook(vector<Book>& booklist, int isbn);
	Book borrowBook(int isbn, const string& title);					//å ����
	void returnBook(int isbn);										//å �ݳ�
	bool searchISBN(vector<Book>& booklist, int isbn);
	void showBook() const;
	bool returnISBN(vector<Book>& booklist, int isbn);
	bool operator==(const Book& other) const;
};


class EachBook : public Book {
	int ISBN;
	string title;
	bool borrow_status;							 //���� ����
public:
	EachBook();
	EachBook(int ISBN);
	void setISBN(int isbn);
	int getISBN() const;
	bool available();
	void borrow(int ISBN);						//å ����
	void returnBook();
	string getTitle() const;
	void setTitle(string t);
};



// å ���� �ҷ�����
void loadBook(vector<Book>& vBook);
// å ���� ����
void storeBook(const vector<Book>& vBook);

#endif