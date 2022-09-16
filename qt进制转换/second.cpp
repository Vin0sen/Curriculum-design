#include "second.h"
#include "ui_second.h"
#include<QPainter>
#include<QPushButton>
void Second::backtomain(){
    emit backmain();
}
bool pderror(QString s){
    for(int i=0;i<s.size();i++){
        if(s[i]>'9'||s[i]<'0')return 0;
    }return 1;
}

Second::Second(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Second)
{
    ui->setupUi(this);
    thir=new Third;
    Second::move(400,0);
    setWindowTitle("制式转换");
    button=new QPushButton(this);
    button->setText("NEXT");
    button->setGeometry(900,750,100,70);
    button->setStyleSheet("QPushButton{background-color:lightblue;}");
    button->setFont(QFont("Arial black",16));
    ui->pushButton->setStyleSheet("QPushButton{background-color:skyblue;}");
    connect(ui->pushButton,&QPushButton::clicked,this,&Second::backtomain);
    connect(button,&QPushButton::clicked,[=](){
        this->hide();
        thir->show();
    });
    connect(thir,&Third::comeback,[=](){
        thir->hide();
        this->show();
    });
    connect(ui->pushButton_1,&QPushButton::clicked,[=](){
        ui->comboBox_1->setCurrentIndex(0);
    });
    connect(ui->pushButton_2,&QPushButton::clicked,[=](){
        ui->comboBox_2->setCurrentIndex(0);
    });
    connect(ui->pushButton_3,&QPushButton::clicked,[=](){
        ui->comboBox_3->setCurrentIndex(2);
    });
    connect(ui->pushButton_4,&QPushButton::clicked,[=](){
        ui->comboBox_4->setCurrentIndex(2);
    });
    connect(ui->pushButton_5,&QPushButton::clicked,[=](){
        ui->comboBox_5->setCurrentIndex(0);
    });
    connect(ui->pushButton_6,&QPushButton::clicked,[=](){
        ui->comboBox_6->setCurrentIndex(0);
    });
    connect(ui->pushButton_7,&QPushButton::clicked,[=](){
        ui->comboBox_7->setCurrentIndex(0);
    });
    connect(ui->pushButton_8,&QPushButton::clicked,[=](){
        ui->comboBox_8->setCurrentIndex(0);
    });
    connect(ui->pushButton_9,&QPushButton::clicked,[=](){
        ui->comboBox_9->setCurrentIndex(0);
    });
    connect(ui->pushButton_10,&QPushButton::clicked,[=](){
        ui->comboBox_10->setCurrentIndex(0);
    });
//    connect(ui->pushButton,&QPushButton::clicked,[=](){
//        this->hide();
//        thir->show();
//    });
    ui->lineEdit_1->setTextMargins(10,0,0,0);
    ui->lineEdit_2->setTextMargins(10,0,0,0);
    ui->lineEdit_3->setTextMargins(10,0,0,0);
    ui->lineEdit_4->setTextMargins(10,0,0,0);
    ui->lineEdit_5->setTextMargins(10,0,0,0);
    ui->lineEdit_6->setTextMargins(10,0,0,0);
    ui->lineEdit_7->setTextMargins(10,0,0,0);
    ui->lineEdit_8->setTextMargins(10,0,0,0);
    ui->lineEdit_9->setTextMargins(10,0,0,0);
    ui->lineEdit_10->setTextMargins(10,0,0,0);

    ui->invisible->setShortcut(Qt::Key_Return);
    connect(ui->invisible,&QPushButton::clicked,[=](){
        if(ui->lineEdit_9->text()!="")emit ui->equal1->clicked();
        if(ui->lineEdit_7->text()!="")emit ui->equal2->clicked();
        if(ui->lineEdit_5->text()!="")emit ui->equal3->clicked();
        if(ui->lineEdit_3->text()!="")emit ui->equal4->clicked();
        if(ui->lineEdit_1->text()!="")emit ui->equal5->clicked();
    });
}


//长度转换   0米 1英尺 2千米 3丈
//1 英尺=0.3048 米		 1 英尺=0.0003048 千米
//1 千米=3280.839895 英尺	 1 米=3.2808399 英尺
//1 米=0.3 丈             1 丈=3.3333333 米
//1 丈=0.0033333 千米	  1 千米=300 丈
//1 英尺=0.09144 丈    1 丈=10.936133 英尺
void Second::on_equal1_clicked()
{
    QString string=ui->lineEdit_9->text();
    if(string=="")return;
    if(!pderror(string))
    {
        ui->lineEdit_10->setText("error");
        return;
    }
    double num=string.toDouble();
    int i=ui->comboBox_1->currentIndex();
    int j=ui->comboBox_2->currentIndex();
    if(i==j)ui->lineEdit_10->setText(QString::number(num,'f',3));
    if(i==0){
        if(j==1)ui->lineEdit_10->setText(QString::number(num*3.2808399 ,'f',3));
        if(j==2)ui->lineEdit_10->setText(QString::number(num*0.001 ,'f',3));
        if(j==3)ui->lineEdit_10->setText(QString::number(num*0.3,'f',3));
    }
    if(i==1){
        if(j==0)ui->lineEdit_10->setText(QString::number(num*0.3048 ,'f',3));
        if(j==2)ui->lineEdit_10->setText(QString::number(num*0.0003048 ,'f',3));
        if(j==3)ui->lineEdit_10->setText(QString::number(num*0.09144,'f',3));
    }
    if(i==2){
        if(j==0)ui->lineEdit_10->setText(QString::number(num*1000 ,'f',3));
        if(j==1)ui->lineEdit_10->setText(QString::number(num*3280.839895 ,'f',3));
        if(j==3)ui->lineEdit_10->setText(QString::number(num*300,'f',3));
    }
    if(i==3){
        if(j==0)ui->lineEdit_10->setText(QString::number(num*3.3333333 ,'f',3));
        if(j==1)ui->lineEdit_10->setText(QString::number(num*10.936133 ,'f',3));
        if(j==2)ui->lineEdit_10->setText(QString::number(num*0.0033333 ,'f',3));
    }
}

Second::~Second()
{
    delete ui;
}


void Second::paintEvent(QPaintEvent *){
    QPainter painter(this);
    QPixmap pix;
    pix.load("://图片/02.JPG");
    painter.drawPixmap(0,0,2000,950,pix);
//    painter.drawPixmap(0,0,this->width(),this->height(),pix);
}


//重量转换
void Second::on_equal2_clicked()
{
    QString string=ui->lineEdit_7->text();
    if(string=="")return;
    if(!pderror(string))
    {
        ui->lineEdit_8->setText("error");
        return;
    }
    double num=string.toDouble();//左边框中的数
    int i=ui->comboBox_3->currentIndex();//左侧下拉框的index
    int j=ui->comboBox_4->currentIndex();//右侧下拉框的index
    if(i==j)ui->lineEdit_8->setText(QString::number(num,'f',3));
    if(i==0){
        if(j==1)ui->lineEdit_8->setText(QString::number(num*1.1023113 ,'f',3));
        if(j==2)ui->lineEdit_8->setText(QString::number(num*0.5 ,'f',3));
    }
    if(i==1){
        if(j==0)ui->lineEdit_8->setText(QString::number(num*0.9071847 ,'f',3));
        if(j==2)ui->lineEdit_8->setText(QString::number(num*0.4535924 ,'f',3));
    }
    if(i==2){
        if(j==1)ui->lineEdit_8->setText(QString::number(num*2.2046226 ,'f',3));
        if(j==0)ui->lineEdit_8->setText(QString::number(num*2 ,'f',3));
    }
}

//面积转换  0平方米 1英亩 2公顷 3平方千米
//1 平方米=0.0002471 英亩    1 平方米=0.0001 公顷  0.000001
//4046.8564224      0.4046856       0.0040469
//10000     2.4710538 0.01
//1000000      247.1053815  100
void Second::on_equal3_clicked()
{
    QString string=ui->lineEdit_5->text();
    if(string=="")return;
    if(!pderror(string))
    {
        ui->lineEdit_6->setText("error");
        return;
    }
    double num=string.toDouble();
    int i=ui->comboBox_5->currentIndex();
    int j=ui->comboBox_6->currentIndex();
    if(i==j)ui->lineEdit_6->setText(QString::number(num,'f',3));
    if(i==0){
        if(j==1)ui->lineEdit_6->setText(QString::number(num*0.0002471 ,'f',5));
        if(j==2)ui->lineEdit_6->setText(QString::number(num*0.0001 ,'f',4));
        if(j==3)ui->lineEdit_6->setText(QString::number(num*0.000001,'f',5));
    }
    if(i==1){
        if(j==0)ui->lineEdit_6->setText(QString::number(num*4046.8564224 ,'f',5));
        if(j==2)ui->lineEdit_6->setText(QString::number(num*0.4046856 ,'f',5));
        if(j==3)ui->lineEdit_6->setText(QString::number(num*0.0040469,'f',5));
    }
    if(i==2){
        if(j==0)ui->lineEdit_6->setText(QString::number(num*10000 ,'f',3));
        if(j==1)ui->lineEdit_6->setText(QString::number(num*2.4710538,'f',5));
        if(j==3)ui->lineEdit_6->setText(QString::number(num*0.01,'f',3));
    }
    if(i==3){
        if(j==0)ui->lineEdit_6->setText(QString::number(num*1000000 ,'f',3));
        if(j==1)ui->lineEdit_6->setText(QString::number(num*247.1053815,'f',5));
        if(j==2)ui->lineEdit_6->setText(QString::number(num*100,'f',3));
    }
}

//体积转换 0立方米 1毫升 2英国加仑  3升（L）
//1000000  219.9691573 1000
//0.000001  0.00022  .001
//0.0045461 4546.09188 4.5460919
//.001  1000 0.2199692
void Second::on_equal4_clicked()
{
    QString string=ui->lineEdit_3->text();
    if(string=="")return;
    if(!pderror(string))
    {
        ui->lineEdit_4->setText("error");
        return;
    }
    double num=string.toDouble();
    int i=ui->comboBox_7->currentIndex();
    int j=ui->comboBox_8->currentIndex();
    if(i==j)ui->lineEdit_4->setText(QString::number(num,'f',3));
    if(i==0){
        if(j==1)ui->lineEdit_4->setText(QString::number(num*1000000 ,'f',3));
        if(j==2)ui->lineEdit_4->setText(QString::number(num*219.9691573 ,'f',3));
        if(j==3)ui->lineEdit_4->setText(QString::number(num*1000,'f',3));
    }
    if(i==1){
        if(j==0)ui->lineEdit_4->setText(QString::number(num*0.000001 ,'f',6));
        if(j==2)ui->lineEdit_4->setText(QString::number(num*0.00022 ,'f',3));
        if(j==3)ui->lineEdit_4->setText(QString::number(num*.001,'f',3));
    }
    if(i==2){
        if(j==0)ui->lineEdit_4->setText(QString::number(num*0.0045461 ,'f',3));
        if(j==1)ui->lineEdit_4->setText(QString::number(num*4546.09188 ,'f',3));
        if(j==3)ui->lineEdit_4->setText(QString::number(num*4.5460919,'f',3));
    }
    if(i==3){
        if(j==0)ui->lineEdit_4->setText(QString::number(num*0.001,'f',3));
        if(j==1)ui->lineEdit_4->setText(QString::number(num*1000,'f',3));
        if(j==2)ui->lineEdit_4->setText(QString::number(num*0.2199692,'f',3));
    }
}
//温度转换  摄氏开式花式
//华氏温度=1.8*摄氏度+32  开式温度=273.15+摄氏度  花式=1.8*（开式-273.15）+32  开式=273.15+（花式-32）/1.8；
void Second::on_equal5_clicked()
{
    QString string=ui->lineEdit_1->text();
    if(string=="")return;
    if(!pderror(string))
    {
        ui->lineEdit_2->setText("error");
        return;
    }
    double num=string.toDouble();//左边框中的数
    int i=ui->comboBox_9->currentIndex();//左侧下拉框的index
    int j=ui->comboBox_10->currentIndex();//右侧下拉框的index
    if(i==j)ui->lineEdit_2->setText(QString::number(num,'f',3));
    if(i==0){
        if(j==1)ui->lineEdit_2->setText(QString::number(num+273.15,'f',3));
        if(j==2)ui->lineEdit_2->setText(QString::number(num*1.8+32,'f',3));
    }
    if(i==1){
        if(j==0)ui->lineEdit_2->setText(QString::number(num-273.15 ,'f',3));
        if(j==2)ui->lineEdit_2->setText(QString::number(1.8*(num-273.15)+32,'f',3));
    }
    if(i==2){
        if(j==1)ui->lineEdit_2->setText(QString::number(273.15+(num-32)/1.8 ,'f',3));
        if(j==0)ui->lineEdit_2->setText(QString::number((num-32)/1.8 ,'f',3));
    }
}

