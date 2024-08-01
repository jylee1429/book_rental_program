#pragma once
#include <iostream>
#include <string>
#include <map>
#include <vector>
#include "eachBook.h"
using namespace std;

vector<Book> book_list;

class Book {
protected:
	string title; //����
	string author; //����
	string publisher; //���ǻ�
	vector<EachBook> each; //������ å ����
public:
	Book();
	//Book(int isbn, string title, string author, string publisher);

	string getTitle();
	string getAuthor();
	string getPublisher();

	void addBook(int isbn, string title, string author, string publisher); //å ���
	void searchBook(int isbn); //å ���� �˻�
	void returnBook(int isbn); //å �ݳ�
};
