#include "book.h"



Book::Book() {
	this->title = "";
	this->author = "";
	this->publisher = "";
}


string Book::getTitle() {
	return this->title;
}

string Book::getAuthor() {
	return this->author;
}

string Book::getPublisher() {
	return this->publisher;
}

void Book::addBook(int isbn, string title, string author, string publisher) { //å ���
	this->title = title;
	this->author = author;
	this->publisher = publisher;
	this->each.push_back(isbn);
}

void Book::searchBook(int isbn) //å ���� �˻�
{
	vector<EachBook>::iterator it;
	for (it = this->each.begin(); it != each.end(); it++)
		if ((*it).getISBN() == isbn)
			break;
	cout << "å ���� : " << (*it).getTitle() << endl;
	cout << "å ���� : " << (*it).getAuthor() << endl;
	cout << "���ǻ� : " << (*it).getPublisher() << endl;
	if ((*it).available())
		cout << "���� ����\n";
	else
		cout << "���� �Ұ���\n";
}

void returnBook(int isbn) //å �ݳ�
{
	vector<EachBook>::iterator it;
	for (it = this->each.begin(); it != each.end(); it++)
		if ((*it).getISBN() == isbn)
			break;
	(*it).borrow = true;
	cout << "�ݳ� �Ϸ�\n";
}