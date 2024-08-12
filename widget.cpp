#include "widget.h"
#include "./ui_widget.h"
#include "book.h"
#include "member.h"
#include <QString>
#include <QDebug>
#include <QAbstractItemView>
#include <QMessageBox>

#include <QTableWidget>
#include<QStringList>
#include <QColor>
void showMem(QTableWidget* t, QString id, QString name, QString tel,int row);

vector<Book> bookList;
vector<Book> includeList;
MemberManage memberMange;
Member M;

Widget::Widget(QWidget* parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    this->setWindowTitle("도서 관리 프로그램");

    initBorrow();
    initBookTable();

    /* [반납] */
    /* 회원 ID 조회 버튼 */
    QPushButton* returnIdButton = ui->checkReturnID;
    connect(returnIdButton, SIGNAL(clicked()), this, SLOT(checkExistId()));

    /* ISBN 조회 버튼 */
    QPushButton* returnISBNButton = ui->checkReturnISBN;
    connect(returnISBNButton, SIGNAL(clicked()), this, SLOT(checkExistISBN()));

    /* [회원관리] */
    /*  회원 ID 중복 확인 버튼 클릭 */
    QPushButton* idAvail = ui->checkAvail;
    connect(idAvail, SIGNAL(clicked()), this, SLOT(checkAvail()));

    /* 회원 등록 버튼 */
    QPushButton* regMemBtn = ui->RegMem;
    connect(regMemBtn, SIGNAL(clicked()), this, SLOT(regMem()));

    /* 회원 조회 버튼 */
    QPushButton* lookUpMemBtn = ui->lookUpMem;
    connect(lookUpMemBtn, SIGNAL(clicked()), this, SLOT(lookUpMem()));

}

Widget::~Widget()
{
    delete ui;
}





//////////////대출////////////////
void Widget::initBorrow(void) {
    int idx;
    // 회원 목록 가져오기 함수 넣기
    // 책 목록 가져오기 함수 넣기
    connect(ui->checkID, SIGNAL(clicked()), this, SLOT(checkID()));
    connect(ui->checkTitle, SIGNAL(clicked()), this, SLOT(checkBook()));
    connect(ui->initButton, SIGNAL(clicked()), this, SLOT(clearSlot()));
    connect(ui->borrowComboTitle, SIGNAL(activated(int)), this, SLOT(setBookInfo(int)));
    connect(ui->borrowButton, SIGNAL(clicked()), this, SLOT(borrowBook()));
}

void Widget::checkID(void) {
    QString ID = ui->borrowID->toPlainText();

    string tmp;
    if (memberMange.checkID(ID.toInt(), tmp)) {
        ui->borrowID->setText(ID);
        ui->borrowName->setText(QString::fromStdString(tmp));
        // ui->borrowEnableCnt->setText();                                ////////////////// 수정 필요
        QDebug debug = qDebug();
       //debug << "대출";
    }
    else {
        QMessageBox::question(this, "Error", "해당하는 정보의 회원이 없습니다", QMessageBox::Cancel);
    }

    //ui->borrowID->clear();
    //ui->borrowName->clear();
}

void Widget::checkBook(void) {
    QString str = ui->borrowTitle->toPlainText();
    includeList.clear();
    ui->borrowComboTitle->clear();

    if (checkTitle(bookList, includeList, str.toStdString())) {
        for (int i = 0; i < includeList.size(); i++) {
            ui->borrowComboTitle->addItem(QString::fromStdString(includeList[i].getTitle()));
        }
    }
    else {
        QMessageBox::question(this, "Error", "해당하는 정보의 책이 없습니다", QMessageBox::Cancel);
    }
}

void Widget::setBookInfo(int idx) {
    QString author = QString::fromStdString(includeList[idx].getAuthor());
    QString publisher = QString::fromStdString(includeList[idx].getPublisher());

    ui->borrowAuthor->setText(author);
    ui->borrowPublisher->setText(publisher);
}

void Widget::borrowBook(void) {
    QString id = ui->borrowID->toPlainText();
    QString title = ui->borrowComboTitle->currentText();
    int id_num = id.toInt();
    string title_str = title.toStdString();

    if(memberMange.memberBorrowBooks(bookList, id_num, title_str)) //대출 성공
    {
        QMessageBox::question(this,"information","대출을 완료하였습니다.",QMessageBox::Ok);
        clearSlot();
    }
    else
    {
        QMessageBox::question(this,"error","대출에 실패하였습니다.",QMessageBox::Ok);
    }


}
void Widget::clearSlot(void) {
    ui->borrowID->clear();
    ui->borrowName->clear();
    ui->borrowAuthor->clear();
    ui->borrowPublisher->clear();
    ui->borrowEnableCnt->clear();
    ui->borrowTitle->clear();
    ui->borrowComboTitle->clear();
}



///////////반납////////////
bool Widget::checkExistId() //반납 시 회원 아이디 조회
{
    QString Id = ui->returnID->toPlainText(); //등록할 ID

    if (Id.toInt() == 0)
    {
        QMessageBox::information(this, "경고", "회원 ID를 입력하세요.", QMessageBox::Ok);
        return false;
    }

    Member_maps m = memberMange.memberShow();
    for (auto& it : m)
    {
        if (it.first == Id.toInt())
        {
            //폰트 변경(초록)
            QString name = QString::fromStdString(it.second->getName());
            ui->checkReturnName->setText(name);
            return true;
        }
    }
    qDebug() << Id;

    QMessageBox::information(this, "경고", "존재하지 않는 회원 ID 입니다.", QMessageBox::Ok);
    ui->returnID->clear();
    return false;
}

bool Widget::checkExistISBN() //대출 목록에 ISBN 존재여부 확인
{
    QString isbn = ui->returnISBN->toPlainText(); //입력한 isbn
    QStringList list = M.checkReturnBook(isbn.toInt()); //Member의 checkReturnBook 함수로 대출 목록에서 isbn 검색
    if (list[0] == "") //존재하지 않는 경우
    {
        QMessageBox::information(this, "경고", "대출 중인 책이 아닙니다.", QMessageBox::Ok);
        ui->returnISBN->clear();
        return false;
    }
    //존재하는 경우
    QString title, author, publisher;
    title = list[0]; author = list[1]; publisher = list[2];
    ui->returnComboTitle->addItem(title);
    ui->returnAuthor->setText(author);
    ui->returnPublisher->setText(publisher);

    return true;
}



///////////회원 관리////////////
bool Widget::checkAvail() //회원 등록 시 id 중복여부 체크
{
    QString RegId = ui->RegMemId->toPlainText(); //등록할 ID
    Member_maps m = memberMange.memberShow();
    for (auto& it : m)
    {
        if (it.first == RegId.toInt())
        {
            QMessageBox::information(this, "경고", "이미 존재하는 ID 입니다.", QMessageBox::Ok);
            ui->RegMemId->clear();
            return false;
        }
    }
    qDebug() << RegId;
    return true;
}

void Widget::regMem() //회원 등록
{
    QString RegId = ui->RegMemId->toPlainText();
    QString name = ui->RegMemName->toPlainText();
    QString tel = ui->RegMemTel->toPlainText();
    qDebug() << RegId;
    qDebug() << name;
    qDebug()<<tel;
    if (RegId.toInt() == 0 || name == ""|| tel=="") // 둘 중 하나라도 입력 누락되면 메시지 창
        QMessageBox::information(this, "입력 누락", "ID, 전화번호, 이름을 모두 입력해야 합니다.", QMessageBox::Ok);
    else
    {
        if (checkAvail())
        {
            memberMange.memberRegister(RegId.toInt(), name.toStdString(),tel.toStdString());
            QMessageBox::information(this,"회원 등록", "회원 등록을 완료하였습니다.",QMessageBox::Ok);
            qDebug() << "회원 등록 완료";
            ui->RegMemId->clear();
            ui->RegMemName->clear();
            ui->RegMemTel->clear();
        }

    }

}

void Widget::lookUpMem()  //회원 조회
{
    QString Id = ui->lookUpMemId->toPlainText();
    QString name = ui->lookUpMemName->toPlainText();
    QString tel = ui->lookUpMemTel->toPlainText();

    QTableWidget* memTableWidget = ui->memTable;
    memTableWidget->clear();
    QStringList header;
    header << "ID" << "이름" << "전화번호";
    memTableWidget->setHorizontalHeaderLabels(header);

    /*  전체 조회 */
    Member_maps m = memberMange.memberShow(); //멤버 리스트 반환 받음
    if (m.size() == 0)
    {
        QMessageBox::information(this, "회원 조회", "회원 정보가 없습니다.", QMessageBox::Ok);
    }
    else {
        int row = 0;
        for (auto& it : m)
        {
            bool matchId = (Id.toInt() == 0 || Id.toInt() == it.first);
            bool matchName = (name.isEmpty() || QString::fromStdString(it.second->getName()) == name);
            bool matchTel = (tel.isEmpty() || QString::fromStdString(it.second->getTel()) == tel);

            if (matchId && matchName && matchTel)
            {
                showMem(memTableWidget, QString::number(it.first), QString::fromStdString(it.second->getName()), QString::fromStdString(it.second->getTel()), row++);
            }
        }

    }
}

void showMem(QTableWidget* t, QString id, QString name, QString tel, int row) //좌측 회원 표에 출력
{
    QTableWidgetItem* item;
    /* 회원 id 출력 */
    item = new QTableWidgetItem;
    item->setText(id);
    t->setItem(row, 0, item);

    /* 회원 이름 출력 */
    item = new QTableWidgetItem;
    item->setText(name);
    t->setItem(row, 1, item);

    /* 회원 전화번호 출력 */
    item = new QTableWidgetItem;
    item->setText(tel);
    t->setItem(row,2,item);
    row++;
}


///////////도서 등록////////////
void Widget::initBookTable(void) {
    ui->bookTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    buttonFunc();
}

void Widget::buttonFunc(void) {
    connect(ui->registerBookButton, SIGNAL(clicked()), this, SLOT(registerBook()));
    connect(ui->searchButton, SIGNAL(clicked()), this, SLOT(searchBook()));
}
// 도서 등록
void Widget::registerBook() {
    QString author = ui->registerAuthor->toPlainText();
    QString title = ui->registerTitle->toPlainText();
    QString publisher = ui->registerPublisher->toPlainText();
    QString isbn = ui->registerISBN->toPlainText();
    Book temp;

    if (!temp.checkSameISBN(bookList, isbn.toInt())) {
        QMessageBox::question(this, "Error", "이미 존재하는 ISBN입니다.", QMessageBox::Cancel);
        return;
    }
    temp.setBookInfo(title.toStdString(), author.toStdString(), publisher.toStdString());
    temp.addBook(bookList, isbn.toInt());

    // Clear existing items in the table
    ui->bookTable->clearContents();
    ui->bookTable->setRowCount(bookList.size());

    for (int i = 0; i < bookList.size(); i++) {
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
void Widget::searchBook(void) {
    Book temp;
    vector<Book> searchBookList;

    QString title = ui->searchTitle->toPlainText();

    // 빈칸 채우기
    if (temp.searchBook(bookList, searchBookList, title.toStdString())) {
        ui->searchAuthor->setText(QString::fromStdString(temp.getAuthor()));
        ui->searchPublisher->setText(QString::fromStdString(temp.getPublisher()));

        // Clear existing items in the table
        ui->bookTable->clearContents();
        ui->bookTable->setRowCount(searchBookList.size());

        for (int i = 0; i < searchBookList.size(); i++) {
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
    else {
        QMessageBox::question(this, "Error", "해당하는 도서가 없습니다.", QMessageBox::Cancel);
    }
}
