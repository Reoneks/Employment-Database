#include "changenews.h"
#include "ui_changenews.h"
#include "database.h"
ChangeNews::ChangeNews(QWidget *parent):QMainWindow(parent),ui(new Ui::ChangeNews){
    ui->setupUi(this);
    this->setWindowFlags(Qt::MSWindowsFixedSizeDialogHint);
    setWindowTitle("Змінити/додати новини");
    QPalette pal;
    QPixmap map;
    map.load(":/image/images/HelpBackground.png");
    map=map.scaled(369,449,Qt::IgnoreAspectRatio,Qt::SmoothTransformation);
    pal.setBrush(ui->centralwidget->backgroundRole(),QBrush(map));
    ui->centralwidget->setPalette(pal);
    ui->buttonBox->button(QDialogButtonBox::Ok)->setText("Ок");
    ui->buttonBox->button(QDialogButtonBox::Cancel)->setText("Скасувати");
    ui->centralwidget->setAutoFillBackground(true);
}
void ChangeNews::SetNews(QVector<News*> NewsWidget){
    this->NewsWidget=NewsWidget;
    ui->horizontalSlider->setRange(0,NewsWidget.length()-1);
    for(int i=0;i<NewsWidget.length();++i){
        NewsWidget[i]->AllowEdit();
        ui->stackedWidget->addWidget(NewsWidget[i]);
    }
}
ChangeNews::~ChangeNews(){
    delete ui;
}
void ChangeNews::on_buttonBox_accepted(){
    Database *database=new Database();
    foreach(News *i,NewsWidget){
        QVector<QString>Result=i->GetData();
        database->RequestForDatabase("UPDATE [Новини проекту] "
                                     "SET [Рубрика]=\""+Result[3]+"\","
                                         "[Тема]=\""+Result[2]+"\","
                                         "[Основний текст]=\""+Result[1]+"\" "
                                     "WHERE [ID]=\""+Result[0]+"\"");
        database->ImageAddRequest(i->GetImage(),"Новини проекту","Картинка"," WHERE [ID]=\""+Result[0]+"\"");
    }
    foreach(News *i,NewNews){
        QVector<QString>Result=i->GetData();
        database->RequestForDatabase("INSERT INTO [Новини проекту]([Рубрика],[Тема],[Основний текст])"
                                     "VALUES(\""+
                                     Result[3]+"\",\""+
                                     Result[2]+"\",\""+
                                     Result[1]+"\")");
        database->ImageAddRequest(i->GetImage(),"Новини проекту","Картинка"," WHERE [ID]=last_insert_rowid()");
    }
    delete database;
    close();
}
void ChangeNews::on_buttonBox_rejected(){
    close();
}
void ChangeNews::on_ChangeImage_clicked(){
    QString filePath = QFileDialog::getOpenFileName(this, tr("Open File"),"/",tr("Images (*.png *.xpm *.jpg)"));
    if(filePath!=""){
        QPixmap image;
        image.load(filePath);
        image=image.scaled(121,121,Qt::IgnoreAspectRatio,Qt::SmoothTransformation);
        if(position<NewsWidget.length()){
            NewsWidget[position]->SetImage(image);
        }else{
            NewNews[position-NewsWidget.length()]->SetImage(image);
        }
    }
}
void ChangeNews::on_NewNews_clicked(){
    NewNews<<new News;
    NewNews[NewNews.length()-1]->AllowEdit();
    ui->stackedWidget->addWidget(NewNews[NewNews.length()-1]);
    ui->horizontalSlider->setRange(0,NewsWidget.length()-1+NewNews.length());
    ui->stackedWidget->setCurrentIndex(NewsWidget.length()-1+NewNews.length());
    ui->horizontalSlider->setValue(NewsWidget.length()-1+NewNews.length());
    position=NewsWidget.length()-1+NewNews.length();
}
void ChangeNews::on_horizontalSlider_valueChanged(int value){
    ui->stackedWidget->setCurrentIndex(value);
    position=value;
}
void ChangeNews::StartDelete(){
    disconnect(Yes,SIGNAL(clicked()),this,SLOT(StartDelete()));
    disconnect(No,SIGNAL(clicked()),this,SLOT(BreakDelete()));
    mainWindow1->close();
    if(position<NewsWidget.length()){
        Database *database=new Database();
        database->RequestForDatabase("DELETE FROM [Новини проекту]"
                                     "WHERE ID=\""+NewsWidget[position]->GetData()[0]+"\"");
        ui->stackedWidget->removeWidget(NewsWidget[position]);
        NewsWidget.remove(position);
        ui->horizontalSlider->setRange(0,NewsWidget.length()-1+NewNews.length());
        position=0;
        ui->stackedWidget->setCurrentIndex(position);
        ui->horizontalSlider->setValue(position);
        delete database;
    }else{
        ui->stackedWidget->removeWidget(NewNews[position-NewsWidget.length()]);
        NewNews.remove(position-NewsWidget.length());
        ui->horizontalSlider->setRange(0,NewsWidget.length()-1+NewNews.length());
        position=0;
        ui->stackedWidget->setCurrentIndex(position);
        ui->horizontalSlider->setValue(position);
    }
}
void ChangeNews::BreakDelete(){
    disconnect(Yes,SIGNAL(clicked()),this,SLOT(StartDelete()));
    disconnect(No,SIGNAL(clicked()),this,SLOT(BreakDelete()));
    mainWindow1->close();
}
void ChangeNews::on_DeleteNews_clicked(){
    hlayout=new QGridLayout();
    label=new QLabel("Ви впевнені?");
    mainWindow1=new QWidget();
    Yes=new QPushButton("Так");
    No=new QPushButton("Ні");
    hlayout->addWidget(label,0,0);
    hlayout->addWidget(Yes,1,0);
    hlayout->addWidget(No,1,1);
    connect(Yes,SIGNAL(clicked()),this,SLOT(StartDelete()),Qt::UniqueConnection);
    connect(No,SIGNAL(clicked()),this,SLOT(BreakDelete()),Qt::UniqueConnection);
    mainWindow1->setLayout(hlayout);
    mainWindow1->setWindowTitle("Видалення");
    mainWindow1->installEventFilter(this);
    mainWindow1->setWindowFlags(Qt::MSWindowsFixedSizeDialogHint);
    mainWindow1->show();
}
