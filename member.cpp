#include <iostream>
#include <string>
#include <memory>

using namespace std;

#include "member.h"


/*				MemberList함수				*/


// 회원 등록
void MemberList::memberRegister(void) {
	unsigned int id;
	string name;

	// 회원 정보 입력
	inputInfo(id, name);
	Member_ptr mem = make_shared<Member>(id, name);
	//예외 처리

	list.insert({ id, mem });
}

// 회원 리스트 출력
void MemberList::memberShow(void) const {
	for (const auto& it : list) {
		cout << "ID: " << it.second->getID() << ", Name: " << it.second->getName() << endl;
		cout << "-----현재 빌린 책 목록-----" << endl;
		// it.second->showBorrowed();
		cout << endl;
		cout << "-----현재 미납된 책 목록-----" << endl;
		it.second->showOverdue();
		cout << endl;
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
void MemberList::memberBorrowBooks(int id, int isbn) {
	if (list.find(id) != list.end()) {
		list[id]->borrowBooks(isbn);
	}
	else {
		cout << "해당하는 회원이 없습니다" << endl;
		return;
	}
}

void MemberList::memberBorrowList(Member_maps::iterator it) {
	// it.first : id, it.second : member

	
}

void MemberList::memberOverdueList(Member_maps::iterator& it) {


}



/*				Member함수				*/

Member::Member(int id = 0, int  borrowed_cnt = 0, int overdue_cnt = 0, string name = "") {
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
	if (overduebooks.find(isbn) != overduebooks.end()) {
		overduebooks.erase(isbn);	// data 삭제
		cout << "책이 반납되었습니다" << endl;
	}
	else {
		cout << "해당하는 책이 없습니다" << endl;
		return;
	}
}
// 책 대여
void Member::borrowBooks(int isbn) {
	if (book.find(isbn) != book.end()) {
		if (book[isbn]->대출가능 여부) {
			// 대출이 불가능한 경우
			// overduebooks.insert(isbn, book[isbn]);
			// 해당 책은 대출 불가능
		}
		else {
			cout << "해당 책은 대출된 상태입니다." << endl;
		}
		
	}
	// 책 목록에 해당하는 isbn의 책이 없는경우(예외 처리)
	else {
		cout << "해당하는 책이 없습니다" << endl;
	}
	
}

void Member::showOverdue(void) const {
	for (const auto& it : overduebooks) {
		// cout << "ID: " << it.second->getName() << ", Name: " << it.second->getName() << endl;
		// 책 정보 출력
	}
}
void Member::showBorrowed(void) const {
	for (const auto& it : borrowedbooks) {
		// cout << "ID: " << it.second->getName() << ", Name: " << it.second->getName() << endl;
		// 책 정보 출력
	}
}



/*				외부 함수				*/
void inputInfo(unsigned int& id, string& name) {
	cout << "ID와 이름을 차례대로 입력하세요 << ";
	cin >> id >> name;
}

