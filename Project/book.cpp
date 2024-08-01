#include "book.h"

Book::Book() {
	this->title = "";
	this->author = "";
	this->publisher = "";
}

string Book::getTitle() const
{
	return this->title;
}

string Book::getAuthor() const
{
	return this->author;
}

string Book::getPublisher() const
{
	return this->publisher;
}

void Book::addBook(int isbn, const string& title, const string& author, const string& publisher) { //å ���
	this->title = title;
	this->author = author;
	this->publisher = publisher;
	this->each.push_back(isbn);
}

void Book::searchBook() const //å �˻�
{
	cout << "å ���� : " << this->getTitle() << endl;
	cout << "å ���� : " << this->getAuthor() << endl;
	cout << "���ǻ� : " << this->getPublisher() << endl;
}

void Book::borrowBook() //å ����
{
	vector<EachBook>::iterator it;
	for (it = this->each.begin(); it != this->each.end(); it++)
		if ((*it).available())
			break;

	int i = (*it).getISBN();
	cout << "ISBN : " << i << " å�� �����մϴ�.\n";
	(*it).borrow(i);
}

void Book::returnBook(int isbn) //å �ݳ�
{
	vector<EachBook>::iterator it;
	for (it = this->each.begin(); it != each.end(); it++)
		if ((*it).getISBN() == isbn)
			break;
	(*it).return_book();
	cout << "�ݳ� �Ϸ�\n";
}