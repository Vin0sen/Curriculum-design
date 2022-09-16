#include "start.h"
#include<QTimer>
#include<QPushButton>
#include<QPixmap>
Start::Start(QWidget *parent)
    : QWidget(parent)
{
    setFixedSize(1000,800);
    setWindowTitle("制式转换");
    QPushButton *btn=new QPushButton(this);

    label.setParent(this);
    label.move(300,400);
    label.setStyleSheet("font:bold 32px");
    label.setFixedSize(550,100);
    QTimer *timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(timerUpdate()));
    timer->start(1000);

    sec=new Second;
    QPixmap pix("://图片/start.png");
    btn->setFixedSize(pix.width(),pix.height());
    btn->setStyleSheet("QPushButton{border:0px;}");
    btn->setIcon(pix);
    btn->setIconSize(QSize(pix.width()*.8,pix.height()*.5));
    btn->move(this->width()*.3,this->height()*.7);
    connect(btn,&QPushButton::clicked,[=](){
        QTimer::singleShot(500,this,[=](){
            this->hide();
            sec->show();
        });

    });
    connect(sec,&Second::backmain,[=](){

        sec->hide();
        this->show();
    });

}
void Start::paintEvent(QPaintEvent *){
    QPainter painter(this);
    QPixmap pix;
    pix.load("://图片/蓝天白云.png");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);
    painter.setFont(QFont("宋体",25,QFont::Bold,true));
    painter.drawText(QRect(350,300,700,500),"制   式  转  换");

}

Start::~Start()
{

}

void Start::timerUpdate(void)
{
    QDateTime time = QDateTime::currentDateTime();
    QString str = time.toString("yyyy-MM-dd hh:mm:ss dddd");
    this->label.setText(str);
}
