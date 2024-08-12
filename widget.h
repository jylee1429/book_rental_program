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
    ~Widget();

private:
    Ui::Widget *ui;
    // QTableWidget* bookTableWidget;
    // QTableWidget* memberTableWidget;

public slots:
    void registerBook(void);
    void checkBook(void);
    void checkID(void);
    void clearSlot(void);
    void searchBook(void);
    void setBookInfo(int idx);
    void borrowBook(void);
    /*반납 탭*/
    bool checkExistId();       //회원 ID 존재 여부 확인
    bool checkExistISBN() ; //ISBN 대출목록 존재 여부 확인

    /* 회원 등록 탭 */
    bool checkAvail();  //ID 중복여부 체크
    void regMem();      //회원 등록
    void lookUpMem();//회원 조회

};
#endif // WIDGET_H
