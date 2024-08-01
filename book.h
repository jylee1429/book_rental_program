#ifndef _BOOK_H_
#define _BOOK_H_

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class EachBook;

class Book {
protected:
	string title; //����
	string author; //����
	string publisher; //���ǻ�
	vector<EachBook> each; //������ å ����
public:
	Book();
	//Book(int isbn, string title, string author, string publisher);

	virtual string getTitle() const;
	string getAuthor() const;
	string getPublisher() const;
	int getBookISBN() const;

	void addBook(int isbn, const string& title, const string& author, const string& publisher); //å ���
	void searchBook() const; //å ���� ���
	EachBook borrowBook(int isbn, string& t); //å ����
	void returnBook(int isbn); //å �ݳ�
};


class EachBook : public Book {
protected:
	int ISBN;
	bool borrow_status; //���� ����
	string title;
public:
	EachBook();
	EachBook(int ISBN);

	void setISBN(int isbn);
	int getISBN() const;
	bool available();

	void borrow(int ISBN); //å ����
	void return_book(); //å �ݳ�

	string getTitle() const;
	void setTitle(string t);
};
#endif