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
    number = 1; //初始化排队编号
    wait = new Queue<Customer>;

    i = 1;

    //初始化窗口
    int evaluateTime = 0; //评价次数
    int evaluateSum = 0; //评价总分

    QFile inputFile("://data/evaluation.txt");    // 指定文件


    bool isOk = inputFile.open(QIODevice::ReadOnly);    // 只读打开：

    if(isOk == true){
        QTextStream stream(&inputFile);    // 文本流：
        stream >> evaluateTime >> evaluateSum;//读取
        qDebug()<<evaluateTime<<" "<<evaluateSum;
        BusinessWindow w(false,0,evaluateTime,evaluateSum);
        wins.emplace_back(w);
        inputFile.close();//关闭文本流
    }else{
        qDebug()<<"打开失败";
    }


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
    Customer *customer = new Customer(false,number);
    qDebug()<<"创建顾客:"<<QString::number(number);
    number++;

    wait->enQueue(customer);

}

void MyMainWindow::on_dequeue_clicked()
{
    qDebug()<<"开始出队";
    Customer *customer = wait->deQueue();
    wins[0].setCustomer(customer);
    //delete(customer);
}

void MyMainWindow::on_windowsView_clicked()
{
    QDialog *dialog = new QDialog();
    QLabel *label = new QLabel(dialog);
    QLabel *customerNumber = new QLabel(dialog);
    label->move(20,20);
    label->setText("当前顾客编号");
    customerNumber->move(20,80);
    customerNumber->setText(QString::number(wins[0].getCustomer()->getNumber()));
    dialog->setWindowTitle("窗口1");
    dialog->resize(100,100);
    dialog->show();

}
