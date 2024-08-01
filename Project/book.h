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
	string title; //����
	string author; //����
	string publisher; //���ǻ�
	vector<EachBook> each; //������ å ����
public:
	Book();
	//Book(int isbn, string title, string author, string publisher);

	string getTitle() const;
	string getAuthor() const;
	string getPublisher() const;

	void addBook(int isbn, const string& title, const string& author, const string& publisher); //å ���
	void searchBook() const; //å ���� ���
	void borrowBook(); //å ����
	void returnBook(int isbn); //å �ݳ�
};

#endif