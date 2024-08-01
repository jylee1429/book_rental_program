#include <iostream>
using namespace std;
#include "eachBook.h"

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
bool EachBook::available()
{
	return this->borrow_status;
}

void EachBook::borrow(int ISBN)
{
	this->borrow_status = true;
	cout << "대출 완료\n";
}

void EachBook::return_book() {
	this->borrow_status = false;
}
