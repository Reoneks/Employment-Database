#include "createmail.h"
#include "ui_createmail.h"
#include "database.h"
CreateMail::CreateMail(QWidget *parent):QMainWindow(parent),ui(new Ui::CreateMail){
    ui->setupUi(this);
    this->setWindowFlags(Qt::MSWindowsFixedSizeDialogHint);
    setWindowTitle("Написати лист");
    ui->CompanyOrJobSeeker->setReadOnly(true);
    ui->To->setReadOnly(true);
    ui->plainTextEdit_3->setReadOnly(true);
    ui->Name->setReadOnly(true);
    ui->Name_2->setReadOnly(true);
    ui->Position->setReadOnly(true);
    ui->buttonBox->button(QDialogButtonBox::Ok)->setText("Ок");
    ui->buttonBox->button(QDialogButtonBox::Cancel)->setText("Скасувати");
    QPalette pal;
    QPixmap map;
    map.load(":/image/images/CreateMail.png");
    map=map.scaled(350,338,Qt::IgnoreAspectRatio,Qt::SmoothTransformation);
    pal.setBrush(ui->centralwidget->backgroundRole(),QBrush(map));
    ui->centralwidget->setPalette(pal);
    ui->centralwidget->setAutoFillBackground(true);
}
CreateMail::~CreateMail(){
    delete ui;
}
void CreateMail::SetData(QString CompanyOrJobSeeker, QString Title, QString Position, QString To, QString ID){
    this->CompanyOrJobSeeker=CompanyOrJobSeeker;
    Title[0]=Title[0].toUpper();
    To[0]=To[0].toUpper();
    ui->Name->setPlainText(Title);
    ui->Position->setPlainText(Position);
    ui->Name_2->setPlainText(To);
    this->ID=ID;
}
void CreateMail::on_buttonBox_accepted(){
    Database *database=new Database();
    if(CompanyOrJobSeeker=="Здобувач"){
        database->RequestForDatabase("INSERT INTO Заявки(Здобувач,Посада,[Текст заявки],[Дата написання заявки],[Вилучено]) "
                                     "VALUES(("
                                        "SELECT [ID] "
                                        "FROM [Здобувач] "
                                        "WHERE [Здобувач].[Email]=\""+ui->Name->toPlainText().toLower()+"\""
                                     "),("
                                        "SELECT [Вакансії].[ID] "
                                        "FROM [Вакансії] "
                                        "INNER JOIN [Компанія] ON [Компанія].[ID]=[Вакансії].[Компанія] "
                                        "WHERE [Вакансії].[Посада]=\""+ui->Position->toPlainText()+"\" "
                                           "AND [Компанія].[Назва компанії]=\""+ui->Name_2->toPlainText().toLower()+"\""
                                     "),\""+
                                     ui->Text->toPlainText()
                                     +"\",\""+
                                     QDate::currentDate().toString("yyyy-MM-dd")
                                     +"\",\"false\")");
    }else{
        database->RequestForDatabase("UPDATE [Заявки] "
                                     "SET [Відповідь здобувачеві]=\""+ui->Text->toPlainText()+"\" "
                                     "WHERE [Заявки].[Здобувач]=\""+ID+"\" "
                                     "AND [Заявки].[Посада]=("
                                                                   "SELECT [Вакансії].[ID] "
                                                                   "FROM [Вакансії] "
                                                                   "INNER JOIN [Компанія] ON [Компанія].[ID]=[Вакансії].[Компанія] "
                                                                   "WHERE [Вакансії].[Посада]=\""+ui->Position->toPlainText()+"\" "
                                                                       "AND [Компанія].[Назва компанії]=\""+ui->Name->toPlainText().toLower()+"\""
                                                               ")");
    }
    delete database;
    close();
}
void CreateMail::on_buttonBox_rejected(){
    close();
}
