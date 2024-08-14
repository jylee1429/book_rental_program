#include "book.h"
#include <random>
#include <QDebug>
#include <filesystem>

// Constructor
Book::Book(string title, string author, string publisher) {
    this->title = title;
    this->author = author;
    this->publisher = publisher;
}

EachBook::EachBook(string isbn, bool isBorrow, bool isOverdue) {
    this->ISBN = isbn;
    this->isBorrow = isBorrow;
    this->isOverdue = isOverdue;
    this->author = "";
    this->publisher = "";
    this->title = "";
}


string BookManage::generateISBN(string& title) {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> dis(0, 9999);

    vector<string> v_str = { "가","나","다","라","마","바","사","아","자","차","카","타","파","하" };
    vector<char> c_str={'A','B','C','D','E','F','G','H','I','J','K','L','M','N'};

    string initISBN;
    string initial_str = title.substr(0,2);
    char initial = title[0];

    if (title.empty())
        return "unknown";

    if (initial_str[0] & 0x80) {
        int cnt = 0;
        for (auto it = v_str.begin(); it != v_str.end(); it++) {
            if (initial_str < *it) {;
                break;
            }
            cnt++;
        }
        initISBN=c_str[cnt];
    }
    else if ((initial >= 'A' && initial <= 'Z') || (initial >= 'a' && initial <= 'z')) {
        char ch = toupper(initial);
        initISBN = string(2, ch);
    }

    else {
        initISBN = "Z";
    }

    while(true) {
        int num = dis(gen);
        string isbn = initISBN + to_string(num);

        auto it = list.find(isbn);
        if (it == list.end()) {
            return isbn;
        }
    }
}

int BookManage::sizeList(void) {
    return this->list.size();
}

void BookManage::bookRegister(string title, string author, string publisher) {
    string isbn = this->generateISBN(title);
    Book_ptr book = make_shared<EachBook>(isbn, false, false);

    book->setTitle(title);
    book->setAuthor(author);
    book->setPublisher(publisher);

    list.insert({ isbn,book });
    multi_list.insert({ title, book });
}

void BookManage::bookInsert(string& title, string& author, string& publisher, string& isbn, bool isBorrow) {
    Book_ptr book = make_shared<EachBook>(isbn, isBorrow, false);

    book->setTitle(title);
    book->setAuthor(author);
    book->setPublisher(publisher);

    list.insert({ isbn,book });
    multi_list.insert({ title, book });
}

bool BookManage::searchBookByTitle(vector<Book_ptr>& bookList, string title, int& total_cnt, int& enable_cnt) {
    total_cnt = 0;
    enable_cnt = 0;

    auto range = multi_list.equal_range(title);
    if (range.first == range.second)
        return false;
    for (auto it = range.first; it != range.second; it++) {
        total_cnt++;
        if (!it->second->getIsBorrow())
            enable_cnt++;
        bookList.push_back(it->second);
    }
    return true;
}

bool BookManage::searchBookISBN(string isbn, Book_ptr& book) {
    auto it = list.find(isbn);

    if (it != list.end()) {
        book = it->second;
        return true;
    }
    else{
        return false;
    }
}

void BookManage::showBookList(vector<Book_ptr>& bookList) const {
    for (auto it = this->list.begin(); it != this->list.end(); it++) {
        bookList.push_back({ it->second });
    }
}

bool BookManage::borrowBook(string isbn, Book_ptr& book) {
    if(searchBookISBN(isbn, book) && !book->getIsBorrow()){
        book->setIsBorrow(true);
        return true;
    }
    else{
        return false;
    }

    return false;
}

bool BookManage::returnBook(string& isbn) {
    Book_ptr book;

    if (this->searchBookISBN(isbn, book) && book->getIsBorrow()) {
        book->setIsBorrow(false);
        return true;
    }
    return false;
}

bool BookManage::loadBookList(void){
    string title, author, publisher, isbn, borrowstatus;
    string line;
    string filePath = "book_information.txt";

    // ifstream 객체를 사용하여 파일 열기
    ifstream file(filePath);

    cout<<"현재 작업 디렉토리 : "<<filesystem::current_path()<<endl;
    // file이 정상적으로 열렸는지 확인
    if (!file.is_open()) {
        return false;
    }

    while (getline(file, line)) {
        istringstream iss(line);

        if (getline(iss, title, '\t') && getline(iss, author, '\t') && getline(iss, publisher, '\t') && getline(iss, isbn, '\t') && getline(iss, borrowstatus, '\t')) {
            bool isBorrow;
            // 대출 가능할 경우
            if(borrowstatus=="Yes")
                isBorrow = false;
            // 대출이 불가능 할 경우
            else
                isBorrow = true;
            this->bookInsert(title, author, publisher, isbn, isBorrow);
        }
    }

    file.close();
}

bool BookManage::storeBookList(void) {
    string filePath = "book_information.txt";
    ofstream file(filePath, ios::out);

    if (!file.is_open()) {
        return false;
    }

    for (const auto& book : this->list) {
        string borrowstatus;
        if(book.second->getIsBorrow())
            borrowstatus="No";
        else
            borrowstatus="Yes";

        file << book.second->getTitle() << '\t' << book.second->getAuthor() << '\t' << book.second->getPublisher() << '\t' << book.second->getISBN() << '\t' << borrowstatus << '\n';
    }

    file.close();
}

void EachBook::setISBN(string isbn) {
    this->ISBN = isbn;
}

string EachBook::getISBN(void) const {
    return ISBN;
}

void EachBook::setTitle(string title) {
    this->title = title;
}

string EachBook::getTitle(void) const {
    return title;
}

void EachBook::setAuthor(string author) {
    this->author = author;
}

string EachBook::getAuthor(void) const {
    return author;
}

void EachBook::setPublisher(string publisher) {
    this->publisher = publisher;
}

string EachBook::getPublisher(void) const {
    return publisher;
}

bool EachBook::getIsBorrow(void) const {
    return isBorrow;
}

void EachBook::setIsBorrow(bool isBorrow) {
    this->isBorrow = isBorrow;
}

void EachBook::setIsOverdue(bool isOverdue) {
    this->isOverdue = isOverdue;
}
bool EachBook::getIsOverdue(void) const {
    return isOverdue;
}

Date::Date(unsigned char year, unsigned char month, unsigned char day) {
    this->year = year;
    this->month = month;
    this->day = day;
}

void Date::setDate(unsigned char year, unsigned char month, unsigned char day) {
    this->year = year;
    this->month = month;
    this->day = day;
}

unsigned char Date::getYear(void) {
    return this->year;
}

unsigned char Date::getMonth(void) {
    return this->month;
}

unsigned char Date::getDay(void) {
    return this->day;
}

