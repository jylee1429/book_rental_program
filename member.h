#ifndef _MEMBER_H_
#define _MEMBER_H_

#include <map>
using namespace std;

class Member;
class Book;


typedef shared_ptr<Member> Member_ptr;
typedef map<unsigned int, shared_ptr<Member>> Member_maps;


class MemberList {
	map<unsigned int, shared_ptr<Member>> list;		// 회원 정보 리스트 : <id, Member>
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
	int borrowed_cnt;	//	현재 빌린 책 수
	int overdue_cnt;	//  반납이 안된 책 수
	map<int, Book> overduebooks;	// 미반납된 책 리스트 : <ISBN, Book>
	map<int, Book> borrowedbooks;	// 빌린 책 리스트 : <ISBN, Book>
	string name;		//  이름
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

