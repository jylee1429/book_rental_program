#include "widget.h"
#include "./ui_widget.h"
#include "book.h"
#include "member.h"
#include <QString>
#include <QDebug>
#include <QAbstractItemView>
#include <QMessageBox>
#include <QTableWidget>
#include <QStringList>
#include <QColor>

void showMem(QTableWidget* t, QString id, QString name, QString tel,int row);

BookManage bookManage;
MemberManage memberManage(bookManage);
vector<Book_ptr> searchList;

Widget::Widget(QWidget* parent)
    : QWidget(parent),idChecked(false)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    this->setWindowTitle("도서 관리 프로그램");

    initBorrow();
    initBookTable();

    /* [대출] */
    ui->borrowAuthor->setStyleSheet("background-color:#F5F5F5;");
    ui->borrowPublisher->setStyleSheet("background-color:#F5F5F5;");
    ui->borrowName->setStyleSheet("background-color:#F5F5F5;");
    ui->borrowEnableCnt->setStyleSheet("background-color:#f5f5f5;");
    ui->borrowInfo->setStyleSheet("background-color:white;");


    /* [반납] */
    ui->checkReturnName->setStyleSheet("background-color:#F5F5F5;");
    ui->returnAuthor->setStyleSheet("background-color:#F5F5F5;");
    ui->returnPublisher->setStyleSheet("background-color:#F5F5F5;");
    ui->returnInfo->setStyleSheet("background-color:white;");
    connect( ui->checkReturnID, SIGNAL(clicked()), this, SLOT(checkExistId()));    /* 회원 ID 조회 버튼 */
    connect(ui->checkReturnISBN, SIGNAL(clicked()), this, SLOT(checkExistISBN()));    /* ISBN 조회 버튼 */
    connect(ui->returnInit,SIGNAL(clicked()),this,SLOT(clearReturn()));
    connect( ui->returnButton, SIGNAL(clicked()), this, SLOT(returnBook()));    /* 반납 버튼 */

    /* [회원관리] */
    ui->lookUpMemName->setStyleSheet("background-color:#F5F5F5;");
    ui->lookUpMemTel->setStyleSheet("background-color:#F5F5F5;");
    ui->memInfo->setStyleSheet("background-color:white;");
    ui->regMemBox->setStyleSheet("background-color:white;");
    connect(ui->checkAvail, SIGNAL(clicked()), this, SLOT(checkAvail()));    /*  회원 ID 중복 확인 버튼 클릭 */
    connect(ui->RegMem, SIGNAL(clicked()), this, SLOT(regMem()));    /* 회원 등록 버튼 */
    connect(ui->lookUpMemclear,SIGNAL(clicked()),this,SLOT(lookUpClear()));    /* 회원 조회 초기화 버튼 */
    connect( ui->lookUpMem, SIGNAL(clicked()), this, SLOT(lookUpMem()));    /* 회원 조회 버튼 */
    connect(ui->lookUpMemAll,SIGNAL(clicked()),this,SLOT(showAllMem()));    /* 회원 전체 조회 버튼 */

    /* [도서 관리] */
    ui->bookInfo->setStyleSheet("background-color:white;");
    ui->regBookBox->setStyleSheet("background-color:white;");
    ui->searchAuthor->setStyleSheet("background-color:#F5F5F5;");
    ui->searchISBN->setStyleSheet("background-color:#F5F5F5;");
    ui->searchPublisher->setStyleSheet("background-color:#F5F5F5;");
    ui->searchEnableBookCnt->setStyleSheet("background-color:#F5F5F5;");
    ui->searchTotalBookCnt->setStyleSheet("background-color:#F5F5F5;");
    connect(ui->searchAll,SIGNAL(clicked()),this, SLOT(showAllBook()));

}

Widget::~Widget()
{
    delete ui;
}


QString strToqstr(string str){
    return QString::fromStdString(str);
}
string qstrTostr(QString qstr){
    return qstr.toStdString();
}
int qstrToint(QString qstr){
    return qstr.toInt();
}
QString intToqstr(int n){
    return QString::number(n);
}


//////////////대출////////////////
void Widget::initBorrow(void) {
    int idx;
    // 회원 목록 가져오기 함수 넣기
    // 책 목록 가져오기 함수 넣기
    connect(ui->checkID, SIGNAL(clicked()), this, SLOT(checkID()));
    connect(ui->checkTitle, SIGNAL(clicked()), this, SLOT(findBookByTitle()));
    connect(ui->initButton, SIGNAL(clicked()), this, SLOT(clearSlot()));
    connect(ui->borrowComboTitle, SIGNAL(activated(int)), this, SLOT(findBookInfo(int)));
    connect(ui->borrowButton, SIGNAL(clicked()), this, SLOT(borrowBook()));
}


bool Widget::checkID(void) {
    QString id = ui->borrowID->toPlainText();
    Member_ptr member;


    if (id.isEmpty())
    {
        QMessageBox::information(this, "경고", "회원 ID를 입력하세요.", QMessageBox::Ok);
        return false;
    }
    bool isInt;
    int intId = id.toInt(&isInt);

    if (!isInt)  // Id가 정수가 아닌 경우
    {
        QMessageBox::warning(this, "입력 오류", "ID는 숫자만 입력해야 합니다.", QMessageBox::Ok);
        ui->borrowID->clear();
        return false;
    }

    string tmp;
    if (memberManage.getInfoByID(qstrToint(id), member)) {
        ui->borrowID->setText(id);
        ui->borrowName->setText(strToqstr(member->getName()));
        ui->borrowEnableCnt->setText(intToqstr(member->getAvailableBorrow()));

        ui->borrowID->setStyleSheet("background-color: #90EE90;"); //버튼 색깔 변경(초록)
        return true;
    }
    else {
        QMessageBox::warning(this, "조회 오류", "해당하는 정보의 회원이 없습니다", QMessageBox::Ok);

        ui->borrowID->setStyleSheet("background-color: #FFCCCB; "); //버튼 색깔 변경(빨강)
        return false;
    }
    return false;
}

bool Widget::findBookByTitle(void) {
    QString title = ui->borrowTitle->toPlainText();
    if(title.isEmpty())
    {
        QMessageBox::information(this,"조회 오류","책 제목을 입력해주세요.",QMessageBox::Ok);
        return false;
    }
    int total_cnt, enable_cnt;
    searchList.clear();

    ui->borrowComboTitle->clear();

    if (bookManage.searchBookByTitle(searchList, qstrTostr(title), total_cnt, enable_cnt)) {
        ui->borrowAuthor->setText(strToqstr(searchList[0]->getAuthor()));
        ui->borrowPublisher->setText(strToqstr(searchList[0]->getPublisher()));

        ui->bookTable->clearContents();
        ui->bookTable->setRowCount(searchList.size());

        for(int i=0;i<searchList.size();i++){
            ui->borrowComboTitle->addItem(strToqstr(searchList[i]->getTitle()));
            QTableWidgetItem* searchTitle = new QTableWidgetItem(strToqstr(searchList[i]->getTitle()));
            QTableWidgetItem* searchAuthor = new QTableWidgetItem(strToqstr(searchList[i]->getAuthor()));
            QTableWidgetItem* searchPublisher = new QTableWidgetItem(strToqstr(searchList[i]->getPublisher()));
            QTableWidgetItem* searchISBN = new QTableWidgetItem(strToqstr(searchList[i]->getISBN()));
            QTableWidgetItem* searchIsBorrow;
            if(!searchList[i]->getIsBorrow()){
                searchIsBorrow = new QTableWidgetItem("yes");
            }
            else{
                searchIsBorrow = new QTableWidgetItem("no");
            }
            ui->bookTable->setItem(i, 0, searchTitle);
            ui->bookTable->setItem(i, 1, searchAuthor);
            ui->bookTable->setItem(i, 2, searchPublisher);
            ui->bookTable->setItem(i, 3, searchISBN);
            ui->bookTable->setItem(i, 4, searchIsBorrow);
        }

        ui->borrowTitle->setStyleSheet("background-color:#90EE90;"); //조회 성공(초록)
        return true;
    }
    else {
        QMessageBox::warning(this, "조회 오류", "해당하는 정보의 책이 없습니다", QMessageBox::Ok);

        ui->borrowTitle->setStyleSheet("background-color: #FFCCCB;");  //조회 실패(빨강)
        return false;
    }
    return false;
}

void Widget::findBookInfo(int idx) {
    QString author = strToqstr(searchList[idx]->getAuthor());
    QString publisher = strToqstr(searchList[idx]->getPublisher());

    ui->borrowAuthor->setText(author);
    ui->borrowPublisher->setText(publisher);
}

void Widget::borrowBook(void) {
    QString id = ui->borrowID->toPlainText();

    if(id.isEmpty())
    {
         QMessageBox::information(this,"조회 오류","회원 ID를 입력해주세요.",QMessageBox::Ok);
        return;
    }

    int userId=id.toInt();
    if (ui->borrowComboTitle->count() == 0) {
        QMessageBox::warning(this, "대출 실패", "책을 선택해 주세요.", QMessageBox::Ok);
        return;
    }
    int idx = ui->borrowComboTitle->currentIndex();
    string isbn = searchList[idx]->getISBN();
    if(checkID()&&findBookByTitle())
    {
        if(memberManage.memberBorrowBooks(userId, isbn)){
            QMessageBox::information(this, "대출 승인", "대출되었습니다.", QMessageBox::Ok);
            clearSlot();
        }
        else{
            QMessageBox::information(this, "대출 실패", "대출불가합니다.", QMessageBox::Ok);
            return;
        }
    }

        vector<Book_ptr> bookList;

    bookManage.showBookList(bookList);

    ui->bookTable->clearContents();
    ui->bookTable->setRowCount(bookList.size());

    for(int i=0;i<bookList.size();i++){
        QTableWidgetItem* searchTitle = new QTableWidgetItem(strToqstr(bookList[i]->getTitle()));
        QTableWidgetItem* searchAuthor = new QTableWidgetItem(strToqstr(bookList[i]->getAuthor()));
        QTableWidgetItem* searchPublisher = new QTableWidgetItem(strToqstr(bookList[i]->getPublisher()));
        QTableWidgetItem* searchISBN = new QTableWidgetItem(strToqstr(bookList[i]->getISBN()));
        QTableWidgetItem* searchIsBorrow;
        if(!bookList[i]->getIsBorrow()){
            searchIsBorrow = new QTableWidgetItem("yes");
        }
        else{
            searchIsBorrow = new QTableWidgetItem("no");
        }
        ui->bookTable->setItem(i, 0, searchTitle);
        ui->bookTable->setItem(i, 1, searchAuthor);
        ui->bookTable->setItem(i, 2, searchPublisher);
        ui->bookTable->setItem(i, 3, searchISBN);
        ui->bookTable->setItem(i, 4, searchIsBorrow);
    }
}

void Widget::clearSlot(void) {
    ui->borrowTitle->setStyleSheet("");
    ui->borrowID->setStyleSheet("");
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
    Member_ptr member;

    if (Id.isEmpty())
    {
        QMessageBox::information(this, "경고", "회원 ID를 입력하세요.", QMessageBox::Ok);
        return false;
    }
    bool isInt;
    int intId = Id.toInt(&isInt);

    if (!isInt)  // Id가 정수가 아닌 경우
    {
        QMessageBox::warning(this, "입력 오류", "ID는 숫자만 입력해야 합니다.", QMessageBox::Ok);
        ui->returnID->clear();
        ui->returnID->setStyleSheet("background-color: #FFCCCB;");
        return false;
    }

    if(memberManage.getInfoByID(Id.toInt(), member))
    {
        QString name = QString::fromStdString(member->getName());
        ui->checkReturnName->setText(name);
          ui->returnID->setStyleSheet("background-color: #90EE90;"); //버튼 색깔 변경(초록)
        return true;
    }
    else
    {
        QMessageBox::warning(this, "경고", "존재하지 않는 회원 ID 입니다.", QMessageBox::Ok);
        ui->returnID->clear();
        ui->returnID->setStyleSheet("background-color: #FFCCCB;");
        return false;
    }
}


bool Widget::checkExistISBN() //대출 목록에 ISBN 존재여부 확인
{
    QString isbn = ui->returnISBN->toPlainText(); //입력한 isbn
    QString Id = ui->returnID->toPlainText(); //등록할 ID
    Book_ptr book;

    if(Id.isEmpty())
    {
        QMessageBox::information(this,"조회 실패","ID를 입력해 주세요.",QMessageBox::Ok);
        return false;
    }
    if(memberManage.checkBorrowedBook(Id.toInt(), isbn.toStdString(), book))
    {
        QString title, author, publisher;
        title = QString::fromStdString(book->getTitle());
        author = QString::fromStdString(book->getAuthor());
        publisher = QString::fromStdString(book->getPublisher());

        ui->returnComboTitle->addItem(title);
        ui->returnAuthor->setText(author);
        ui->returnPublisher->setText(publisher);

         ui->returnISBN->setStyleSheet("background-color: #90EE90;"); //버튼 색깔 변경(초록)
        return true;
    }
    else
    {
        QMessageBox::information(this, "경고", "반납 가능한 책이 아닙니다.", QMessageBox::Ok);
        ui->returnISBN->clear();
        ui->returnISBN->setStyleSheet("background-color: #FFCCCB;");
        return false;
    }
}

void Widget::returnBook(){
    QString isbn = ui->returnISBN->toPlainText(); //입력한 isbn
    QString Id = ui->returnID->toPlainText(); //등록할 ID
    vector<Book_ptr> bookList;

    if(memberManage.memberReturnBooks(Id.toInt(), isbn.toStdString())){
        QMessageBox::information(this, "반납", "반납되었습니다.", QMessageBox::Ok);
        clearReturn();
    }
    else{
        QMessageBox::information(this, "반납 실패", "반납 실패", QMessageBox::Ok);
        return;
    }

    bookManage.showBookList(bookList);

    ui->bookTable->clearContents();
    ui->bookTable->setRowCount(bookList.size());

    for(int i=0;i<bookList.size();i++){
        QTableWidgetItem* searchTitle = new QTableWidgetItem(strToqstr(bookList[i]->getTitle()));
        QTableWidgetItem* searchAuthor = new QTableWidgetItem(strToqstr(bookList[i]->getAuthor()));
        QTableWidgetItem* searchPublisher = new QTableWidgetItem(strToqstr(bookList[i]->getPublisher()));
        QTableWidgetItem* searchISBN = new QTableWidgetItem(strToqstr(bookList[i]->getISBN()));
        QTableWidgetItem* searchIsBorrow;
        if(!bookList[i]->getIsBorrow()){
            searchIsBorrow = new QTableWidgetItem("yes");
        }
        else{
            searchIsBorrow = new QTableWidgetItem("no");
        }
        ui->bookTable->setItem(i, 0, searchTitle);
        ui->bookTable->setItem(i, 1, searchAuthor);
        ui->bookTable->setItem(i, 2, searchPublisher);
        ui->bookTable->setItem(i, 3, searchISBN);
        ui->bookTable->setItem(i, 4, searchIsBorrow);
    }
}

void Widget::clearReturn()
{
    ui->returnID->setStyleSheet("");
    ui->returnISBN->setStyleSheet("");
    ui->returnID->clear();
    ui->returnISBN->clear();
    ui->checkReturnName->clear();
    ui->returnComboTitle->clear();
    ui->returnAuthor->clear();
    ui->returnPublisher->clear();

}

///////////회원 관리////////////
bool Widget::checkAvail() //회원 등록 시 id 중복여부 체크
{
    QString RegId = ui->RegMemId->toPlainText(); //등록할 ID

    if(RegId.isEmpty())
    {
        QMessageBox::warning(this,"경고","ID를 입력하세요.",QMessageBox::Ok);
        idChecked=false;
        ui->RegMemId->setStyleSheet("background-color:#FFCCCB;");
        return false;
    }
    bool isInt;
    int intRegId = RegId.toInt(&isInt);

    if (!isInt)  // RegId가 정수가 아닌 경우
    {
        QMessageBox::warning(this, "입력 오류", "ID는 숫자만 입력해야 합니다.", QMessageBox::Ok);
        ui->RegMemId->clear();
         ui->RegMemId->setStyleSheet("background-color:#FFCCCB;");
        return false;
    }

    if(!memberManage.checkAvailableID(RegId.toInt()))
    {
        QMessageBox::warning(this,"경고","사용불가 ID 입니다.",QMessageBox::Ok);
        ui->RegMemId->clear();
        idChecked=false;
         ui->RegMemId->setStyleSheet("background-color:#FFCCCB;");
        return false;
    }
    else
    {
        QMessageBox::information(this, "중복 조회", "등록 가능한 ID 입니다.", QMessageBox::Ok);
        idChecked=true;
        ui->RegMemId->setStyleSheet("background-color: #90EE90;"); //버튼 색깔 변경(초록)
        return true;
    }
}

void Widget::regMem() //회원 등록
{
    QString RegId = ui->RegMemId->toPlainText();
    QString name = ui->RegMemName->toPlainText();
    QString tel = ui->RegMemTel->toPlainText();
    QTableWidget* memTableWidget = ui->memTable;
    vector<Member_ptr> memberList;
    int row = 0;
if (RegId == "" || name == ""|| tel=="") // 셋 중 하나라도 입력 누락되면 메시지 창
        QMessageBox::information(this, "입력 누락", "ID, 전화번호, 이름을 모두 입력해야 합니다.", QMessageBox::Ok);
    else
    {
        if (idChecked || checkAvail())
        {
            memberManage.memberRegister(RegId.toInt(), name.toStdString(), tel.toStdString());
            QMessageBox::information(this,"회원 등록", "회원 등록을 완료하였습니다.",QMessageBox::Ok);

            ui->RegMemId->clear();
            ui->RegMemName->clear();
            ui->RegMemTel->clear();
            ui->RegMemId->setStyleSheet("");
            idChecked=false;
        }
    }
    showAllMem();
}

void Widget::showAllMem()
{
        QTableWidget* memTableWidget = ui->memTable;
        vector<Member_ptr> memberList;
    memberManage.memberShow(memberList);

        if(memberList.size()==0)
    {
        QMessageBox::information(this,"조회 실패","회원 정보가 없습니다.",QMessageBox::Ok);
            return;
    }
        int row=0;
    for(auto it=memberList.begin(); it!=memberList.end();it++)
    {
        showMem(memTableWidget, QString::number((*it)->getID()), QString::fromStdString((*it)->getName()), QString::fromStdString((*it)->getCallNumber()), row++);
    }
}

void Widget::lookUpClear() //회원 조회 입력 초기화
{
    ui->lookUpMemName->clear();
    ui->lookUpMemId->clear();
    ui->lookUpMemTel->clear();
}

void Widget::lookUpMem()  //회원 조회
{
    Member_ptr member;
    int row = 0;
    QString Id = ui->lookUpMemId->toPlainText();
    if(Id.isEmpty())
    {
        QMessageBox::information(this,"조회 실패","조회할 회원의 ID를 입력하세요.",QMessageBox::Ok);
        return;
    }
    bool isInt;
    int intId =Id.toInt(&isInt);

    if (!isInt)  // Id가 정수가 아닌 경우
    {
        QMessageBox::warning(this, "입력 오류", "ID는 숫자만 입력해야 합니다.", QMessageBox::Ok);
        ui->lookUpMemId->clear();
        return;
    }

    QTableWidget* memTableWidget = ui->memTable;
    memTableWidget->clearContents();
    QStringList header;
    header << "ID" << "이름" << "전화번호";
    memTableWidget->setHorizontalHeaderLabels(header);

    /*  전체 조회 */
    if(memberManage.getInfoByID(Id.toInt(), member))
    {
        QString name = QString::fromStdString(member->getName());
        QString tel = QString::fromStdString(member->getCallNumber());
        showMem(memTableWidget, QString::number(member->getID()), name, tel, row++);
        ui->lookUpMemName->setText(name);
        ui->lookUpMemTel->setText(tel);
    }
    else
    {
        QMessageBox::information(this, "조회 실패", "회원 정보가 없습니다.", QMessageBox::Ok);
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
    connect(ui->searchButton, SIGNAL(clicked()), this, SLOT(searchBookTable()));
    connect(ui->clearButton,SIGNAL(clicked()),this,SLOT(clearSearchBook()));
}

// 도서 등록
void Widget::registerBook() {
    QString author = ui->registerAuthor->toPlainText();
    QString title = ui->registerTitle->toPlainText();
    QString publisher = ui->registerPublisher->toPlainText();

    if(author.isEmpty()||title.isEmpty()||publisher.isEmpty())
    {
        QMessageBox::information(this,"등록 실패","모든 항목을 입력해야 합니다.",QMessageBox::Ok);
        return;
    }

    bookManage.bookRegister(qstrTostr(title), qstrTostr(author), qstrTostr(publisher));

    // Clear existing items in the table
    showAllBook();

    ui->registerTitle->clear();
    ui->registerAuthor->clear();
    ui->registerPublisher->clear();
}

//전체 도서 리스트 출력
void Widget::showAllBook()
{
    if(bookManage.sizeList()==0)
    {
        QMessageBox::information(this,"조회 실패","도서 정보가 없습니다.",QMessageBox::Ok);
        return;
    }

       vector<Book_ptr> bookList;
    ui->bookTable->clearContents();
    ui->bookTable->setRowCount(bookManage.sizeList());
    bookManage.showBookList(bookList);

    for (int i = 0; i < bookManage.sizeList(); i++) {
        QTableWidgetItem* searchTitle = new QTableWidgetItem(strToqstr(bookList[i]->getTitle()));
        QTableWidgetItem* searchAuthor = new QTableWidgetItem(strToqstr(bookList[i]->getAuthor()));
        QTableWidgetItem* searchPublisher = new QTableWidgetItem(strToqstr(bookList[i]->getPublisher()));
        QTableWidgetItem* searchISBN = new QTableWidgetItem(strToqstr(bookList[i]->getISBN()));
        QTableWidgetItem* searchIsBorrow;
        if(!bookList[i]->getIsBorrow()){
            searchIsBorrow = new QTableWidgetItem("yes");
        }
        else{
            searchIsBorrow = new QTableWidgetItem("no");
        }
        ui->bookTable->setItem(i, 0, searchTitle);
        ui->bookTable->setItem(i, 1, searchAuthor);
        ui->bookTable->setItem(i, 2, searchPublisher);
        ui->bookTable->setItem(i, 3, searchISBN);
        ui->bookTable->setItem(i, 4, searchIsBorrow);
    }
    ui->bookTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

void Widget::searchBookTable(void){
    QString title = ui->searchTitle->toPlainText();
    int total_cnt, enable_cnt;
    vector<Book_ptr> bookList;

    // 빈칸 채우기
    if(bookManage.searchBookByTitle(bookList, qstrTostr(title), total_cnt, enable_cnt)) {
        ui->searchAuthor->setText(strToqstr(bookList[0]->getAuthor()));
        ui->searchPublisher->setText(strToqstr(bookList[0]->getPublisher()));
        ui->searchISBN->setText(strToqstr(bookList[0]->getISBN()));
        ui->searchEnableBookCnt->setText(intToqstr(enable_cnt));
        ui->searchTotalBookCnt->setText(intToqstr(total_cnt));

        ui->bookTable->clearContents();
        ui->bookTable->setRowCount(bookList.size());

        for(int i=0;i<bookList.size();i++){
            ui->borrowComboTitle->addItem(strToqstr(bookList[i]->getTitle()));
            QTableWidgetItem* searchTitle = new QTableWidgetItem(strToqstr(bookList[i]->getTitle()));
            QTableWidgetItem* searchAuthor = new QTableWidgetItem(strToqstr(bookList[i]->getAuthor()));
            QTableWidgetItem* searchPublisher = new QTableWidgetItem(strToqstr(bookList[i]->getPublisher()));
            QTableWidgetItem* searchISBN = new QTableWidgetItem(strToqstr(bookList[i]->getISBN()));
            QTableWidgetItem* searchIsBorrow;
            if(!bookList[i]->getIsBorrow()){
                searchIsBorrow = new QTableWidgetItem("yes");
            }
            else{
                searchIsBorrow = new QTableWidgetItem("no");
            }
            ui->bookTable->setItem(i, 0, searchTitle);
            ui->bookTable->setItem(i, 1, searchAuthor);
            ui->bookTable->setItem(i, 2, searchPublisher);
            ui->bookTable->setItem(i, 3, searchISBN);
            ui->bookTable->setItem(i, 4, searchIsBorrow);
        }
    }
    else if (ui->searchTitle->toPlainText().isEmpty() &&
                 ui->searchISBN->toPlainText().isEmpty() &&
                 ui->searchPublisher->toPlainText().isEmpty() &&
                 ui->searchAuthor->toPlainText().isEmpty()) {
            QMessageBox::information(this, "조회 실패", "조회할 정보를 입력하세요.", QMessageBox::Ok);
    }
    else{
        QMessageBox::information(this, "조회 실패","해당하는 도서가 없습니다.",QMessageBox::Ok);
    }

}

void Widget::clearSearchBook()
{
    ui->searchTitle->clear();
    ui->searchAuthor->clear();
    ui->searchISBN->clear();
    ui->searchPublisher->clear();
    ui->searchEnableBookCnt->clear();
    ui->searchTotalBookCnt->clear();
}


