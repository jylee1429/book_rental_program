#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QPushButton>

QT_BEGIN_NAMESPACE
namespace Ui {
	class Widget;
}
QT_END_NAMESPACE

class Widget : public QWidget
{
	Q_OBJECT

public:
	Widget(QWidget* parent = nullptr);
	friend void showMem(QTableWidget* t, QString id, QString name, int row);
	void initBookTable(void);
	void buttonFunc(void);
	void initBorrow(void);
	~Widget();
public slots:
	void registerBook(void);
	void checkBook(void);
	void checkID(void);
	void clearSlot(void);
	void searchBook(void);
	void setBookInfo(int idx);
	void borrowBook(void);

	/*�ݳ� ��*/
	bool checkExistId();       //ȸ�� ID ���� ���� Ȯ��
	bool checkExistISBN(); //ISBN ������ ���� ���� Ȯ��

	/* ȸ�� ��� �� */
	bool checkAvail();  //ID �ߺ����� üũ
	void regMem();      //ȸ�� ���
	void lookUpMem();//ȸ�� ��ȸ
private:
	Ui::Widget* ui;
};
#endif // WIDGET_H
