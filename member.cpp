#include <iostream>
#include <string.h>
#include <memory>

using namespace std;

#include "member.h"
#include "book.h"


extern vector<Book> book_list;

/*				MemberList�Լ�				*/


// ȸ�� ���
void MemberManage::memberRegister(void) {
	int id;
	string name;

	// ȸ�� ���� �Է�
	inputInfo(id, name);
	Member_ptr mem = make_shared<Member>(id, 0, 0, name);
	//���� ó��

	list.insert({ id, mem });
}

// ȸ�� ����Ʈ ���
void MemberManage::memberShow(void) const {
	for (const auto& it : list) {
		cout << "ID: " << it.second->getID() << ", Name: " << it.second->getName() << endl;
		cout << "---------���� ���� å ���---------" << endl;
		it.second->showBorrowed();
		cout << endl;
	}
}

// id�� �ش��ϴ� ȸ�� å �ݳ�
void MemberManage::memberReturnBooks(vector<Book>& booklist, int id, int isbn) {
	if (list.find(id) != list.end()) {
		list[id]->returnBooks(booklist, isbn);
	}
	else {
		cout << "�ش��ϴ� ȸ���� �����ϴ�" << endl;
		return;
	}
}

// id�� �ش��ϴ� ȸ�� å ����
void MemberManage::memberBorrowBooks(vector<Book>& book, int id, string title) {
	if (list.find(id) != list.end()) {
		list[id]->borrowBooks(book, title);
	}
	else {
		cout << "�ش��ϴ� ȸ���� �����ϴ�" << endl;
		return;
	}
}
// ���� å ��� ���
void MemberManage::memberBorrowList(Member_maps::iterator& it) {
	cout << "-----���� ���� å ���-----" << endl;
	(*it).second->showBorrowed();
	cout << endl;
}

void MemberManage::memberOverdueList(Member_maps::iterator& it) {
	cout << "-----���� ���� å ���-----" << endl;
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
// å ���� ���� 
bool sortCriteria(Book a, Book b) {
	if (a.getTitle() < b.getTitle())
		return true;
	else
		return false;
}

/*				Member�Լ�				*/
// Constructor
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
void Member::returnBooks(vector<Book>& booklist, int isbn) {
	// �ش��ϴ� isbn�� å�� �ִ��� �˻�
	auto it = borrowedbooks.find(isbn);
	// å�� �ִ� ���
	if (it != borrowedbooks.end()) {
		(*it).second.returnBook(booklist, isbn);
		borrowedbooks.erase(it);
	}
	else {
		cout << "�ش��ϴ� å�� �����ϴ�" << endl;
	}
}
// å �뿩
void Member::borrowBooks(vector<Book>& book, string& title) {
	for (auto it = book.begin(); it != book.end(); it++) {
		// ���� �̸��� å�� �ִ� ���
		if (title == it->getTitle()) {
			int isbn = it->getBookISBN();
			// å�� ���� ���
			if (isbn == -1) {
				cout << "å�� �����ϴ�." << endl;
			}
			// �ش� å �뿩
			auto tmp = it->borrowBook(isbn, title);

			if (tmp.getTitle() != "-") {
				borrowedbooks.insert({ it->getBookISBN(),tmp });
				// �� �Ǹ� ������ �ݺ��� ����
				return;  
			}
		}
	}

	cout << "���� ������ å�� �����ϴ�.\n";
}
// ��ü�� å ��� ���
void Member::showOverdue(void) const {
	for (auto& it : overduebooks) {
		cout << "å�̸� : " << it.second.getTitle() << "\t���� : " << it.second.getAuthor() << "\t���ǻ� : " << it.second.getPublisher() << endl;
	}
}
// �뿩�� å ��� ���
void Member::showBorrowed(void) const {
	for (auto it : borrowedbooks) {
		cout << "å�̸� : " << it.second.getTitle() << "\t���� : " << it.second.getAuthor() << "\t���ǻ� : " << it.second.getPublisher() << endl;
	}
}


/*				�ܺ� �Լ�				*/
void inputInfo(int& id, string& name) {
	cout << "ȸ�� ID : ";
	cin >> id;
	cout << "�̸� : ";
	cin >> name;
}
