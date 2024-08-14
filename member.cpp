#include <iostream>
#include <string.h>
#include <memory>
#include <QDebug>
using namespace std;

#include "member.h"
#include "book.h"



/*				MemberList함수				*/
bool MemberManage::memberRegister(unsigned int id, string name, string callNumber) {
    if(!checkAvailableID(id)){
        return false;
    }

    Member_ptr mem = make_shared<Member>(id, name, callNumber);
    if (!mem) {
        return false;
    }

    list.insert({ id, mem });
    return true;
}

bool MemberManage::checkAvailableID(unsigned int id) {
    auto it = list.find(id);

    if(it != list.end()){
        return false;
    }
    else{
        return true;
    }
}

void MemberManage::memberShow(vector<Member_ptr>& memberList){
    for (const auto& it : list) {
        memberList.push_back(it.second);
    }
}

bool MemberManage::memberReturnBooks(unsigned int id, string isbn) {
    auto it = list.find(id);
    // id에 해당하는 회원이 있는경우
    if (it != list.end()) {
        // 빌린 책 중 isbn에 해당하는 책이 있는 경우
        if (list[id]->deleteBorrowedList(isbn)) {
            this->bookManage.returnBook(isbn);
            list[id]->memberReturnBook();
            return true;
        }
        else
            return false;
    }
    // id에 해당하는 회원이 없는 경우
    else {
        return false;
    }
}

// id에 해당하는 회원 책 대출
bool MemberManage::memberBorrowBooks(unsigned int id, string isbn) {
    Book_ptr book;
    auto it = list.find(id);

    // id에 해당하는 회원이 있는경우
    if (it != list.end()) {
        // isbn에 해당하는 책을 빌렸을 경우
        if (this->bookManage.borrowBook(isbn, book) && list[id]->memberBorrowBook()) {
            list[id]->insertBorrowedList(isbn, book);
            return true;
        }
        else
            return false;
    }
    // id에 해당하는 회원이 없는 경우
    else {
        return false;
    }
}

bool MemberManage::getInfoByID(unsigned int id, Member_ptr& member) {
    auto it = list.find(id);

    // 회원이 존재
    if (it != list.end()) {
        member = it->second;
        return true;
    }
    else
        return false;
}

bool MemberManage::checkBorrowedBook(unsigned id, string isbn, Book_ptr& book){
    auto it = list.find(id);
    // id에 해당하는 회원이 있는경우
    if (it != list.end()) {
        // 빌린 책 중 isbn에 해당하는 책이 있는 경우
        if (list[id]->searchBorrowBook(isbn, book)) {
            return true;
        }
        else
            return false;
    }
    return false;
}

/*				Member함수				*/

Member::Member(unsigned int id, string name, string callNumber) {
    this->id = id;
    this->availableBorrow = INIT_AVAILABLE_BORROW;
    this->borrowedCnt = 0;
    this->overdueCnt = 0;
    this->name = name;
    this->callNumber = callNumber;
}

string Member::getName(void) const {
    return name;
}

unsigned int Member::getID(void) const {
    return id;
}

string Member::getCallNumber(void) const {
    return callNumber;
}

unsigned int Member::getAvailableBorrow(void) const {
    return availableBorrow;
}

unsigned int Member::getBorrowedCnt(void) const {
    return borrowedCnt;
}

unsigned int Member::getOverdueCnt(void) const {
    return overdueCnt;
}

void Member::setID(unsigned int id) {
    this->id = id;
}

void Member::setName(string& name) {
    this->name = name;
}

void Member::setCallNumber(string& name) {
    this->callNumber = callNumber;
}

bool Member::memberBorrowBook(void) {
    if (availableBorrow < 1) {
        return false;
    }
    availableBorrow--;
    return true;
}

bool Member::memberReturnBook(void) {
    availableBorrow++;
    if (availableBorrow > INIT_AVAILABLE_BORROW)
        availableBorrow = INIT_AVAILABLE_BORROW;

    return true;
}

bool Member::searchBorrowBook(string& isbn, Book_ptr& book) {
    auto it = this->borrowedbooks.find(isbn);

    // 빌린 책 중 해당하는 isbn이 존재
    if (it != this->borrowedbooks.end()) {
        book = it->second;
        return true;
    }
    else
        return false;
}

void Member::insertBorrowedList(string& isbn, Book_ptr& book) {
    this->borrowedbooks.insert({ isbn,book });
}




bool Member::deleteBorrowedList(string& isbn) {
    auto it = this->borrowedbooks.find(isbn);

    // 빌린 책 중 해당하는 isbn이 존재
    if (it != this->borrowedbooks.end()) {
        this->borrowedbooks.erase(it);
        return true;
    }
    else
        return false;
}
