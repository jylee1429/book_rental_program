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

void Book::addBook(int isbn, string title, string author, string publisher) { //책 등록
	this->title = title;
	this->author = author;
	this->publisher = publisher;
	this->each.push_back(isbn);
}

void Book::searchBook(int isbn) //책 정보 검색
{
	vector<EachBook>::iterator it;
	for (it = this->each.begin(); it != each.end(); it++)
		if ((*it).getISBN() == isbn)
			break;
	cout << "책 제목 : " << (*it).getTitle() << endl;
	cout << "책 저자 : " << (*it).getAuthor() << endl;
	cout << "출판사 : " << (*it).getPublisher() << endl;
	if ((*it).available())
		cout << "대출 가능\n";
	else
		cout << "대출 불가능\n";
}

void returnBook(int isbn) //책 반납
{
	vector<EachBook>::iterator it;
	for (it = this->each.begin(); it != each.end(); it++)
		if ((*it).getISBN() == isbn)
			break;
	(*it).borrow = true;
	cout << "반납 완료\n";
}