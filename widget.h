#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QTableWidget>

QT_BEGIN_NAMESPACE
namespace Ui {
class Widget;
}
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    void initBookTable(void);
    void buttonFunc(void);
    void initBorrow(void);
    bool idChecked; //회원 id 중복 체크
    ~Widget();

private:
    Ui::Widget *ui;

public slots:
    void quit();
    bool checkID(void);
    bool findBookByTitle(void);
    void findBookInfo(int idx);
    void borrowBook(void);
    void clearSlot(void);
    void registerBook(void);
    void searchBookTable(void);
    void showAllBook(); //전체 도서 목록 조회
    void clearSearchBook();//도서 조회 정보 초기화
    void lookUpClear();//회원 조회 정보 초기화
    void showAllMem(); //전체 회원 목록 조회

    /*반납 탭*/
    bool checkExistId();       //회원 ID 존재 여부 확인
    bool checkExistISBN() ; //ISBN 대출목록 존재 여부 확인
    void returnBook();  // 책 반납
    void clearReturn();//반납 정보 초기화
    /* 회원 등록 탭 */
    bool checkAvail();  //ID 중복여부 체크
    void regMem();      //회원 등록
    void lookUpMem();//회원 조회

};
#endif // WIDGET_H
