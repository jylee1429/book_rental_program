#include <iostream>
using namespace std;
#include "eachBook.h"


EachBook::EachBook() {
	this->ISBN = 0;
	this->borrow_status = true;
}
EachBook::EachBook(int ISBN)
{
	this->ISBN = ISBN;
	this->borrow_status = true;
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
	this->borrow_status = false;
	cout << "대출 완료\n";
}
