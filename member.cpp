#include <iostream>
#include <string.h>
#include <memory>

using namespace std;

#include "member.h"
#include "book.h"


extern vector<Book> book_list;

/*				MemberList함수				*/


// 회원 등록
void MemberList::memberRegister(void) {
	int id;
	string name;

	// 회원 정보 입력
	inputInfo(id, name);
	Member_ptr mem = make_shared<Member>(id, 0, 0, name);
	//예외 처리

	list.insert({ id, mem });
}

// 회원 리스트 출력
void MemberList::memberShow(void) const {
	for (const auto& it : list) {
		cout << "ID: " << it.second->getID() << ", Name: " << it.second->getName() << endl;
		cout << "-----현재 빌린 책 목록-----" << endl;
		it.second->showBorrowed();
		cout << endl;
		//cout << "-----현재 미납된 책 목록-----" << endl;
		//it.second->showOverdue();
		//cout << endl;
	}
}

// id에 해당하는 회원 책 반납
void MemberList::memberReturnBooks(int id, int isbn) {
	if (list.find(id) != list.end()) {
		list[id]->returnBooks(isbn);
	}
	else {
		cout << "해당하는 회원이 없습니다" << endl;
		return;
	}
}

// id에 해당하는 회원 책 대출
void MemberList::memberBorrowBooks(int id, string title) {
	if (list.find(id) != list.end()) {
		list[id]->borrowBooks(title);
	}
	else {
		cout << "해당하는 회원이 없습니다" << endl;
		return;
	}
}

void MemberList::memberBorrowList(Member_maps::iterator& it) {
	// it.first : id, it.second : member
	cout << "-----현재 빌린 책 목록-----" << endl;
	(*it).second->showBorrowed();
	cout << endl;
}

void MemberList::memberOverdueList(Member_maps::iterator& it) {
	cout << "-----현재 빌린 책 목록-----" << endl;
	(*it).second->showBorrowed();
	cout << endl;
}



/*				Member함수				*/

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
void Member::returnBooks(int isbn) {

	//auto it = overduebooks.find(isbn);

	//if (it != overduebooks.end()) {
	//	book_list.push_back(it->second);
	//	overduebooks.erase(it);
	//	cout << "책이 반납되었습니다" << endl;
	//}
	//else {
	//	cout << "해당하는 책이 없습니다" << endl;
	//	return;
	//}
	auto it = borrowedbooks.find(isbn);

	if (it != borrowedbooks.end()) {
		(*it).second.returnBook(isbn);
		borrowedbooks.erase(it);
	}
	else {
		cout << "해당하는 책이 없습니다" << endl;
		return;
	}
}

// 책 대여
void Member::borrowBooks(string& title) {
	for (auto it = book_list.begin(); it != book_list.end(); it++) {
		if (title == it->getTitle()) {
			auto tmp = it->borrowBook(it->getBookISBN(), title);
			cout << "tmp.getTitle() = " << tmp.getTitle() << endl;
			borrowedbooks.insert({ it->getBookISBN(),tmp });
			break;  // 한 권만 빌리면 반복을 종료
		}
	}
}

void Member::showOverdue(void) const {
	for (auto& it : overduebooks) {
		cout << "책이름 : " << it.second.getTitle() << "저자 : " << it.second.getAuthor() << "출판사 : " << it.second.getPublisher() << endl;
	}
}
void Member::showBorrowed(void) const {
	for (auto it : borrowedbooks) {

		cout << "책이름 : " << it.second.getTitle() << "저자 : " << it.second.getAuthor() << "출판사 : " << it.second.getPublisher() << endl;
	}
}


/*				외부 함수				*/
void inputInfo(int& id, string& name) {
	cout << "회원 ID : ";
	cin >> id;
	cout << "이름 : ";
	cin >> name;
}
