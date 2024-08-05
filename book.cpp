#include "book.h"

// Constructor
Book::Book(string title, string author, string publisher) {
	this->title = title;
	this->author = author;
	this->publisher = publisher;
}
// 책 정보 저장
void Book::setBookInfo(string title, string author, string publisher) {
	this->title = title;
	this->author = author;
	this->publisher = publisher;
}

// 책 리스트 중 제목, 저자, 출판사가 같은 책이 있는지 확인
int Book :: compareBook(vector<Book>& bookList) {
	if (!bookList.size()) {
		return -1;
	}

	for (int i = 0; i < bookList.size(); i++) {
		// 같은 책이 있는 경우 index반환
		if ((*this) == bookList[i]) {
			return i;
		}
		// 같은 책이 없는 경우 -1 반환
		else {
			return -1;
		}
	}
}

// 비교 oepration
bool Book :: operator==(const Book& book) const {
	if ((title == book.getTitle())&&(author==book.getAuthor()) && (publisher==book.getPublisher())) {
		return true;
	}
	else
		return false;
}


// 책 추가
void Book::addBook(vector<Book>& bookList, int isbn) {
	int idx = this->compareBook(bookList);
	
	if (idx != -1) {
		cout << "check1";
		bookList[idx].addEachBook(isbn);
	}
	// 책이 존재하지 않는 경우 List에 추가
	else {
		cout << "check2";
		int n = bookList.size();
		bookList.push_back({ *this });
		bookList[n].addEachBook(isbn);
	}
}

// 책이 존재하는 경우 기존의 책 객체에서 isbn만 추가
void Book::addEachBook(int isbn) {
	this->each.push_back(EachBook(isbn));
}

// 책 제목 반환
string Book::getTitle() const {
	return this->title;
}
// 책 저자 반환
string Book::getAuthor() const {
	return this->author;
}
// 책 출판사 반환
string Book::getPublisher() const {
	return this->publisher;
}


// 해당하는 제목의 책이 있는 경우 isbn 반환
int Book::getBookISBN() const {
	if (each.size() == 0)
		return -1;				// 재고 없음

	return each[each.size() - 1].getISBN();	// ISBN 출력
}


// 책 목록 출력
void Book::showBook() const {
	for (int i = 0; i < this->each.size(); i++) {
		EachBook eachbook = this->each[i];

		cout << "책 제목 : " << this->getTitle() << endl;
		cout << "책 저자 : " << this->getAuthor() << endl;
		cout << "출판사 : " << this->getPublisher() << endl;
		cout << "ISBN : " << eachbook.getISBN() << endl;
		if(!eachbook.available())
			cout << "대출 가능 여부 : yes" << endl;
		else
			cout << "대출 가능 여부 : no" << endl;
	}
}

// 책 대출
Book Book::borrowBook(int isbn, const string& title) 
{
	Book noExist;

	try {
		for (auto& it : each) {
			if (it.getISBN() == isbn) {
				// 대여가 가능한 상태일 경우
				if (!it.available()) {
					cout << "책 제목 : " << title << "\tISBN: " << isbn << " 책을 대출합니다.\n";
					it.borrow(isbn);
					// Book 반환
					return *this;
				}
			}
		}
		// 대여가 가능한 책이 없는 경우
		return noExist;
	}

	catch (exception& e) {
		cout << "대출 불가\n";
	}
}
//책 반납
void Book::returnBook(vector<Book>& booklist, int isbn) {
	bool bookExist = returnISBN(booklist, isbn);
	//존재하는 책인 경우
	if (bookExist) {
		cout << "반납 성공" << endl;
	}
	else {
		cout << "반납 불가" << endl;
	}
}

// booklist에 해당하는 isbn의 책 검색
bool Book::searchISBN(vector<Book>& booklist, int isbn) {
	for (int i = 0; i < booklist.size(); i++) {
		for (int j = 0; j < booklist[i].each.size(); j++) {
			if (booklist[i].each[j].getISBN() == isbn) {
				return true;
			}
		}
	}
	return false;
}

// 해당하는 isbn의 책이 있다면 반환
bool Book::returnISBN(vector<Book>& booklist, int isbn) {
	for (int i = 0; i < booklist.size(); i++) {
		for (int j = 0; j < booklist[i].each.size(); j++) {
			EachBook& book = booklist[i].each[j];

			if (book.getISBN() == isbn) {
				cout << "해당하는 isbn : " << book.getISBN() << "의 책을 찾았습니다." << endl;
				book.returnBook();
				cout << book.available() << endl;

				return true;
			}
		}
	}
	return false;
}

EachBook::EachBook() :EachBook(0) {}

EachBook::EachBook(int ISBN) {
	this->ISBN = ISBN;
	this->borrow_status = false;
}

void EachBook::setISBN(int isbn) {
	this->ISBN = isbn;
}
int EachBook::getISBN() const {
	return ISBN;
}
bool EachBook::available() {
	return borrow_status;
}

void EachBook::borrow(int ISBN) {
	borrow_status = true;					// 대여 중
}

void EachBook::returnBook() {
	borrow_status = false;					// 반환
}


string EachBook::getTitle() const {
	return Book::getTitle();
}

void EachBook::setTitle(string title) {
	this->title = title;
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

			temp.setBookInfo(title, author, publisher);
			temp.addBook(vBook, isbn++);
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