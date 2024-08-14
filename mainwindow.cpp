#include "mainwindow.h"
#include "./ui_mainwindow.h"

#define BOOK_COLUMNS 3
#define BOOK_ROWS 1000
#define MEMBER_COLUMNS 5

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    bookTableWidget=new QTableWidget(this);
    // memberTableWidget=new QTableWidget(this);

    bookTableWidget->setGeometry(QRect(10,10,300,200));
    // bookTableWidget->setGeometry(QRect(320,10,300,200));

    for(int i=0;i<BOOK_COLUMNS;i++){
        bookTableWidget->setColumnCount(BOOK_COLUMNS);
    }
    for(int i=0;i<BOOK_ROWS;i++){
        bookTableWidget->setColumnCount(BOOK_ROWS);
    }
    /*
    for(int i=0;i<MEMBER_COLUMNS;i++){
        bookTableWidget->setColumnCount(MEMBER_COLUMNS);
    }
*/
    QStringList bookHeader;
    bookHeader<<"ID"<<"이름"<<"전화번호";
    // QStringList memberHeader;
    // memberHeader<<"제목"<<"저자"<<"출판사"<<"isbn"<<"대출가능여부";
    bookTableWidget->setHorizontalHeaderLabels(bookHeader);
    // memberTableWidget->setHorizontalHeaderLabels(memberHeader);
}

MainWindow::~MainWindow()
{
    delete ui;
}
