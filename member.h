#ifndef _MEMBER_H_
#define _MEMBER_H_

#include <map>
#include <QStringList>
using namespace std;

#include "book.h"

class Member;

typedef shared_ptr<Member> Member_ptr;
typedef map<int, shared_ptr<Member>> Member_maps;

typedef map<int, shared_ptr<Book>> book_maps;

class MemberManage {
	Member_maps list;				// ȸ�� ���� ����Ʈ : <id, Member>

public:
    void memberRegister(int id, string name, string tel);
    Member_maps memberShow(void) const;
	void memberBorrowList(Member_maps::iterator& it);
	void memberOverdueList(Member_maps::iterator& it);
	void memberReturnBooks(vector<Book>& booklist, int id, int isbn);
    bool memberBorrowBooks(vector<Book>& book, int id, string title);
	void showBoookList(vector<Book>& booklist) const;
        bool checkID(int id, string& name);
};

class Member {
	int id;							//	id
	int borrowed_cnt;				//	���� ���� å ��
    int overdue_cnt;                        	//  �ݳ��� �ȵ� å ��
	map<int, Book> overduebooks;	//  �̹ݳ��� å ����Ʈ : <ISBN, Book>
	map<int, Book> borrowedbooks;	//  ���� å ����Ʈ : <ISBN, Book>
    string name;                                    //  �̸�
        string tel;                                       // ��ȭ��ȣ
public:
    Member(int id = 0, int  borrowed_cnt = 0, int overdue_cnt = 0, string name = " ", string tel = " ");
	string getName(void) const;
	int getID(void) const;
    string getTel(void)const;
	int getBorrowedCnt(void) const;
	int getOverdueCnt(void) const;
	void returnBooks(vector<Book>& booklist, int isbn);
    bool borrowBooks(vector<Book>& book, string& title);
	void showOverdue(void) const;
	void showBorrowed(void) const;
        QStringList checkReturnBook(int isbn);
};


void inputInfo(int& id, string& name);
bool sortCriteria(Book a, Book b);
#endif

