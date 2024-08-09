#include <iostream>
#include <string.h>
#include <memory>

using namespace std;

#include "member.h"
#include "book.h"
#include <QStringList>

extern vector<Book> book_list;

/*				MemberList함수				*/


// 회원 등록
void MemberManage::memberRegister(int id, string name) {
	//   int id;
	  // string name;

	   // 회원 정보 입력
	  // inputInfo(id, name);
	Member_ptr mem = make_shared<Member>(id, 0, 0, name);
	//예외 처리

	list.insert({ id, mem });
}

// 회원 리스트 출력
Member_maps MemberManage::memberShow(void) const {
	return list;
}

bool MemberManage::checkID(int id, string& name) {
	if (list.find(id) != list.end()) {
		name = list[id]->getName();
		return true;
	}
	return false;
}
// id에 해당하는 회원 책 반납
void MemberManage::memberReturnBooks(vector<Book>& booklist, int id, int isbn) {
	if (list.find(id) != list.end()) {
		list[id]->returnBooks(booklist, isbn);
	}
	else {
		cout << "해당하는 회원이 없습니다" << endl;
		return;
	}
}

// id에 해당하는 회원 책 대출
void MemberManage::memberBorrowBooks(vector<Book>& book, int id, string title) {
	if (list.find(id) != list.end()) {
		list[id]->borrowBooks(book, title);
	}
	else {
		// cout << "해당하는 회원이 없습니다" << endl;
		return;
	}
}
// 빌린 책 목록 출력
void MemberManage::memberBorrowList(Member_maps::iterator& it) {
	cout << "-----현재 빌린 책 목록-----" << endl;
	(*it).second->showBorrowed();
	cout << endl;
}

void MemberManage::memberOverdueList(Member_maps::iterator& it) {
	cout << "-----현재 빌린 책 목록-----" << endl;
	(*it).second->showBorrowed();
	cout << endl;
}

void MemberManage::showBoookList(vector<Book>& booklist) const {
	int idx = 0;
	sort(booklist.begin(), booklist.end(), sortCriteria);

	for (auto& it : booklist) {
		cout << "[" << idx++ << "]\n";
		it.showBook();
		cout << endl;
	}
}
// 책 정렬 기준
bool sortCriteria(Book a, Book b) {
	if (a.getTitle() < b.getTitle())
		return true;
	else
		return false;
}

/*				Member함수				*/
// Constructor
Member::Member(int id, int  borrowed_cnt, int overdue_cnt, string name) {
	this->id = id;
	this->borrowed_cnt = borrowed_cnt;
	this->overdue_cnt = overdue_cnt;
	this->name = name;
}

// 회원 이름 출력
string Member::getName(void) const {
	return name;
}
// 회원 ID 출력
int Member::getID(void) const {
	return id;
}
// 현재 빌린 책 수 출력
int Member::getBorrowedCnt(void) const {
	return borrowed_cnt;
}
// 미납된 책 수 출력
int Member::getOverdueCnt(void) const {
	return overdue_cnt;
}
// 책 반환
void Member::returnBooks(vector<Book>& booklist, int isbn) {
	// 해당하는 isbn의 책이 있는지 검색
	auto it = borrowedbooks.find(isbn);
	// 책이 있는 경우
	if (it != borrowedbooks.end()) {
		(*it).second.returnBook(booklist, isbn);
		borrowedbooks.erase(it);
	}
	else {
		cout << "해당하는 책이 없습니다" << endl;
	}
}
// 반납할 책 isbn으로 검색
QStringList Member::checkReturnBook(int isbn)
{
	auto it = borrowedbooks.find(isbn);
	QStringList list;
	if (it != borrowedbooks.end()) //책이 있는 경우
		list << QString::fromStdString(it->second.getTitle()) << QString::fromStdString(it->second.getAuthor()) << QString::fromStdString(it->second.getPublisher());
	else
		list << "";

	return list;
}

// 책 대여
void Member::borrowBooks(vector<Book>& book, string& title) {
	for (auto it = book.begin(); it != book.end(); it++) {
		// 같은 이름의 책이 있는 경우
		if (title == it->getTitle()) {
			int isbn = it->getBookISBN();
			// 책이 없는 경우
			if (isbn == -1) {
				// cout << "책이 없습니다." << endl;
			}
			// 해당 책 대여
			auto tmp = it->borrowBook(isbn, title);

			if (tmp.getTitle() != "-") {
				borrowedbooks.insert({ it->getBookISBN(),tmp });
				// 한 권만 빌리면 반복을 종료
				return;
			}
		}
	}

	cout << "대출 가능한 책이 없습니다.\n";
}
// 연체된 책 목록 출력
void Member::showOverdue(void) const {
	for (auto& it : overduebooks) {
		cout << "책이름 : " << it.second.getTitle() << "\t저자 : " << it.second.getAuthor() << "\t출판사 : " << it.second.getPublisher() << endl;
	}
}
// 대여한 책 목록 출력
void Member::showBorrowed(void) const {
	for (auto it : borrowedbooks) {
		cout << "책이름 : " << it.second.getTitle() << "\t저자 : " << it.second.getAuthor() << "\t출판사 : " << it.second.getPublisher() << endl;
	}
}


/*				외부 함수				*/
void inputInfo(int& id, string& name) {
	cout << "회원 ID : ";
	cin >> id;
	cout << "이름 : ";
	cin >> name;
}
