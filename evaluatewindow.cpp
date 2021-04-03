#include "evaluatewindow.h"
#include "ui_evaluatewindow.h"

EvaluateWindow::EvaluateWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::EvaluateWindow)
{
    ui->setupUi(this);
}

EvaluateWindow::~EvaluateWindow()
{
    delete ui;
}
