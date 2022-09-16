#ifndef SECOND_H
#define SECOND_H
#include<QPushButton>
#include <QWidget>
#include<third.h>

namespace Ui {
class Second;
}

class Second : public QWidget
{
    Q_OBJECT

public:
    explicit Second(QWidget *parent = 0);
    ~Second();
    Third*thir=NULL;
    QPushButton * button;
    void paintEvent(QPaintEvent *);

signals:
    void backmain();
private slots:
    void backtomain();
    void on_equal2_clicked();
    void on_equal1_clicked();
    void on_equal3_clicked();
    void on_equal4_clicked();
    void on_equal5_clicked();

private:
    Ui::Second *ui;
};

#endif // SECOND_H
