#ifndef _BOOK_H_
#define _BOOK_H_

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <map>
#include <algorithm>
#include <cstdint>

using namespace std;


class EachBook;
class Date;

typedef shared_ptr<EachBook> Book_ptr;
typedef map<string, Book_ptr> Book_maps;
typedef multimap<string, Book_ptr> Book_multi_maps;


class BookManage {
    Book_maps list;
    Book_multi_maps multi_list;
public:
    string generateISBN(string& title);                                                                      // ISBN생성
    void bookRegister(string title, string author, string publisher);                                        // 새로운 책 등록
    void bookInsert(string& title, string& author, string& publisher, string& isbn);                         // 기존의 책 등록
    bool searchBookByTitle(vector<Book_ptr>& bookList, string title, int& total_cnt, int& enable_cnt);       // 책 제목을 이용한 검색
    bool searchBookISBN(string isbn, Book_ptr& book);                                                        // 책 ISBN을 이용한 검색
    void showBookList(vector<Book_ptr>& bookList) const;                                                     // 전체 책 목록 출력
    bool borrowBook(string title, Book_ptr& book);                                                           // 책 대여
    bool returnBook(string& isbn);                                                                           // 책 반납
    int sizeList(void);                                                                                      // 책 목록 크기 출력
};

class Book {
protected:
    string title;				// 제목
    string author;				// 저자
    string publisher;			// 출판사
public:
    Book(string title = "", string author = "", string publisher = "");
    virtual void setTitle(string title) = 0;
    virtual string getTitle(void) const = 0;
    virtual void setAuthor(string author) = 0;
    virtual string getAuthor(void) const = 0;
    virtual void setPublisher(string publisher) = 0;
    virtual string getPublisher(void) const = 0;
};

class EachBook : public Book {
    string ISBN;							// 고유식별 번호
    Date borrowDate();						// 대출 일자
    Date returnDate();						// 반납 예정 일자
    bool isBorrow;							// 대출 여부
    bool isOverdue;
public:
    EachBook(string isbn = "", bool isBorrow = false, bool isOverdue = false);              // 생성자 설정
    void setTitle(string title);															// 책 이름 설정
    string getTitle(void) const;															// 책 이름 출력
    void setAuthor(string author);															// 책 저자 설정
    string getAuthor(void) const;                                                           // 책 저자 출력
    void setPublisher(string publisher);                                                    // 책 출판사 설정
    string getPublisher(void) const;                                                		// 책 출판사 출력
    void setISBN(string isbn);																// 책 ISBN 설정
    string getISBN(void) const;																// 책 ISBN 출력
    void setIsBorrow(bool status);															// 책 대여가능여부 설정(true-> 불가능, false->가능)
    bool getIsBorrow(void) const;															// 책 대여가능여부 출력
    void setIsOverdue(bool isOverdue);														// 책 연체 여부 확인
    bool getIsOverdue(void) const;															// 책 연체 여부 출력
};


class Date {
    unsigned char year;
    unsigned char month;
    unsigned char day;
public:
    Date(unsigned char year = 0, unsigned char month = 0, unsigned char day = 0);			// 생성자 설정
    void setDate(unsigned char year, unsigned char month, unsigned char day);				// 년/월/일 설정
    unsigned char getYear(void);															// 년도 설정
    unsigned char getMonth(void);															// 월 설정
    unsigned char getDay(void);																// 날짜 설정
};

#endif
