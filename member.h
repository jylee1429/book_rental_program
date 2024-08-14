#ifndef _MEMBER_H_
#define _MEMBER_H_

#include <map>
using namespace std;

#include "book.h"

#define INIT_AVAILABLE_BORROW 10

class Member;

typedef shared_ptr<Member> Member_ptr;
typedef map<unsigned int, shared_ptr<Member>> Member_maps;


class MemberManage {
    Member_maps list;
    BookManage& bookManage;
public:
    MemberManage(BookManage& bookmanage) : bookManage(bookmanage) {}
    bool memberRegister(unsigned int id, string name, string callNumber);
    bool checkAvailableID(unsigned int id);
    void memberShow(vector<Member_ptr>& memberList);
    bool memberReturnBooks(unsigned int id, string isbn);
    bool memberBorrowBooks(unsigned int id, string isbn);
    bool getInfoByID(unsigned int id, Member_ptr& member);
    bool checkBorrowedBook(unsigned id, string isbn, Book_ptr& book);
};

class Member {
    unsigned int id;
    unsigned int availableBorrow;
    unsigned int borrowedCnt;
    unsigned int overdueCnt;
    Book_maps overduebooks;
    Book_maps borrowedbooks;
    string name;
    string callNumber;
public:
    Member(unsigned int id = 0, string name = "", string callNumber = "");
    void setName(string& name);
    string getName(void) const;
    void setID(unsigned int id);
    unsigned int getID(void) const;
    void setCallNumber(string& callNumber);
    string getCallNumber(void) const;
    unsigned int getAvailableBorrow(void) const;
    unsigned int getBorrowedCnt(void) const;
    unsigned int getOverdueCnt(void) const;																														//
    bool searchBorrowBook(string& isbn, Book_ptr& book);
    void insertBorrowedList(string& isbn, Book_ptr& book);
    bool deleteBorrowedList(string& isbn);
    Book_maps returnBorrowBooks(void);
    Book_maps returnOverdueBooks(void);
    bool memberBorrowBook(void);
    bool memberReturnBook(void);
};



#endif

