#include "widget.h"
#include "./ui_widget.h"
#include "book.h"
#include "member.h"
#include <QString>
#include <QDebug>
#include <QAbstractItemView>
#include <QMessageBox>

vector<Book> bookList;
vector<Book> includeList;
MemberManage memberMange;

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    initBorrow();
    initBookTable();

}

Widget::~Widget()
{
    delete ui;
}





//////////////대출////////////////
void Widget::initBorrow(void){
    int idx;
    // 회원 목록 가져오기 함수 넣기
    // 책 목록 가져오기 함수 넣기
    connect(ui->checkID,SIGNAL(clicked()),this, SLOT(checkID()));
    connect(ui->checkTitle,SIGNAL(clicked()), this, SLOT(checkBook()));
    connect(ui->initButton, SIGNAL(clicked()), this, SLOT(clearSlot()));
    connect(ui->borrowComboTitle, SIGNAL(activated(int)), this, SLOT(setBookInfo(int)));
    connect(ui->borrowButton,SIGNAL(clicked()),this, SLOT(borrowBook()));
}

void Widget::checkID(void){
    QString ID=ui->borrowID->toPlainText();

    string tmp;
    if(memberMange.checkID(ID.toInt(), tmp)){
        ui->borrowID->setText(ID);
        // ui->borrowEnableCnt->setText();                                ////////////////// 수정 필요
        QDebug debug = qDebug();
        debug << "This is a debug message";
    }
    else{
        QMessageBox::question(this, "Error","해당하는 정보의 회원이 없습니다",QMessageBox::Cancel);
    }

    //ui->borrowID->clear();
    //ui->borrowName->clear();
}

void Widget::checkBook(void){
    QString str = ui->borrowTitle->toPlainText();
    includeList.clear();
    ui->borrowComboTitle->clear();

    if(checkTitle(bookList, includeList, str.toStdString())){
        for(int i=0;i<includeList.size();i++){
            ui->borrowComboTitle->addItem(QString::fromStdString(includeList[i].getTitle()));
        }
    }
    else{
        QMessageBox::question(this, "Error","해당하는 정보의 책이 없습니다",QMessageBox::Cancel);
    }
}

void Widget::setBookInfo(int idx){
    QString author = QString::fromStdString(includeList[idx].getAuthor());
    QString publisher = QString::fromStdString(includeList[idx].getPublisher());

    ui->borrowAuthor->setText(author);
    ui->borrowPublisher->setText(publisher);
}

void Widget::borrowBook(void){
    QString id = ui->borrowID->toPlainText();
    QString title=ui->borrowComboTitle->currentText();
    int id_num=id.toInt();
    string title_str=title.toStdString();

    memberMange.memberBorrowBooks(bookList, id_num, title_str);
}
void Widget::clearSlot(void){
    ui->borrowID->clear();
    ui->borrowName->clear();
    ui->borrowAuthor->clear();
    ui->borrowPublisher->clear();
    ui->borrowEnableCnt->clear();
    ui->borrowTitle->clear();
    ui->borrowComboTitle->clear();
}




///////////도서 등록////////////
void Widget::initBookTable(void){
    ui->bookTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    buttonFunc();
}

void Widget::buttonFunc(void){
    connect(ui->registerBookButton,SIGNAL(clicked()),this,SLOT(registerBook()));
    connect(ui->searchButton, SIGNAL(clicked()), this, SLOT(searchBook()));
}
// 도서 등록
void Widget::registerBook(){
    QString author = ui->registerAuthor->toPlainText();
    QString title = ui->registerTitle->toPlainText();
    QString publisher=ui->registerPublisher->toPlainText();
    QString isbn = ui->registerISBN->toPlainText();
    Book temp;

    if(!temp.checkSameISBN(bookList, isbn.toInt())){
        QMessageBox::question(this, "Error","이미 존재하는 ISBN입니다.",QMessageBox::Cancel);
        return;
    }
    temp.setBookInfo(title.toStdString(),author.toStdString(), publisher.toStdString());
    temp.addBook(bookList, isbn.toInt());

    // Clear existing items in the table
    ui->bookTable->clearContents();
    ui->bookTable->setRowCount(bookList.size());

    for(int i = 0; i < bookList.size(); i++){
        QTableWidgetItem* searchTitle = new QTableWidgetItem(QString::fromStdString(bookList[i].getTitle()));
        QTableWidgetItem* searchAuthor = new QTableWidgetItem(QString::fromStdString(bookList[i].getAuthor()));
        QTableWidgetItem* searchPublisher = new QTableWidgetItem(QString::fromStdString(bookList[i].getPublisher()));
        // Add item to the table widget
        ui->bookTable->setItem(i, 0, searchTitle);
        ui->bookTable->setItem(i, 1, searchAuthor);
        ui->bookTable->setItem(i, 2, searchPublisher);
    }
    ui->bookTable->setEditTriggers(QAbstractItemView::NoEditTriggers);

    ui->registerTitle->clear();
    ui->registerAuthor->clear();
    ui->registerPublisher->clear();
    ui->registerISBN->clear();
}

// 도서 검색
void Widget::searchBook(void){
    Book temp;
    vector<Book> searchBookList;

    QString title = ui->searchTitle->toPlainText();

    // 빈칸 채우기
    if(temp.searchBook(bookList, searchBookList, title.toStdString())){
        ui->searchAuthor->setText(QString::fromStdString(temp.getAuthor()));
        ui->searchPublisher->setText(QString::fromStdString(temp.getPublisher()));

        // Clear existing items in the table
        ui->bookTable->clearContents();
        ui->bookTable->setRowCount(searchBookList.size());

        for(int i = 0; i < searchBookList.size(); i++){
            // Create a QTableWidgetItem for each book's title
            QTableWidgetItem* searchTitle = new QTableWidgetItem(QString::fromStdString(searchBookList[i].getTitle()));
            QTableWidgetItem* searchAuthor = new QTableWidgetItem(QString::fromStdString(searchBookList[i].getAuthor()));
            QTableWidgetItem* searchPublisher = new QTableWidgetItem(QString::fromStdString(searchBookList[i].getPublisher()));
            // Add item to the table widget
            ui->bookTable->setItem(i, 0, searchTitle);
            ui->bookTable->setItem(i, 1, searchAuthor);
            ui->bookTable->setItem(i, 2, searchPublisher);
        }
    }
    else{
        QMessageBox::question(this, "Error","해당하는 도서가 없습니다.",QMessageBox::Cancel);
    }
}
