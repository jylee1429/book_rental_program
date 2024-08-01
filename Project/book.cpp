#include "book.h"

/* Book */
Book::Book() : title(""), author(""), publisher("") {}

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
	this->each.push_back(EachBook(isbn));
}

void Book::searchBook() const //å �˻�
{
	cout << "å ���� : " << this->getTitle() << endl;
	cout << "å ���� : " << this->getAuthor() << endl;
	cout << "���ǻ� : " << this->getPublisher() << endl;

	int cnt = 0;
	for (auto it : this->each)
		if (it.available())
			cnt++;
	cout << "���� ���� �� �� : " << cnt << endl;
	cout << "��ü �� �� : " << this->each.size() << endl;
}

void Book::borrowBook() //å ����
{
	vector<EachBook>::iterator it;

	for (it = this->each.begin(); it != this->each.end(); it++)
		if ((*it).available())
			break;

	cout << (*it).getTitle() << " ��(��) �����մϴ�.\n";
	int i = (*it).getISBN();
	cout << "ISBN : " << i << endl;

	try {
		(*it).borrow(i);
	}
	catch (exception& e) {
		cout << "������ �Ұ��մϴ�.\n";
	}
}

void Book::returnBook(int isbn) //å �ݳ�
{
	vector<EachBook>::iterator it;
	for (it = this->each.begin(); it != each.end(); it++)
		if ((*it).getISBN() == isbn)
			break;
	(*it).return_book(isbn);
	cout << "�ݳ� �Ϸ�\n";
}

/* EachBook */
EachBook::EachBook() :EachBook(0) {}
EachBook::EachBook(int ISBN)
{
	this->ISBN = ISBN;
	this->borrow_status = false;
}

void EachBook::setISBN(int isbn)
{
	this->ISBN = isbn;
}
int EachBook::getISBN()
{
	return this->ISBN;
}

bool EachBook::available() //���� ���� ����
{
	return this->borrow_status;
}

void EachBook::borrow(int ISBN) //isbn �ش� å ���� ó��
{
	try {
		if (this->borrow_status)
			throw 1;
		else
			this->borrow_status = true;
		cout << "���� �Ϸ�\n";
	}
	catch (int e) {
		cout << "�̹� ����� å�Դϴ�.\n";
	}
}

void EachBook::return_book(int ISBN)  //å �ݳ� ó��
{
	try {
		if (this->borrow_status == false)
			throw 1;
		else
			this->borrow_status = false;
		cout << "�ݳ� �Ϸ�\n";
	}
	catch (int e) {
		cout << "�̹� �ݳ��� å�Դϴ�.\n";
	}
}
