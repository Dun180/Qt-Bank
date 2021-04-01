#ifndef MYMAINWINDOW_H
#define MYMAINWINDOW_H

#include <QMainWindow>
#include "utils.h"
#include "queue.h"
#include "function.h"
#include "QLabel"
#include "winsthread.h"
#include "QThread"

QT_BEGIN_NAMESPACE
namespace Ui { class MyMainWindow; }
QT_END_NAMESPACE

class MyMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MyMainWindow(QWidget *parent = nullptr);
    ~MyMainWindow();

    void start();

private slots:
    void on_enqueue_clicked();
    void on_dequeue_clicked();
    void on_windowsView_clicked();
    void on_start_clicked();

public slots:
    void windowViewChange(int l,int num);
    void viewNumOfLine(int num);
signals:
    void workStart(int identifer,Function* function);
private:
    QThread *wthread;
    Ui::MyMainWindow *ui;
    Queue<Customer> *wait;   //排队等待队列
    vector<BusinessWindow> wins;//窗口
    QDialog *dialog;
    QVector<QLabel*> customerNumber;
    int number;//编号
    int i;

    Function *function;

};
#endif // MYMAINWINDOW_H
