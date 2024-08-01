#ifndef _EACHBOOK_H_
#define _EACHBOOK_H_
#include "book.h"

class EachBook :public Book {
protected:
	int ISBN;
	bool borrow; //대출 여부

public:
	EachBook();
	EachBook(int ISBN);

	void setISBN(int isbn);
	int getISBN();
	bool available();

	void borrow(int ISBN);

};
#endif