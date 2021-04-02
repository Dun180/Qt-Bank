#include "mymainwindow.h"
#include "./ui_mymainwindow.h"
#include "queue.h"
#include "queue.cpp"
#include <QMessageBox>


MyMainWindow::MyMainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MyMainWindow)
{
    //初始化Function
    function = new Function();
    QObject::connect(function,&Function::changeLabel,this,&MyMainWindow::windowViewChange);
    ui->setupUi(this);
    wait = new Queue<Customer>;


    //初始化view窗口
    dialog = new QDialog();
    dialog->setWindowTitle("view窗口");
    dialog->resize(400,100);
    QLabel *label1 = new QLabel(dialog);
    QLabel *label2 = new QLabel(dialog);



    label1->move(20,60);
    label1->setText("当前顾客编号");
    label2->move(20,20);
    label2->setText("窗口编号                  1              2              3              VIP");

    for(int i=0;i<function->numOfWindow;i++){
        QLabel *number = new QLabel(dialog);
        number->resize(15,10);
        number->move(140+63*i,60);
        customerNumber.emplace_back(number);

    }





}

MyMainWindow::~MyMainWindow()
{
    for(int i = 0; i < function->numOfWindow; i++){
        wthreads[i]->quit();
        wthreads[i]->wait();
    }
    delete ui;
}


void MyMainWindow::start()
{
    function->createSimulation();//创建模拟
    for (int i = 0; i< function->numOfWindow; ++i) {
        function->callNumber();
    }
}


void MyMainWindow::on_enqueue_clicked()
{
//    Customer *customer = new Customer(false,number);
//    qDebug()<<"创建顾客:"<<QString::number(number);
//    number++;

//    wait->enQueue(customer);
    function->getNumber();

}

void MyMainWindow::on_dequeue_clicked()
{
//    qDebug()<<"开始出队";
//    Customer *customer = wait->deQueue();
//    wins[0].setCustomer(customer);
//    emit changeCustomer(wins[0].getCustomer()->getNumber());
//    //delete(customer);
    function->callNumber();
}
void MyMainWindow::on_windowsView_clicked()
{
    dialog->show();
}

void MyMainWindow::windowViewChange(int l,int num){

    QMutexLocker locker(&m_mutex);
    customerNumber[l]->setNum(num);

}

void MyMainWindow::viewNumOfLine(int num)
{

    QMutexLocker locker(&m_mutex);
    ui->lineNum->setNum(num);

}

void MyMainWindow::endThread()
{
    for(int i = 0; i < function->numOfWindow; i++){
        wthreads[i]->quit();
        wthreads[i]->wait();
    }
    qDebug()<<"排队模拟完成";
}

void MyMainWindow::on_start_clicked()
{
    function->threadFlag2 = true;
    function->createSimulation();
    for(int i = 0;i<function->numOfWindow;i++){
        function->callNumber();
    }
    ui->lineNum->setNum(function->numberOfLine);


    //开启线程
    for(int i = 0; i < function->numOfWindow; i++){
        QThread *wthread = new QThread();
        WinsThread *winsthread = new WinsThread;
        winsthreads.emplace_back(winsthread);
        wthreads.emplace_back(wthread);
        winsthread->moveToThread(wthread);
        connect(wthread,&QThread::finished,wthread,&QObject::deleteLater);
        connect(wthread,&QThread::finished,winsthread,&QObject::deleteLater);
        connect(this,&MyMainWindow::workStart,winsthread,&WinsThread::transactionProcessing);
        connect(winsthread,&WinsThread::setNumOfLine,this,&MyMainWindow::viewNumOfLine);
        connect(winsthread,&WinsThread::setViewCustomer,this,&MyMainWindow::windowViewChange);
        connect(winsthread,&WinsThread::endSignal,this,&MyMainWindow::endThread);
        wthread->start();
        if(wthread->isRunning()){
            qDebug()<<"线程"<<i<<"已开启";
        }else{
            qDebug()<<"线程"<<i<<"未启动";
        }
        emit workStart(i,function);
    }
    //提示对话框
    int ret2 = QMessageBox::information(this,tr("提示"),
                            tr("您的排队号码为：")+QString::number(function->number)+tr("，请牢记！"),QMessageBox::Ok);
    if(ret2 == QMessageBox::Yes) qDebug()<<tr("提示！");

}
