#ifndef _MEMBER_H_
#define _MEMBER_H_

#include <map>
using namespace std;

class Member;
class Book;


typedef shared_ptr<Member> Member_ptr;
typedef map<unsigned int, shared_ptr<Member>> Member_maps;


class MemberList {
	map<unsigned int, shared_ptr<Member>> list;		// ȸ�� ���� ����Ʈ : <id, Member>
public:
	void memberRegister(void);
	void memberShow(void) const;
	void memberBorrowList(Member_maps::iterator it);
	void memberOverdueList(Member_maps::iterator& it);
	void memberReturnBooks(int id, int isbn);
	void memberBorrowBooks(int id, int isbn);
};

class Member {
	unsigned int id;				//	id
	int borrowed_cnt;	//	���� ���� å ��
	int overdue_cnt;	//  �ݳ��� �ȵ� å ��
	map<int, Book> overduebooks;	// �̹ݳ��� å ����Ʈ : <ISBN, Book>
	map<int, Book> borrowedbooks;	// ���� å ����Ʈ : <ISBN, Book>
	string name;		//  �̸�
public:
	Member(int id = 0, int  borrowed_cnt = 0, int overdue_cnt = 0, string name = "");
	string getName(void) const;
	int getID(void) const;
	int getBorrowedCnt(void) const;
	int getOverdueCnt(void) const;
	void returnBooks(int isbn);
	void borrowBooks(int isbn);
	void showOverdue(void) const;
	void showBorrowed(void) const;
};


void inputInfo(unsigned int& id, string& name);

#endif

