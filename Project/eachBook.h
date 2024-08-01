#ifndef _EACHBOOK_H_
#define _EACHBOOK_H_
#include "book.h"

class EachBook : public Book {
protected:
	int ISBN;
	bool borrow_status; //���� ����

public:
	EachBook();
	EachBook(int ISBN);

	void setISBN(int isbn);
	int getISBN();
	bool available();

	void borrow(int ISBN); //å ����
	void return_book(); //å �ݳ�
};
#endif