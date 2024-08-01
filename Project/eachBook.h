#include "book.h"


class EachBook : public Book {
protected:
	int ISBN;
	bool borrow_status; //대출 여부

public:
	EachBook();
	EachBook(int ISBN);

	void setISBN(int isbn);
	int getISBN();
	bool available();

	void borrow(int ISBN);

};