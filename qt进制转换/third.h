#ifndef THIRD_H
#define THIRD_H
#include<QPainter>
#include <QWidget>
#include<QPushButton>
namespace Ui {
class Third;
}

class Third : public QWidget
{
    Q_OBJECT

public:
    explicit Third(QWidget *parent = 0);
    ~Third();
    void paintEvent(QPaintEvent *);

private slots:
    void on_equal1_3_clicked();
    void back();
    void on_equal1_2_clicked();
signals:
    void comeback();
private:
    Ui::Third *ui;
};

#endif // THIRD_H
