#include "book.h"

class EachBook :public Book {
protected:
	int ISBN;
	bool borrow; //���� ����

public:
	EachBook();
	EachBook(int ISBN);

	void setISBN(int isbn);
	int getISBN();
	bool available();

	void borrow(int ISBN);

};