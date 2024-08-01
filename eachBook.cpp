#include "eachBook.h"

EachBook::EachBook() {
	this->ISBN = 0;
	this->borrow = true;
}
EachBook::EachBook(int ISBN)
{
	this->ISBN = ISBN;
	this->borrow = true;
}

void EachBook::setISBN(int isbn)
{
	this->ISBN = isbn;
}
int EachBook::getISBN()
{
	return this->ISBN;
}
bool EachBook::available()
{
	return borrow;
}

void EachBook::borrow(int ISBN)
{
	this->borrow = false;
	cout << "대출 완료\n";
}
