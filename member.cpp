#include <iostream>
#include <string>
#include <memory>

using namespace std;

#include "member.h"


/*				MemberList�Լ�				*/


// ȸ�� ���
void MemberList::memberRegister(void) {
	unsigned int id;
	string name;

	// ȸ�� ���� �Է�
	inputInfo(id, name);
	Member_ptr mem = make_shared<Member>(id, name);
	//���� ó��

	list.insert({ id, mem });
}

// ȸ�� ����Ʈ ���
void MemberList::memberShow(void) const {
	for (const auto& it : list) {
		cout << "ID: " << it.second->getID() << ", Name: " << it.second->getName() << endl;
		cout << "-----���� ���� å ���-----" << endl;
		// it.second->showBorrowed();
		cout << endl;
		cout << "-----���� �̳��� å ���-----" << endl;
		it.second->showOverdue();
		cout << endl;
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
void MemberList::memberBorrowBooks(int id, int isbn) {
	if (list.find(id) != list.end()) {
		list[id]->borrowBooks(isbn);
	}
	else {
		cout << "�ش��ϴ� ȸ���� �����ϴ�" << endl;
		return;
	}
}

void MemberList::memberBorrowList(Member_maps::iterator it) {
	// it.first : id, it.second : member

	
}

void MemberList::memberOverdueList(Member_maps::iterator& it) {


}



/*				Member�Լ�				*/

Member::Member(int id = 0, int  borrowed_cnt = 0, int overdue_cnt = 0, string name = "") {
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
	if (overduebooks.find(isbn) != overduebooks.end()) {
		overduebooks.erase(isbn);	// data ����
		cout << "å�� �ݳ��Ǿ����ϴ�" << endl;
	}
	else {
		cout << "�ش��ϴ� å�� �����ϴ�" << endl;
		return;
	}
}
// å �뿩
void Member::borrowBooks(int isbn) {
	if (book.find(isbn) != book.end()) {
		if (book[isbn]->���Ⱑ�� ����) {
			// ������ �Ұ����� ���
			// overduebooks.insert(isbn, book[isbn]);
			// �ش� å�� ���� �Ұ���
		}
		else {
			cout << "�ش� å�� ����� �����Դϴ�." << endl;
		}
		
	}
	// å ��Ͽ� �ش��ϴ� isbn�� å�� ���°��(���� ó��)
	else {
		cout << "�ش��ϴ� å�� �����ϴ�" << endl;
	}
	
}

void Member::showOverdue(void) const {
	for (const auto& it : overduebooks) {
		// cout << "ID: " << it.second->getName() << ", Name: " << it.second->getName() << endl;
		// å ���� ���
	}
}
void Member::showBorrowed(void) const {
	for (const auto& it : borrowedbooks) {
		// cout << "ID: " << it.second->getName() << ", Name: " << it.second->getName() << endl;
		// å ���� ���
	}
}



/*				�ܺ� �Լ�				*/
void inputInfo(unsigned int& id, string& name) {
	cout << "ID�� �̸��� ���ʴ�� �Է��ϼ��� << ";
	cin >> id >> name;
}

