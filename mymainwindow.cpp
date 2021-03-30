#include "mymainwindow.h"
#include "./ui_mymainwindow.h"
#include "queue.h"
#include "queue.cpp"
#include <QMessageBox>

MyMainWindow::MyMainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MyMainWindow)
{
    ui->setupUi(this);
    wait = new Queue<int>;
    function = new Function();
    i = 1;
}

MyMainWindow::~MyMainWindow()
{
    delete ui;
}




void MyMainWindow::on_enter_clicked()
{
    //问题对话框
       int ret1 = QMessageBox::question(this,tr("问题对话框"),
                           tr("你是vip吗"),QMessageBox::Yes,QMessageBox::No);
       if(ret1 == QMessageBox::Yes) qDebug()<<tr("问题！");
}

void MyMainWindow::on_enqueue_clicked()
{
    int *j = &i;
    qDebug()<<"开始入队";
    wait->enQueue(j);
    Qnode<int> *d = wait->getFront();
    int k = *(d->data);
    ui->label_2->setText(QString::number(k));
    i++;
}

void MyMainWindow::on_dequeue_clicked()
{
    qDebug()<<"开始出队";
    int *j = wait->deQueue();
    Qnode<int> *d = wait->getFront();
    int k = *(d->data);
    ui->label_2->setText(QString::number(k));
}
