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

	return each[each.size() - 1].getISBN();	// ISBN 출력
}

void Book::addBook(int isbn, const string& title, const string& author, const string& publisher) { //책 등록
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
}

Book Book::borrowBook(int isbn, string& t) //책 대출
{
	try {
		cout << "ISBN: " << isbn << " 책을 대출합니다.\n";

		for (auto& it : this->each)
		{
			//auto eachBook = dynamic_cast<Book>(it);
			if (it.getISBN() == isbn)
			{
				it.setTitle(t);
				cout << "책 제목 : " << this->getTitle() << endl;
				cout << "저자 : " << this->getAuthor() << endl;
				cout << "출판사 : " << this->getPublisher() << endl;

				it.borrow(isbn);
				return *this;
			}
		}
	}
	catch (exception& e) {
		cout << "대출 불가\n";
	}
}

void Book::returnBook(int isbn) //책 반납
{
	for (auto& it : this->each)
		if (it.getISBN() == isbn)
		{
			it.return_book();
		}

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
	return ISBN;
}
bool EachBook::available()
{
	return borrow_status;
}

void EachBook::borrow(int ISBN)
{
	this->borrow_status = true;
}

void EachBook::return_book() {
	this->borrow_status = false;
}

string EachBook::getTitle() const
{
	//return this->title;
	return Book::getTitle();
}

void EachBook::setTitle(string t)
{
	this->title = t;
}

// 책 목록 읽기
void loadBook(vector<Book>& vBook) {
	string title, author, publisher;
	string line;
	int isbn = 1;

	ifstream file("book_information.txt");
	// file이 정상적으로 열렸는지 확인 
	if (!file.is_open()) {
		cout << "파일을 열 수 없습니다." << endl;
		exit(1);
	}

	while (getline(file, line)) {
		istringstream iss(line);

		Book temp;
		if (getline(iss, title, '\t') &&
			getline(iss, author, '\t') &&
			getline(iss, publisher, '\t')) {

			temp.addBook(isbn++, title, author, publisher);
			vBook.push_back(temp);
		}
	}

	file.close();

}

// 책 목록 쓰기
void storeBook(const vector<Book>& vBook) {
	ofstream file("book_information.txt", ios::out);

	if (!file.is_open()) {
		cout << "파일을 열 수 없습니다." << endl;
		exit(1);
	}

	for (const auto& book : vBook) {
		file << book.getTitle() << '\t' << book.getAuthor() << '\t' << book.getPublisher() << '\n';
	}

	file.close();
}