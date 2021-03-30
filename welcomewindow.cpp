#include "welcomewindow.h"
#include "ui_welcomewindow.h"
#include "mymainwindow.h"
#include <QMessageBox>
WelcomeWindow::WelcomeWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WelcomeWindow)
{
    ui->setupUi(this);
}

WelcomeWindow::~WelcomeWindow()
{
    delete ui;
}

void WelcomeWindow::on_pushButton_clicked()
{
    close();
    //问题对话框
       int ret1 = QMessageBox::question(this,tr("问题对话框"),
                           tr("你是vip吗"),QMessageBox::Yes,QMessageBox::No);
       if(ret1 == QMessageBox::No) {
           MyMainWindow *w = new MyMainWindow;
           w->show();
           qDebug()<<tr("普通用户");
       }else{
           WelcomeWindow *r = new WelcomeWindow;
           r->show();
       }
}
