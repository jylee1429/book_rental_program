#include <iostream>
#include <string.h>
#include <memory>

using namespace std;

#include "member.h"
#include "book.h"


extern vector<Book> book_list;

/*				MemberList�Լ�				*/


// ȸ�� ���
void MemberList::memberRegister(void) {
	int id;
	string name;

	// ȸ�� ���� �Է�
	inputInfo(id, name);
	Member_ptr mem = make_shared<Member>(id, 0, 0, name);
	//���� ó��

	list.insert({ id, mem });
}

// ȸ�� ����Ʈ ���
void MemberList::memberShow(void) const {
	for (const auto& it : list) {
		cout << "ID: " << it.second->getID() << ", Name: " << it.second->getName() << endl;
		cout << "-----���� ���� å ���-----" << endl;
		it.second->showBorrowed();
		cout << endl;
		//cout << "-----���� �̳��� å ���-----" << endl;
		//it.second->showOverdue();
		//cout << endl;
	}
}

// id�� �ش��ϴ� ȸ�� å �ݳ�
void MemberList::memberReturnBooks(int id, int isbn) {
	if (list.find(id) != list.end()) {
		list[id]->returnBooks(isbn);
	}
	else {
		cout << "�ش��ϴ� ȸ���� �����ϴ�" << endl;
		return;
	}
}

// id�� �ش��ϴ� ȸ�� å ����
void MemberList::memberBorrowBooks(int id, string title) {
	if (list.find(id) != list.end()) {
		list[id]->borrowBooks(title);
	}
	else {
		cout << "�ش��ϴ� ȸ���� �����ϴ�" << endl;
		return;
	}
}

void MemberList::memberBorrowList(Member_maps::iterator& it) {
	// it.first : id, it.second : member
	cout << "-----���� ���� å ���-----" << endl;
	(*it).second->showBorrowed();
	cout << endl;
}

void MemberList::memberOverdueList(Member_maps::iterator& it) {
	cout << "-----���� ���� å ���-----" << endl;
	(*it).second->showBorrowed();
	cout << endl;
}



/*				Member�Լ�				*/

Member::Member(int id, int  borrowed_cnt, int overdue_cnt, string name) {
	this->id = id;
	this->borrowed_cnt = borrowed_cnt;
	this->overdue_cnt = overdue_cnt;
	this->name = name;
}

// ȸ�� �̸� ���
string Member::getName(void) const {
	return name;
}
// ȸ�� ID ���
int Member::getID(void) const {
	return id;
}
// ���� ���� å �� ���
int Member::getBorrowedCnt(void) const {
	return borrowed_cnt;
}
// �̳��� å �� ���
int Member::getOverdueCnt(void) const {
	return overdue_cnt;
}
// å ��ȯ
void Member::returnBooks(int isbn) {

	//auto it = overduebooks.find(isbn);

	//if (it != overduebooks.end()) {
	//	book_list.push_back(it->second);
	//	overduebooks.erase(it);
	//	cout << "å�� �ݳ��Ǿ����ϴ�" << endl;
	//}
	//else {
	//	cout << "�ش��ϴ� å�� �����ϴ�" << endl;
	//	return;
	//}
	auto it = borrowedbooks.find(isbn);

	if (it != borrowedbooks.end()) {
		(*it).second.returnBook(isbn);
		borrowedbooks.erase(it);
	}
	else {
		cout << "�ش��ϴ� å�� �����ϴ�" << endl;
		return;
	}
}

// å �뿩
void Member::borrowBooks(string& title) {
	for (auto it = book_list.begin(); it != book_list.end(); it++) {
		if (title == it->getTitle()) {
			auto tmp = it->borrowBook(it->getBookISBN(), title);
			cout << "tmp.getTitle() = " << tmp.getTitle() << endl;
			borrowedbooks.insert({ it->getBookISBN(),tmp });
			break;  // �� �Ǹ� ������ �ݺ��� ����
		}
	}
}

void Member::showOverdue(void) const {
	for (auto& it : overduebooks) {
		cout << "å�̸� : " << it.second.getTitle() << "���� : " << it.second.getAuthor() << "���ǻ� : " << it.second.getPublisher() << endl;
	}
}
void Member::showBorrowed(void) const {
	for (auto it : borrowedbooks) {

		cout << "å�̸� : " << it.second.getTitle() << "���� : " << it.second.getAuthor() << "���ǻ� : " << it.second.getPublisher() << endl;
	}
}


/*				�ܺ� �Լ�				*/
void inputInfo(int& id, string& name) {
	cout << "ȸ�� ID : ";
	cin >> id;
	cout << "�̸� : ";
	cin >> name;
}
