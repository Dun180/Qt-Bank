#ifndef MYMAINWINDOW_H
#define MYMAINWINDOW_H

#include <QMainWindow>
#include "utils.h"
#include "queue.h"
#include "function.h"
QT_BEGIN_NAMESPACE
namespace Ui { class MyMainWindow; }
QT_END_NAMESPACE

class MyMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MyMainWindow(QWidget *parent = nullptr);
    ~MyMainWindow();


private slots:
    void on_enter_clicked();

    void on_enqueue_clicked();

    void on_dequeue_clicked();

private:
    Ui::MyMainWindow *ui;
    Queue<int> *wait;   //排队等待队列
    Function *function;
    int i;
};
#endif // MYMAINWINDOW_H
