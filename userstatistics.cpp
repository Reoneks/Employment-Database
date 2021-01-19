#include "userstatistics.h"
#include "ui_userstatistics.h"
UserStatistics::UserStatistics(QWidget *parent):QMainWindow(parent),ui(new Ui::UserStatistics){
    ui->setupUi(this);
    this->setWindowFlags(Qt::MSWindowsFixedSizeDialogHint);
    setWindowTitle("Статистика користувачів");
    QPalette pal;
    QPixmap map;
    map.load(":/image/images/MainwindowBackground.png");
    map=map.scaled(541,461,Qt::IgnoreAspectRatio,Qt::SmoothTransformation);
    pal.setBrush(ui->centralwidget->backgroundRole(),QBrush(map));
    ui->centralwidget->setPalette(pal);
    ui->centralwidget->setAutoFillBackground(true);
}
void UserStatistics::LoadData(QVector<QVector<QString>>Result,QVector<QVector<QString>>Result1){
    int datesJS[12],datesC[12];
    for(int i=0;i<12;++i){
        datesJS[i]=0;
        datesC[i]=0;
    }
    for(int i=0;i<Result.length();++i){
        datesJS[Result[i][0].split("-")[1].toInt()-1]+=1;
    }
    for(int i=0;i<Result1.length();++i){
        datesC[Result1[i][0].split("-")[1].toInt()-1]+=1;
    }
    set0=new QBarSet("Здобувачі");
    set1=new QBarSet("Компанії");
    for(int i=0;i<12;++i){
        *set0<<datesJS[i];
        *set1<<datesC[i];
    }
    series=new QBarSeries();
    series->append(set0);
    series->append(set1);
    chart=new QChart();
    chart->addSeries(series);
    chart->setTitle("Графік кількості реєстрацій");
    chart->setAnimationOptions(QChart::SeriesAnimations);
    QStringList categories;
    categories<<"01"<<"02"<<"03"<<"04"<<"05"<<"06"<<"07"<<"08"<<"09"<<"10"<<"11"<<"12";
    axis=new QBarCategoryAxis();
    axis->append(categories);
    axis->setTitleText(Result[0][0].split("-")[0]+" рік");
    chart->createDefaultAxes();
    chart->setAxisX(axis,series);
    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignBottom);
    ui->chartview->setChart(chart);
}
UserStatistics::~UserStatistics(){
    delete ui;
}
