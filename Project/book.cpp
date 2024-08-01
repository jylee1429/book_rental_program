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

void Book::searchBook() const //책 검색
{
	cout << "책 제목 : " << this->getTitle() << endl;
	cout << "책 저자 : " << this->getAuthor() << endl;
	cout << "출판사 : " << this->getPublisher() << endl;

	int cnt = 0;
	for (auto it : this->each)
		if (it.available())
			cnt++;
	cout << "대출 가능 권 수 : " << cnt << endl;
	cout << "전체 권 수 : " << this->each.size() << endl;
}

EachBook Book::borrowBook() //책 대출
{
	vector<EachBook>::iterator it;

	for (it = this->each.begin(); it != this->each.end(); it++)
		if ((*it).available())
			break;

	cout << (*it).getTitle() << "  을(를) 대출합니다.\n";
	int i = (*it).getISBN();
	cout << "ISBN : " << i << endl;

	try {
		(*it).borrow(i);
	}
	catch (exception& e) {
		cout << "대출이 불가합니다.\n";
	}
}

void Book::returnBook(int isbn) //책 반납
{
	vector<EachBook>::iterator it;
	for (it = this->each.begin(); it != each.end(); it++)
		if ((*it).getISBN() == isbn)
			break;
	(*it).return_book(isbn);
	cout << "반납 완료\n";
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

bool EachBook::available() //대출 가능 여부
{
	return this->borrow_status;
}

void EachBook::borrow(int ISBN) //isbn 해당 책 대출 처리
try {
	if (this->borrow_status)
		throw 1;
	else
		this->borrow_status = true;
	cout << "대출 완료\n";
}
catch (int e) {
	cout << "이미 대출된 책입니다.\n";
}
}

void EachBook::return_book(int ISBN)  //책 반납 처리
{
	try {
		if (this->borrow_status == false)
			throw 1;
		else
			this->borrow_status = false;
		cout << "반납 완료\n";
	}
	catch (int e) {
		cout << "이미 반납된 책입니다.\n";
	}
}
