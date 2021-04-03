#ifndef EVALUATEWINDOW_H
#define EVALUATEWINDOW_H

#include <QWidget>

namespace Ui {
class EvaluateWindow;
}

class EvaluateWindow : public QWidget
{
    Q_OBJECT

public:
    explicit EvaluateWindow(QWidget *parent = nullptr);
    ~EvaluateWindow();

private:
    Ui::EvaluateWindow *ui;
};

#endif // EVALUATEWINDOW_H
