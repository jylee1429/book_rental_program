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
int Book::getBookISBN() const
{
	if (each.size() == 0)
		return -1;				// 재고 없음

	return each[0].getISBN();	// ISBN 출력
}

void Book::addBook(int isbn, const string& title, const string& author, const string& publisher) { //책 등록
	this->title = title;
	this->author = author;
	this->publisher = publisher;
	this->each.push_back(isbn);
}

void Book::searchBook() const //책 검색
{
	cout << "책 제목 : " << this->getTitle() << endl;
	cout << "책 저자 : " << this->getAuthor() << endl;
	cout << "출판사 : " << this->getPublisher() << endl;
}

void Book::borrowBook() //책 대출
{
	vector<EachBook>::iterator it;
	for (it = this->each.begin(); it != this->each.end(); it++)
		if ((*it).available())
			break;

	int i = (*it).getISBN();
	cout << "ISBN : " << i << " 책을 대출합니다.\n";
	(*it).borrow(i);
}

void Book::returnBook(int isbn) //책 반납
{
	vector<EachBook>::iterator it;
	for (it = this->each.begin(); it != each.end(); it++)
		if ((*it).getISBN() == isbn)
			break;
	(*it).return_book();
	cout << "반납 완료\n";
}


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
int EachBook::getISBN() const
{
	return this->ISBN;
}
bool EachBook::available()
{
	return this->borrow_status;
}

void EachBook::borrow(int ISBN)
{
	this->borrow_status = true;
}

void EachBook::return_book() {
	this->borrow_status = false;
}